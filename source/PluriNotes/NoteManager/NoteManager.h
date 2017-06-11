/*Pour generaliser les types de note, factory method ou adapter?
*/



#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include "notes.h"
#include "iterator.h"
#include "exception.h"

class NotesManager {

private:
    /*besoin de generaliser pour Note
    Article** articles;
    unsigned int nbArticles;
    unsigned int nbMaxArticles;
    void addArticle(Article* a);
    void addArticle(const QString& i, const QString& ti, const QString& te);
    */

    Note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    void addNotes(Note* n);

    //filename à manager
    mutable QString filename;

    static NotesManager* instance; // pointeur sur l'unique instance
    NotesManager():notes(nullptr),nbNotes(0),nbMaxNotes(0),filename(""){}
    ~NotesManager();
    NotesManager(const NotesManager& m);
    NotesManager& operator=(const NotesManager& m);

public:
    /*besoin de generaliser pour Notes
    Article* getArticle(const QString& id); // return the article with identificator id
    Article* getNewArticle();  //create a new article
    */
    static NotesManager& getManager();
    static void freeManager(); // free the memory used by the NotesManager; it can be rebuild later

    Note* getNote(const QString& id);
    //Note* getNewNote(char type);

    void deleteNote(const QString& id);

    QString getFilename() const { return filename; }
    void setFilename(const QString& f) { filename=f; }
    void load(); // load all notes
    void load(const QString& id);
    void save() const; //save all notes (at the beginning)
    void save(const QString& id); // create a note in array notes
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
/*
    class Iterator {
            friend class NotesManager;
            Note** cur;
            unsigned int nbRemain;
            Iterator(Note** n, unsigned int nb):cur(n), nbRemain(nb){}
        public:
            Iterator():cur(nullptr),nbRemain(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw NotesException("error, next on an iterator which is done");
                nbRemain--;
                cur++;
            }
            Note& current() const {
                if (isDone())
                    throw NotesException("error, indirection on an iterator which is done");
                return **cur;
            }
    };

    class ConstIterator {
        friend class NotesManager;
        Note** cur;
        unsigned int nbRemain;
        ConstIterator(Note** n, unsigned int nb):cur(n),nbRemain(nb){}
    public:
        ConstIterator():cur(0),nbRemain(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw NotesException("error, next on an iterator which is done");
                nbRemain--;
                cur++;
            }
        const Note& current() const {
            if (isDone())
                throw NotesException("error, indirection on an iterator which is done");
                return **cur;
            }
    };
*/


};


#endif // NOTEMANAGER_H
