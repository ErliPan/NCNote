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

    static const std::string SPECIAL_COLLECTION;

    Collections() {
        collection.insert(std::pair<std::string, int>(SPECIAL_COLLECTION, 0));

    }

    void update(const std::string &fromCollection, const std::string &toCollection) {

    }

    void addCollections(const std::string &name) {
        collection.insert(std::pair<std::string, int>(name, 0));
    }

    TextNote& addNote(const std::string &title, const std::string &collection) {
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

    TextNote& getNote(const int index) {
        auto it = notes.begin();
        if (notes.size() > index)
            std::advance(it, index);
        return *it;
    }

};

#endif //NCNOTE_COLLECTIONS_H
