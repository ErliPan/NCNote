//
// Created by erli on 25/08/21.
//

#ifndef NCNOTE_COLLECTIONINTERFACE_H
#define NCNOTE_COLLECTIONINTERFACE_H


#include <stdlib.h>
#include <string>

class CollectionInterface {

public:
    virtual void update(const std::string &fromCollection, const std::string &toCollection, const bool important, const bool remove) = 0;

protected:
    virtual ~CollectionInterface() {}

};

#endif //NCNOTE_COLLECTIONINTERFACE_H
