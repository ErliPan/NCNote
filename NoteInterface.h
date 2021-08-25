//
// Created by erli on 25/08/21.
//

#ifndef NCNOTE_NOTEINTERFACE_H
#define NCNOTE_NOTEINTERFACE_H


class NoteInterface {

protected:
    string title;

    bool locked;
    bool important;

    ~NoteInterface() {};
public:

    virtual void registerObs(Collections* obs) = 0;
    virtual void removeObs(Collections* obs) = 0;
    virtual void notify() = 0;

    virtual const string &getTitle() const {
        return title;
    }

    virtual void setTitle(const string &title) {
        if (!locked)
        NoteInterface::title = title;
    }

    virtual bool isLocked() const {
        return locked;
    }

    virtual void setLocked(bool locked) {
        NoteInterface::locked = locked;
    }

    virtual bool isImportant() const {
        return important;
    }

    virtual void setImportant(bool important) {
        if (!locked)
        NoteInterface::important = important;
    }

public:
    virtual void registerObs() = 0;
    virtual void removeObs() = 0;
    virtual void notify() const = 0;

};

#endif //NCNOTE_NOTEINTERFACE_H