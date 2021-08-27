//
// Created by erli on 25/08/21.
//

#ifndef NCNOTE_QTVIEW_H
#define NCNOTE_QTVIEW_H


#include <memory>
#include <QWidget>
#include <QtWidgets>
#include "ViewInterface.h"

class QPushButton;

class QTextBrowser;

class QTView : public QWidget, public ViewInterface {
Q_OBJECT
public:
    QTView() {
        mainLayout = QPointer<QGridLayout>(new QGridLayout);

        std::string elm[]{"test1", "test2", "test3"};
        int elmLen = 3;
        collectionView(elm, elmLen);
    }

    void collectionView(const std::string *elm, const int size) override {
        clearLayout(mainLayout);
        int rowCount = 0;

        //Title
        mainLayout->addWidget(createTitle("Lista collezioni"), rowCount++, 0);
        mainLayout->addWidget(createText("Seleziona una collezione di note da visualizzare"), rowCount++, 0);

        selectionList = createListSelection(elm, size);
        connect(selectionList, SIGNAL(itemSelectionChanged()), this, SLOT(collectionSelected()));
        mainLayout->addWidget(selectionList, rowCount++, 0);

        setLayout(mainLayout);
        setWindowTitle(tr("QTNote: Collezioni"));
    }

    void noteView(const std::string *elm, const int size, const std::string collectionName) override {
        clearLayout(mainLayout);
        int rowCount = 0;

        //Title
        mainLayout->addWidget(createTitle("Lista note"), rowCount++, 0);
        mainLayout->addWidget(createText("Seleziona una nota per modificare"), rowCount++, 0);

        selectionList = createListSelection(elm, size);
        connect(selectionList, SIGNAL(itemSelectionChanged()), this, SLOT(noteSelected()));
        mainLayout->addWidget(selectionList, rowCount++, 0);

        auto backBtn = createButton("Torna indietro");
        connect(backBtn, SIGNAL(released()), this, SLOT(goBackToCollection()));
        mainLayout->addWidget(backBtn, rowCount++, 0);

        setLayout(mainLayout);
        std::string title = "QTNote: " + collectionName;
        setWindowTitle(tr(title.c_str()));
    }

    void editNote(TextNote &note) override {
        clearLayout(mainLayout);
        int rowCount = 0;

        //Title
        mainLayout->addWidget(createTitle(note.getText()), rowCount++, 0);
        mainLayout->addWidget(createText("Seleziona una nota per modificare"), rowCount++, 0);

        mainLayout->addWidget(createCheckBox("Bloccato"), rowCount++, 0);
        mainLayout->addWidget(createCheckBox("Importante"), rowCount++, 0);

        textArea = createTextArea();
        mainLayout->addWidget(textArea, rowCount++, 0);

        auto deleteBtn = createButton("Elimina");
        connect(deleteBtn, SIGNAL(released()), this, SLOT(onButtonReleased()));
        mainLayout->addWidget(deleteBtn, rowCount++, 0);

        auto changeCollectionBtn = createButton("Cambia collezione");
        connect(changeCollectionBtn, SIGNAL(released()), this, SLOT(onButtonReleased()));
        mainLayout->addWidget(changeCollectionBtn, rowCount++, 0);

    }

private slots:

    void goBackToCollection() {
        std::string elm[]{"test1", "test2", "test3"};
        int elmLen = 3;
        collectionView(elm, elmLen);
    };

    void collectionSelected() {
        std::string elm[]{"note1", "note2", "note3"};
        int elmLen = 3;
        noteView(elm, elmLen, selectionList->currentItem()->text().toStdString());
    }

    void noteSelected() {

    }

    void onButtonReleased() {
        textArea->clear();
        //QString fullText = "Pulsante premuto " + btn->text();
        QString fullText = "Pulsante premuto ";
        textArea->append(tr(fullText.toStdString().c_str()));
    }

    void selectionChange() {
        QString fullText = "Cambio selezione ";
        textArea->append(tr(fullText.toStdString().c_str()));
    }

private:

    QPointer<QTextBrowser> textArea;
    QPointer<QGridLayout> mainLayout;
    QPointer<QListWidget> selectionList;

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

    QPointer<QListWidget> createListSelection(const std::string list[], int size) {
        auto listWidget = QPointer<QListWidget>(new QListWidget(this));
        for (int i = 0; i < size; i++) {
            new QListWidgetItem(tr(list[i].c_str()), listWidget);
        }
        return listWidget;
    }

    QPointer<QPushButton> createButton(const std::string &text) {
        auto btn = QPointer<QPushButton>(new QPushButton(tr(text.c_str())));
        return btn;
    }

    QPointer<QTextBrowser> createTextArea(const std::string &text = "") {
        auto textArea = QPointer<QTextBrowser>(new QTextBrowser());
        textArea->setTextInteractionFlags(Qt::TextEditable);
        return textArea;
    }

    QPointer<QCheckBox> createCheckBox(const std::string &text) {
        auto check = QPointer<QCheckBox>(new QCheckBox(QString::fromStdString(text)));
        return check;
    }

};


#endif //NCNOTE_QTVIEW_H
