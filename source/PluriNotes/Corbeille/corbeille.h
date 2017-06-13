#ifndef CORBEILLE_H
#define CORBEILLE_H

#include "NoteManager/notes.h"
#include "iterator.h"
#include "exception.h"
#include "NoteManager/NoteManager.h"

class corbeille{
private:
    Note** deletedNotes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;

    static corbeille* instance; // pointeur sur l'unique instance
    corbeille():deletedNotes(nullptr),nbNotes(0),nbMaxNotes(0){}
    ~corbeille();
    corbeille(const corbeille& m);
    corbeille& operator=(const corbeille& m);
    void addNotes(Note* n);
    friend class NotesManager;
public:
    static corbeille& getCorbeille();
    static void freeCorbeille();
    void viderCorbeille();
    void restaurerNote(const QString& id);

    class Iterator: public _Iterator<Note>{
        friend class corbeille;
        Iterator(Note** notes, unsigned int n): _Iterator(notes,n){}
    public:
        Iterator(): _Iterator(){}
    };
    Iterator begin() const { return Iterator(deletedNotes,nbNotes); }
    Iterator end() const { return Iterator(deletedNotes + nbNotes,nbNotes); }

    class Const_Iterator: public _const_iterator<Note>{
        friend class corbeille;
        Const_Iterator(Note** notes, unsigned int n): _const_iterator(notes,n){}
    public:
        Const_Iterator(): _const_iterator(){}
    };
    Const_Iterator cbegin() const { return Const_Iterator(deletedNotes,nbNotes); }
    Const_Iterator cend() const { return Const_Iterator(deletedNotes + nbNotes,nbNotes); }


};

#endif // CORBEILLE_H
