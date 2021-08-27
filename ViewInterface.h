//
// Created by erli on 25/08/21.
//

#ifndef NCNOTE_VIEWINTERFACE_H
#define NCNOTE_VIEWINTERFACE_H


#include "TextNote.h"

class ViewInterface {
public:
    virtual ~ViewInterface() {};

    virtual void collectionView(const std::string elm[], const int size) = 0;
    virtual void noteView(const std::string elm[], const int size, const std::string collectionName) = 0;
    virtual void editNote(TextNote &note) = 0;

};


#endif //NCNOTE_VIEWINTERFACE_H
