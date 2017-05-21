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
    Article** articles;
    unsigned int nbArticles;
    unsigned int nbMaxArticles;
    void addArticle(Article* a);
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
    void addArticle(const QString& i, const QString& ti, const QString& te);
public:
    Article& getArticle(const QString& id); // return the article with identificator id (create a new one if it not exists)
    QString getFilename() const { return filename; }
    void setFilename(const QString& f) { filename=f; }
    void load(); // load notes from file filename
    void save() const; // save notes in file filename
    static NotesManager& getManager();
    static void freeManager(); // free the memory used by the NotesManager; it can be rebuild later

    class Iterator {
            friend class NotesManager;
            Article** currentA;
            unsigned int nbRemain;
            Iterator(Article** a, unsigned nb):currentA(a),nbRemain(nb){}
        public:
            Iterator():nbRemain(0),currentA(nullptr){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw NotesException("error, next on an iterator which is done");
                nbRemain--;
                currentA++;
            }
            Article& current() const {
                if (isDone())
                    throw NotesException("error, indirection on an iterator which is done");
                return **currentA;
            }
        };
        Iterator getIterator() {
            return Iterator(articles,nbArticles);
        }

        class ConstIterator {
            friend class NotesManager;
            Article** currentA;
            unsigned int nbRemain;
            ConstIterator(Article** a, unsigned nb):currentA(a),nbRemain(nb){}
        public:
            ConstIterator():nbRemain(0),currentA(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw NotesException("error, next on an iterator which is done");
                nbRemain--;
                currentA++;
            }
            const Article& current() const {
                if (isDone())
                    throw NotesException("error, indirection on an iterator which is done");
                return **currentA;
            }
        };
        ConstIterator getIterator() const {
            return ConstIterator(articles,nbArticles);
        }
};


#endif // NOTEMANAGER_H
