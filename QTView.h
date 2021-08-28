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

        // Selection list
        selectionList = createListSelection();
        selectionList = createListSelection();
        for (auto it : collections->getCollections()) {
            new QListWidgetItem(tr(it.first.c_str()), selectionList);
        }
        connect(selectionList, SIGNAL(itemSelectionChanged()), this, SLOT(collectionSelected()));
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

        mainLayout->addWidget(createCheckBox("Bloccato"), rowCount++, 0);
        mainLayout->addWidget(createCheckBox("Importante"), rowCount++, 0);

        textArea = createTextArea();
        mainLayout->addWidget(textArea, rowCount++, 0);

        // BTN
        auto saveBtn = createButton("Salva");
        connect(saveBtn, SIGNAL(released()), this, SLOT(onButtonReleased()));
        mainLayout->addWidget(saveBtn, rowCount++, 0);

        // BTN
        auto changeCollectionBtn = createButton("Cambia collezione");
        connect(changeCollectionBtn, SIGNAL(released()), this, SLOT(onButtonReleased()));
        mainLayout->addWidget(changeCollectionBtn, rowCount++, 0);

        // BTN
        auto deleteBtn = createButton("Elimina");
        connect(deleteBtn, SIGNAL(released()), this, SLOT(onButtonReleased()));
        mainLayout->addWidget(deleteBtn, rowCount++, 0);

        setLayout(mainLayout);
        std::string title = "QTNote: " + note.getTitle();
        setWindowTitle(tr(title.c_str()));

    }

private slots:

    void goBackToCollection() {
        collectionView();
    };

    void addCollection() {
        std::string input = inputTextDialog("Inserisci il nome della collezione", "nuova collezione");
        if (input != "") {
            collections->addCollections(input);
            collectionView();
        }
    }

    void collectionSelected() {
        currentCollection = selectionList->currentItem()->text().toStdString();
        noteView();
    }

    void createNote() {
        std::string input = inputTextDialog("Dimmi il titolo della nota", "Titolo molto interessante");
        if (input != "") {
            currentNote = std::unique_ptr<TextNote>(&collections->addNote(input, currentCollection));
            noteView();
        }
    }

    void noteSelected() {
        editNote(*currentNote);
    }

    void onButtonReleased() {
        textArea->clear();
        //QString fullText = "Pulsante premuto " + btn->text();
        QString fullText = "Pulsante premuto ";
        textArea->append(tr(fullText.toStdString().c_str()));
    }

private:

    Collections * collections;
    QPointer<QTextBrowser> textArea;
    QPointer<QGridLayout> mainLayout;
    QPointer<QListWidget> selectionList;

    std::string currentCollection = "";
    std::unique_ptr<TextNote> currentNote;

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

    QPointer<QPushButton> createButton(const std::string &text) {
        auto btn = QPointer<QPushButton>(new QPushButton(tr(text.c_str())));
        return btn;
    }

    QPointer<QTextBrowser> createTextArea(const std::string &text = "") {
        auto textArea = QPointer<QTextBrowser>(new QTextBrowser());
        textArea->setText(QString::fromStdString(text));
        textArea->setTextInteractionFlags(Qt::TextEditable);
        return textArea;
    }

    QPointer<QCheckBox> createCheckBox(const std::string &text) {
        auto check = QPointer<QCheckBox>(new QCheckBox(QString::fromStdString(text)));
        return check;
    }

};


#endif //NCNOTE_QTVIEW_H
