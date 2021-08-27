//
// Created by erli on 25/08/21.
//

#ifndef NCNOTE_TEXTNOTE_H
#define NCNOTE_TEXTNOTE_H


#include "NoteInterface.h"


class TextNote : public NoteInterface {

protected:
    std::string text;
    Collections* observer;

public:
    const std::string &getText() const {
        return text;
    }

    void setText(const std::string &text) {
        if (!locked)
            this->text = text;
    }

    void registerObs(Collections *obs) override {

    }

    void removeObs(Collections *obs) override {

    }

    void notify() override {

    }
};


#endif //NCNOTE_TEXTNOTE_H
