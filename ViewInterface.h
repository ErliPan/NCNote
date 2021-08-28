//
// Created by erli on 25/08/21.
//

#ifndef NCNOTE_VIEWINTERFACE_H
#define NCNOTE_VIEWINTERFACE_H


#include "TextNote.h"

class ViewInterface {
public:
    virtual ~ViewInterface() {};

    virtual void collectionView() = 0;
    virtual void noteView() = 0;
    virtual void editNote(TextNote &note) = 0;

};


#endif //NCNOTE_VIEWINTERFACE_H
