/*Pour generaliser les types de note, factory method ou adapter?
*/



#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include "notes.h"

class NotesException{
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};


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

    //filename a manager
    mutable QString filename;


    struct Handler {
        NotesManager* instance; // pointeur sur l'unique instance
        Handler():instance(nullptr){}
        ~Handler() { delete instance; }
    };
    static Handler handler;
    NotesManager();
    ~NotesManager();
    NotesManager(const NotesManager& m);
    NotesManager& operator=(const NotesManager& m);

public:
    /*besoin de generaliser pour Notes
    Article* getArticle(const QString& id); // return the article with identificator id
    Article* getNewArticle();  //create a new article
    */

    Note* getNote(const QString& id);
    Note* getNewNote(char type);

    QString getFilename() const { return filename; }
    void setFilename(const QString& f) { filename=f; }
    void load(); // load notes from file filename
    void save(Note *a) const; // save a specific note in a specific file filename
    static NotesManager& getManager();
    static void freeManager(); // free the memory used by the NotesManager; it can be rebuild later


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


};


#endif // NOTEMANAGER_H
