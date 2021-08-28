//
// Created by erli on 25/08/21.
//

#ifndef NCNOTE_TEXTNOTE_H
#define NCNOTE_TEXTNOTE_H


#include <string>
#include "NoteInterface.h"

class TextNote : public NoteInterface {

protected:
    std::string text;

public:

    TextNote(const std::string &title, const std::string &collection) : NoteInterface(title, collection) {}

    const std::string &getText() const {
        return text;
    }

    void setText(const std::string &text) {
        if (!locked)
            this->text = text;
    }

    void registerObs(Collections *obs) override {
        this->observer = obs;
    }

    void removeObs(Collections *obs) override {
        this->observer = nullptr;
    }

    void notify(const std::string &fromCollection) override;

    bool operator==(const TextNote &that) const {
        return (this->title == that.title && this->text == that.text);
    }
};


#endif //NCNOTE_TEXTNOTE_H
