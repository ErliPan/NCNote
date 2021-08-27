//
// Created by erli on 25/08/21.
//

#ifndef NCNOTE_NOTEINTERFACE_H
#define NCNOTE_NOTEINTERFACE_H

class Collections; //Fix circular dependency
class NoteInterface {

protected:
    std::string title;

    bool locked;
    bool important;

    ~NoteInterface() {};
public:

    virtual void registerObs(Collections* obs) = 0;
    virtual void removeObs(Collections* obs) = 0;
    virtual void notify() = 0;

    virtual const std::string &getTitle() const {
        return title;
    }

    virtual void setTitle(const std::string &title) {
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

};

#endif //NCNOTE_NOTEINTERFACE_H