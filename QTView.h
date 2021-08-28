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

    void collectionView() override;
    void noteView() override;
    void editNote(TextNote &note) override;
    void editImportantNote(TextNote &note) override;
    void importantNoteView() override;

private slots:

    void goBackToCollection() {
        collectionView();
    };

    void noteSelected() {
        currentTitle = selectionList->currentItem()->text().toStdString();
        editNote(getCurrentNote(currentTitle));
    }

    void importantNoteSelected() {
        currentTitle = selectionList->currentItem()->text().toStdString();
        editImportantNote(collections->getImportantNote(currentTitle));
    }

    void addCollection() {
        std::string input = inputTextDialog("Inserisci il nome della collezione", "nuova collezione");
        if (input != "" && collections->addCollections(input))
            collectionView();
    }

    void viewNotes() {
        currentCollection = selectionList->currentItem()->text().toStdString();
        currentCollection = currentCollection.substr(10, currentCollection.length());
        noteView();
    }

    void createNote() {
        std::string input = inputTextDialog("Dimmi il titolo della nota", "Titolo molto interessante");
        if (input != "") {
            currentTitle = input;
            collections->addOrCreateAndGetNote(input, currentCollection);
            noteView();
        }
    }

    void viewImportantNotes() {
        importantNoteView();
    }

    void saveCurrentNote() {
        if (!getCurrentNote(currentTitle).isLocked())
            getCurrentNote(currentTitle).setText(textArea->toPlainText().toStdString());
        noteView();
    }

    void saveImportantNote() {
        if (!collections->getImportantNote(currentTitle).isLocked())
            collections->getImportantNote(currentTitle).setText(textArea->toPlainText().toStdString());
        importantNoteView();
    }

    void changeCollection() {
        std::string input = inputTextDialog("A quale collezione lo sposto", currentCollection);
        if (input != "") {
            collections->addCollections(input);
            getCurrentNote(currentTitle).setCollection(input);
            collectionView();
        }
    }

    void deleteNote() {
        collections->removeNote(currentTitle, currentCollection);
        noteView();
    }

    void lockStateChange(int state) {
        if (!getCurrentNote(currentTitle).isLocked())
            getCurrentNote(currentTitle).setText(textArea->toPlainText().toStdString());
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
        return collections->addOrCreateAndGetNote(title, currentCollection);
    }

    std::string addCollectionCount(std::string collection) {
        std::string count = std::to_string(collections->collectionNoteCount(collection));
        for (int i = 0;i < 6 - count.length();i++)
            count = " " + count;
        std::cout << ("\tdim: " + count).length() << std::endl;
        return "dim: " + count + "\t" + collection;
    }

    void clearLayout(QLayout* layout, bool deleteWidgets = true) {
        while (QLayoutItem* item = layout->takeAt(0)) {
            if (deleteWidgets) {
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
