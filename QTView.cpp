//
// Created by erli on 28/08/21.
//

#include "QTView.h"

void QTView::importantNoteView() {
    clearLayout(mainLayout);
    int rowCount = 0;

    //Title
    mainLayout->addWidget(createTitle("Lista note importanti"), rowCount++, 0);
    mainLayout->addWidget(createText("Seleziona una nota per modificare"), rowCount++, 0);

    // Selection list
    selectionList = createListSelection();

    for (auto it: collections->notes) {
        if (it.isImportant())
            new QListWidgetItem(tr((it.getCollection() + " --> " + it.getTitle()).c_str()), selectionList);
    }

    connect(selectionList, SIGNAL(itemSelectionChanged()), this, SLOT(importantNoteSelected()));
    mainLayout->addWidget(selectionList, rowCount++, 0);

    // BTN
    auto backBtn = createButton("Torna indietro");
    connect(backBtn, SIGNAL(released()), this, SLOT(goBackToCollection()));
    mainLayout->addWidget(backBtn, rowCount++, 0);

    setLayout(mainLayout);
    std::string title = "QTNote: " + currentCollection;
    setWindowTitle(tr(title.c_str()));
}

void QTView::editImportantNote(TextNote &note) {
    clearLayout(mainLayout);
    int rowCount = 0;

    //Title
    mainLayout->addWidget(createTitle(note.getTitle()), rowCount++, 0);

    //Text Area
    textArea = createTextArea(collections->getImportantNote(currentTitle).getText(), collections->getImportantNote(currentTitle).isLocked());
    mainLayout->addWidget(textArea, rowCount++, 0);

    // BTN
    auto saveBtn = createButton(collections->getImportantNote(currentTitle).isLocked() ? "Torna indietro" : "Salva");
    connect(saveBtn, SIGNAL(released()), this, SLOT(saveImportantNote()));
    mainLayout->addWidget(saveBtn, rowCount++, 0);

    setLayout(mainLayout);
    std::string title = "QTNote: " + currentCollection;
    setWindowTitle(tr(title.c_str()));

}

void QTView::editNote(TextNote &note) {
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

void QTView::collectionView() {
    clearLayout(mainLayout);
    int rowCount = 0;

    //Title
    mainLayout->addWidget(createTitle("Lista collezioni"), rowCount++, 0);
    mainLayout->addWidget(createText("Seleziona una collezione di note da visualizzare"), rowCount++, 0);

    if (collections->getImportantNoteCount() > 0) {
        // BTN
        auto backBtn = createButton("Note importanti: " + std::to_string(collections->getImportantNoteCount()));
        connect(backBtn, SIGNAL(released()), this, SLOT(viewImportantNotes()));
        mainLayout->addWidget(backBtn, rowCount++, 0);
    }

    // Selection list
    selectionList = createListSelection();
    int i = 0;
    for (auto it : collections->getCollections()) {
        new QListWidgetItem(tr(addCollectionCount(it.first).c_str()), selectionList);
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

void QTView::noteView() {
    clearLayout(mainLayout);
    int rowCount = 0;

    //Title
    mainLayout->addWidget(createTitle("Lista note"), rowCount++, 0);
    mainLayout->addWidget(createText("Seleziona una nota per modificare"), rowCount++, 0);

    // Selection list
    selectionList = createListSelection();
    auto notes = collections->getNotes(currentCollection);

    if (notes->size() > 0) {
        for (auto it: *notes) {
            new QListWidgetItem(tr(it.getTitle().c_str()), selectionList);
        }
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