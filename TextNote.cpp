//
// Created by erli on 28/08/21.
//

#include "TextNote.h"
#include "Collections.h"

void TextNote::notify(const std::string &fromCollection) {
    observer->update(fromCollection, NoteInterface::collection, this->isImportant());
}