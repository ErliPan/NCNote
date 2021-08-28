//
// Created by erli on 25/08/21.
//

#ifndef NCNOTE_QTVIEW_H
#define NCNOTE_QTVIEW_H


#include <iostream>
#include <memory>
#include <QWidget>
#include <QtWidgets>
#include <algorithm>
#include <cctype>
#include <string>
#include "ViewInterface.h"
#include "Collections.h"

class QPushButton;

class QTextBrowser;

class QTView : public QWidget, public ViewInterface {
Q_OBJECT
public:
    QTView(Collections *collections) : collections(collections) {

        this->show();
        mainLayout = QPointer<QGridLayout>(new QGridLayout);
        collectionView();

    }

    void collectionView() override {
        clearLayout(mainLayout);
        int rowCount = 0;

        //Title
        mainLayout->addWidget(createTitle("Lista collezioni"), rowCount++, 0);
        mainLayout->addWidget(createText("Seleziona una collezione di note da visualizzare"), rowCount++, 0);

        if (collections->getImportantNoteCount() > 0) {
            // BTN
            auto backBtn = createButton("Note importanti: " + collections->getImportantNoteCount());
            connect(backBtn, SIGNAL(released()), this, SLOT(viewImportantNotes()));
            mainLayout->addWidget(backBtn, rowCount++, 0);
        }

        // Selection list
        selectionList = createListSelection();
        for (auto it : collections->getCollections()) {
            new QListWidgetItem(tr(it.first.c_str()), selectionList);
        }
        connect(selectionList, SIGNAL(itemSelectionChanged()), this, SLOT(viewNotes()));
        mainLayout->addWidget(selectionList, rowCount++, 0);

        // BTN
        auto backBtn = createButton("Aggiungi collezione");
        connect(backBtn, SIGNAL(released()), this, SLOT(addCollection()));
        mainLayout->addWidget(backBtn, rowCount++, 0);

        setLayout(mainLayout);
        setWindowTitle(tr("QTNote: Collezioni"));
    }

    void noteView() override {
        clearLayout(mainLayout);
        int rowCount = 0;

        //Title
        mainLayout->addWidget(createTitle("Lista note"), rowCount++, 0);
        mainLayout->addWidget(createText("Seleziona una nota per modificare"), rowCount++, 0);

        // Selection list
        selectionList = createListSelection();
        auto notes = collections->getNotes(currentCollection);

        if (notes->size() > 0) {
            for (auto it: *notes)
                new QListWidgetItem(tr(it.getTitle().c_str()), selectionList);
        } else {
            mainLayout->addWidget(createText("Nessuna nota. Creane una"), rowCount++, 0);
        }

        connect(selectionList, SIGNAL(itemSelectionChanged()), this, SLOT(noteSelected()));
        mainLayout->addWidget(selectionList, rowCount++, 0);

        // BTN
        auto newNoteBtn = createButton("Crea nota");
        connect(newNoteBtn, SIGNAL(released()), this, SLOT(createNote()));
        mainLayout->addWidget(newNoteBtn, rowCount++, 0);

        // BTN
        auto backBtn = createButton("Torna indietro");
        connect(backBtn, SIGNAL(released()), this, SLOT(goBackToCollection()));
        mainLayout->addWidget(backBtn, rowCount++, 0);

        setLayout(mainLayout);
        std::string title = "QTNote: " + currentCollection;
        setWindowTitle(tr(title.c_str()));
    }

    void editNote(TextNote &note) override {
        clearLayout(mainLayout);
        int rowCount = 0;

        //Title
        mainLayout->addWidget(createTitle(note.getTitle()), rowCount++, 0);

        //CHeckbox
        auto lockCheck = createCheckBox("Bloccato");
        lockCheck->setChecked(getCurrentNote(currentTitle).isLocked());
        mainLayout->addWidget(lockCheck, rowCount++, 0);
        connect(lockCheck, SIGNAL(stateChanged(int)), this, SLOT(lockStateChange(int)));

        //CHeckbox
        auto importantCheck = createCheckBox("Importante", getCurrentNote(currentTitle).isLocked());
        importantCheck->setChecked(getCurrentNote(currentTitle).isImportant());
        mainLayout->addWidget(importantCheck, rowCount++, 0);
        connect(importantCheck, SIGNAL(stateChanged(int)), this, SLOT(importantStateChange(int)));

        //Text Area
        textArea = createTextArea(getCurrentNote(currentTitle).getText(), getCurrentNote(currentTitle).isLocked());
        mainLayout->addWidget(textArea, rowCount++, 0);

        // BTN
        auto saveBtn = createButton(getCurrentNote(currentTitle).isLocked() ? "Torna indietro" : "Salva");
        connect(saveBtn, SIGNAL(released()), this, SLOT(saveCurrentNote()));
        mainLayout->addWidget(saveBtn, rowCount++, 0);

        // BTN
        auto changeCollectionBtn = createButton("Cambia collezione", getCurrentNote(currentTitle).isLocked());
        connect(changeCollectionBtn, SIGNAL(released()), this, SLOT(changeCollection()));
        mainLayout->addWidget(changeCollectionBtn, rowCount++, 0);

        // BTN
        auto deleteBtn = createButton("Elimina", getCurrentNote(currentTitle).isLocked());
        connect(deleteBtn, SIGNAL(released()), this, SLOT(deleteNote()));
        mainLayout->addWidget(deleteBtn, rowCount++, 0);

        setLayout(mainLayout);
        std::string title = "QTNote: " + currentCollection;
        setWindowTitle(tr(title.c_str()));

    }

private slots:

