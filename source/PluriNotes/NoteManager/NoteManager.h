#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include "notes.h"
#include "iterator.h"
#include "exception.h"

class corbeille;

class NotesManager {

private:
    Note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;


    /** filename à enregistrer les notes.
     * On enregistre tous les notes dans une structure xml dans le fichier noteslog.xml
     * Il faut créer en avant ce fichier dans le bureau
     */
    mutable QString filename;

    static NotesManager* instance; ///< pointeur sur l'unique instance
    NotesManager():notes(nullptr),nbNotes(0),nbMaxNotes(0),filename(""){}
    ~NotesManager();
    NotesManager(const NotesManager& m);
    NotesManager& operator=(const NotesManager& m);
    friend class corbeille;
public:

    void addNotes(Note* n);
    static NotesManager& getManager();
    static void freeManager(); ///< free the memory used by the NotesManager; it can be rebuild later

    /** code pour la corbeille.
     * On utilise le Notesmanager pour gérer la corbeille aussi
     */
    void deleteNote(const QString& id);
    void restaurerNote(const QString& id);
    void reallyDeleteNote(const QString& id);
    void viderCorbeille();

    void afficher(const QString& idNoteAfficher, QString& contenu) const;

    QString getFilename() const { return filename; }
    void setFilename(const QString& f) { filename=f; }
    void load(); ///< load all notes
    Note* load(const QString& id);
    void save() const; ///< save all notes (at the beginning)
    void save(const QString& id, Version* v); ///< create a note in array notes

    /** iterator.
     * On parcours publiquement tous les notes par iterator
     */
    class Iterator: public _Iterator<Note>{
        friend class NotesManager;
        Iterator(Note** notes, unsigned int n): _Iterator(notes,n){}
    public:
        Iterator(): _Iterator(){}
    };
    Iterator begin() const { return Iterator(notes,nbNotes); }
    Iterator end() const { return Iterator(notes + nbNotes,nbNotes); }

    class Const_Iterator: public _const_iterator<Note>{
        friend class NotesManager;
        Const_Iterator(Note** notes, unsigned int n): _const_iterator(notes,n){}
    public:
        Const_Iterator(): _const_iterator(){}
    };
    Const_Iterator cbegin() const { return Const_Iterator(notes,nbNotes); }
    Const_Iterator cend() const { return Const_Iterator(notes + nbNotes,nbNotes); }

};


#endif // NOTEMANAGER_H
