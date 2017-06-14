/*Pour generaliser les types de note, factory method ou adapter?
*/



#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include "notes.h"
#include "iterator.h"
#include "exception.h"

class NotesManager {

private:
    Note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;


    //filename à manager
    mutable QString filename;

    static NotesManager* instance; // pointeur sur l'unique instance
    NotesManager():notes(nullptr),nbNotes(0),nbMaxNotes(0),filename(""){}
    ~NotesManager();
    NotesManager(const NotesManager& m);
    NotesManager& operator=(const NotesManager& m);

public:
    void addNotes(Note* n);
    /*besoin de generaliser pour Notes
    Article* getArticle(const QString& id); // return the article with identificator id
    Article* getNewArticle();  //create a new article
    */
    static NotesManager& getManager();
    static void freeManager(); // free the memory used by the NotesManager; it can be rebuild later

    //Note* getNote(const QString& id);
    //Note* getNewNote(char type);

    void deleteNote(const QString& id);

    QString getFilename() const { return filename; }
    void setFilename(const QString& f) { filename=f; }
    void load(); // load all notes
    Note* load(const QString& id);
    void save() const; //save all notes (at the beginning)
    void save(const QString& id, Version* v); // create a note in array notes
    class Iterator: public _Iterator<Note>{
        friend class NotesManager;
        Iterator(Note** notes, unsigned int n): _Iterator(notes,n){}
    };
    Iterator begin() const { return Iterator(notes,nbNotes); }
    Iterator end() const { return Iterator(notes + nbNotes,nbNotes); }

    class Const_Iterator: public _const_iterator<Note>{
        friend class NotesManager;
        Const_Iterator(Note** notes, unsigned int n): _const_iterator(notes,n){}
    };
    Const_Iterator cbegin() const { return Const_Iterator(notes,nbNotes); }
    Const_Iterator cend() const { return Const_Iterator(notes + nbNotes,nbNotes); }

};


#endif // NOTEMANAGER_H
