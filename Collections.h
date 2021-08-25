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
    std::list<std::unique_ptr<TextNote>> notes;
    std::map<std::string, int> collection;

    void update(std::string fromCollection, std::string toCollection) {

    }

    void addNote(TextNote note) {

    }

};


#endif //NCNOTE_COLLECTIONS_H
