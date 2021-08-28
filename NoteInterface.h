//
// Created by erli on 25/08/21.
//

#ifndef NCNOTE_NOTEINTERFACE_H
#define NCNOTE_NOTEINTERFACE_H

class Collections; //Fix circular dependency
class NoteInterface {

protected:
    std::string title;
    std::string collection;

    bool locked = false;
    bool important = false;

    NoteInterface(const std::string &title, const std::string &collection) : title(title), collection(collection) {};

public:

    virtual ~NoteInterface() {}

    virtual void registerObs(Collections* obs) = 0;
    virtual void removeObs(Collections* obs) = 0;
    virtual void notify() = 0;

    virtual const std::string &getTitle() const {
        return title;
    }

    const std::string &getCollection() const {
        return collection;
    }

    void setCollection(const std::string &collection) {
        NoteInterface::collection = collection;
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