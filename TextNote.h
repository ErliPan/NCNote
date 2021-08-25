//
// Created by erli on 25/08/21.
//

#ifndef NCNOTE_TEXTNOTE_H
#define NCNOTE_TEXTNOTE_H


class TextNote {

protected:
    string text;
    Collections* observer;

public:
    const string &getText() const {
        return text;
    }

    void setText(const string &text) {
        if (!locked)
            NoteInterface::text = text;
    }
};


#endif //NCNOTE_TEXTNOTE_H
