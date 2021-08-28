//
// Created by erli on 25/08/21.
//

#ifndef NCNOTE_COLLECTIONS_H
#define NCNOTE_COLLECTIONS_H


#include "CollectionInterface.h"
#include "TextNote.h"
#include <stdlib.h>
#include <memory>
#include <list>
#include <map>

class Collections : public CollectionInterface {

public:
    std::map<std::string, int> collection;
    std::list<TextNote> notes;
    int importantNoteCount = 0;


    void update(const std::string &fromCollection, const std::string &toCollection, const bool important, const bool remove) {

        if (remove) {
            collection[fromCollection]--;
        } else if (fromCollection == toCollection) {
            important ? importantNoteCount++ : importantNoteCount--;
        } else {
            collection[fromCollection]--;
            collection[toCollection]++;
        }
    }

    bool removeNote(const std::string &title, const std::string &collection) {
        for (auto it = notes.begin(); it != notes.end(); it++) {
            if ((it->getTitle()) == title && (it->getCollection()) == collection) {
                it->removeObs(this);
                notes.erase(it);
                return true;
            }
        }
        return false;
    }

    int collectionNoteCount(const std::string &name) {
        for (auto it : collection)
            if (it.first == name)
                return collection[name];

        return -1;
    }

    bool addCollections(const std::string &name) {
        for (auto it : collection)
            if (it.first == name)
                return false;

        collection.insert(std::pair<std::string, int>(name, 0));
        return true;
    }

    TextNote& addOrCreateAndGetNote(const std::string &title, const std::string &collectionName) {

        for (auto it = notes.begin(); it != notes.end(); it++) {
            if ((it->getTitle()) == title && (it->getCollection()) == collectionName)
                return *it;
        }

        TextNote elm(title, collectionName);
        elm.registerObs(this);
        notes.push_back(elm);
        collection[collectionName]++;
        return notes.back();
    }

    TextNote& getImportantNote(const std::string &collectionAndTitle) {
        for (auto it = notes.begin(); it != notes.end(); it++) {
            if (it->isImportant() && (it->getCollection() + " --> " + it->getTitle()) == collectionAndTitle)
                return *it;
        }
        return *notes.end();
    }

    std::map<std::string, int>& getCollections() {
        return collection;
    }

    std::unique_ptr<std::list<TextNote>> getNotes(const std::string collection) {
        auto ret = std::unique_ptr<std::list<TextNote>>(new std::list<TextNote>);

        for (auto it : notes) {
            if (it.getCollection() == collection) {
                ret->push_back(it);
            }
        }

        return ret;
    }

    int getImportantNoteCount() const {
        return importantNoteCount;
    }

};

#endif //NCNOTE_COLLECTIONS_H
