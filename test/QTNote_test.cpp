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

TEST(ObserverPattern, collectionNoteCountCheck) {

    Collections c;
    ASSERT_EQ(c.collectionNoteCount("new collection"), -1);

    c.addCollections("new collection");
    ASSERT_EQ(c.collectionNoteCount("new collection"), 0);

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

