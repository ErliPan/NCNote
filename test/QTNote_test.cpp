//
// Created by erli on 28/08/21.
//

#include "gtest/gtest.h"
#include "../TextNote.h"
#include "../Collections.h"

TEST(TextNote, Lock) {

    TextNote t("a", "a");
    ASSERT_FALSE(t.isLocked());

    t.setLocked(true);
    ASSERT_TRUE(t.isLocked());

}

TEST(TextNote, CheckTitle) {

    TextNote t("Titolo", "Collezione #1");
    ASSERT_EQ(t.getTitle(), "Titolo");

    t.setTitle("Titolo2");
    ASSERT_EQ(t.getTitle(), "Titolo2");

}

TEST(TextNote, LockTest) {

    TextNote t("a", "a");

    t.setText("123");
    t.setLocked(true);
    t.setText("321");

    ASSERT_EQ(t.getText(), "123");

}

TEST(CollectionTest, defaultValueCheck) {

    Collections c;

    ASSERT_EQ(c.importantNoteCount, 0);
    ASSERT_EQ(c.collectionNoteCount("nothing"), -1);
    ASSERT_FALSE(c.removeNote("a", "a"));

}

TEST(CollectionTest, methodTest) {

    Collections c;

    ASSERT_EQ(c.collectionNoteCount("new collection"), -1);

    ASSERT_TRUE(c.addCollections("new collection"));
    ASSERT_EQ(c.collectionNoteCount("new collection"), 0);

    ASSERT_FALSE(c.addCollections("new collection"));
    ASSERT_EQ(c.collectionNoteCount("new collection"), 0);

}

TEST(CollectionTest, createAndAddNote) {

    Collections c;

    c.addCollections("new collection");
    TextNote& note = c.addOrCreateAndGetNote("Nuova Nota", "new collection");

    ASSERT_EQ(c.collectionNoteCount("new collection"), 1);
    ASSERT_EQ(c.addOrCreateAndGetNote("Nuova Nota", "new collection"), note);

    note.setImportant(true);
    ASSERT_EQ(c.getImportantNote("new collection --> Nuova Nota"), note);

}

TEST(CollectionTest, moveCollection) {

    Collections c;

    c.addCollections("Col1");
    c.addCollections("Col2");

    TextNote& note = c.addOrCreateAndGetNote("Nuova Nota", "Col1");
    ASSERT_EQ(c.collectionNoteCount("Col1"), 1);

    note.setCollection("Col2");

    ASSERT_EQ(c.collectionNoteCount("Col1"), 0);
    ASSERT_EQ(c.collectionNoteCount("Col2"), 1);

}

TEST(CollectionTest, lockedCountCheck) {
    Collections c;

    c.addCollections("c137");
    TextNote& note = c.addOrCreateAndGetNote("Rick", "c137");
    ASSERT_EQ(c.countLocked(), 0);
    note.setLocked(true);
    ASSERT_EQ(c.countLocked(), 1);
}

TEST(CollectionTest, removeNote) {
    Collections c;

    c.addCollections("Col1");
    ASSERT_EQ(c.collectionNoteCount("Col1"), 0);
    TextNote& note = c.addOrCreateAndGetNote("Nuova Nota", "Col1");
    ASSERT_EQ(c.collectionNoteCount("Col1"), 1);
    c.removeNote("Nuova Nota", "Col1");
    ASSERT_EQ(c.collectionNoteCount("Col1"), 0);

}

TEST(ObserverPattern, collectionNoteCountCheck) {

    Collections c; //Create collections class
    ASSERT_EQ(c.collectionNoteCount("new collection"), -1); //Error: "New collection" doesn't exists so -1

    c.addCollections("new collection"); //Create new collection
    ASSERT_EQ(c.collectionNoteCount("new collection"), 0); //New collection exists and it's count is 0

    c.addOrCreateAndGetNote("Nuova Nota", "new collection");
    ASSERT_EQ(c.collectionNoteCount("new collection"), 1);

}

TEST(ObserverPattern, importantNoteObserverCheck) {
    Collections c;

    c.addCollections("new collection");
    c.addOrCreateAndGetNote("Nuova Nota", "new collection");
    TextNote& note = c.addOrCreateAndGetNote("Nuova Nota", "new collection");
    note.setImportant(true);

    ASSERT_EQ(c.getImportantNoteCount(), 1);

}