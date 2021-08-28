//
// Created by erli on 28/08/21.
//

#include "TextNote.h"
#include "Collections.h"

void TextNote::notify(const std::string &fromCollection, const bool remove) {
    observer->update(fromCollection, NoteInterface::collection, this->isImportant(), remove);
}

void TextNote::removeObs(Collections *obs) {
    notify(this->collection, true);
    this->observer = nullptr;
}