    void goBackToCollection() {
        collectionView();
    };

    void noteSelected() {
        currentTitle = selectionList->currentItem()->text().toStdString();
        editNote(getCurrentNote(currentTitle));
    }

    void addCollection() {
        std::string input = inputTextDialog("Inserisci il nome della collezione", "nuova collezione");
        if (input != "" && collections->addCollections(input))
            collectionView();
    }

    void viewNotes() {
        currentCollection = selectionList->currentItem()->text().toStdString();
        noteView();
    }

    void createNote() {
        std::string input = inputTextDialog("Dimmi il titolo della nota", "Titolo molto interessante");
        if (input != "") {
            currentTitle = input;
            collections->addNote(input, currentCollection);
            noteView();
        }
    }

    void viewImportantNotes() {

    }

    void saveCurrentNote() {
        if (!getCurrentNote(currentTitle).isLocked())
            getCurrentNote(currentTitle).setText(textArea->toPlainText().toStdString());
        noteView();
    }

    void changeCollection() {

    }

    void deleteNote() {

    }

    void lockStateChange(int state) {
        getCurrentNote(currentTitle).setLocked(state);
        editNote(getCurrentNote(currentTitle));
    }

    void importantStateChange(int state) {
        getCurrentNote(currentTitle).setImportant(state);
    }

private:

    Collections * collections;
    QPointer<QTextBrowser> textArea;
    QPointer<QGridLayout> mainLayout;
    QPointer<QListWidget> selectionList;

    std::string currentCollection = "";
    std::string currentTitle = "";

    TextNote& getCurrentNote(const std::string &title) {
        return collections->addNote(title, currentCollection);
    }

    void clearLayout(QLayout* layout, bool deleteWidgets = true)
    {
        while (QLayoutItem* item = layout->takeAt(0))
        {
            if (deleteWidgets)
            {
                if (QWidget* widget = item->widget())
                    widget->deleteLater();
            }
            if (QLayout* childLayout = item->layout())
                clearLayout(childLayout, deleteWidgets);
            delete item;
        }
    }

    std::string inputTextDialog(const std::string &question, const std::string &hint) {
        bool ok;
        QString text = QInputDialog::getText(this, tr(question.c_str()),tr(question.c_str()),
                                             QLineEdit::Normal,QString::fromStdString(hint), &ok);

        if (ok && !text.isEmpty()) {
            std::string stringText = text.toStdString();

            // Stackoverflow toLowerCase function in C++
            std::transform(stringText.begin(), stringText.end(), stringText.begin(), [](unsigned char c){ return std::tolower(c); });

            return stringText;
        }
        return "";
    }

    QPointer<QLabel> createTitle(const std::string &titleText) {
        auto title = QPointer<QLabel>(new QLabel());
        title->setAlignment(Qt::AlignCenter);
        title->setText(QString::fromStdString(titleText));
        QFont font = title->font();
        font.setPointSize(20);
        font.setBold(true);
        title->setFont(font);
        return title;
    }

    QPointer<QLabel> createText(const std::string &text) {
        auto label = QPointer<QLabel>(new QLabel());
        label->setText(QString::fromStdString(text));
        return label;
    }

    QPointer<QListWidget> createListSelection() {
        auto listWidget = QPointer<QListWidget>(new QListWidget(this));
        return listWidget;
    }

    QPointer<QPushButton> createButton(const std::string &text, bool locked = false) {
        auto btn = QPointer<QPushButton>(new QPushButton(tr(text.c_str())));
        btn->setEnabled(!locked);
        return btn;
    }

    QPointer<QTextBrowser> createTextArea(const std::string &text, bool locked = false) {
        auto textArea = QPointer<QTextBrowser>(new QTextBrowser());
        textArea->setText(QString::fromStdString(text));
        if (!locked)
            textArea->setTextInteractionFlags(Qt::TextEditable);
        return textArea;
    }

    QPointer<QCheckBox> createCheckBox(const std::string &text, bool locked = false) {
        auto check = QPointer<QCheckBox>(new QCheckBox(QString::fromStdString(text)));
        if (locked) { //Set checkable have a bug where a checked box looks like unchecked
            check->setAttribute(Qt::WA_TransparentForMouseEvents);
            check->setFocusPolicy(Qt::NoFocus);
        }
        return check;
    }

};


#endif //NCNOTE_QTVIEW_H
