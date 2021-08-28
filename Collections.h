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


    void update(const std::string &fromCollection, const std::string &toCollection) {

    }

    bool addCollections(const std::string &name) {
        for (auto it : collection)
            if (it.first == name) return false;

        collection.insert(std::pair<std::string, int>(name, 0));
        return true;
    }

    TextNote& addNote(const std::string &title, const std::string &collection) {

        for (auto it = notes.begin(); it != notes.end(); it++) {
            if ((it->getTitle()) == title && (it->getCollection()) == collection)
                return *it;
        }

        TextNote elm(title, collection);
        notes.push_back(elm);
        return notes.back();
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

private:
    int importantNoteCount = 0;

};

#endif //NCNOTE_COLLECTIONS_H
