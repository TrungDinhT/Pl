/* Different types of note (tache, image, article,...) defined here
*/

#ifndef NOTES_H
#define NOTES_H

#include <QString>
#include <QDateTime>


using namespace std;


//class Article;
//class NotesManager;

class Note;

Note** loadOldVersions();



class Note {

private:
    QString id;
    QString title;
    QDateTime dateCreation;
    QDateTime dateModif;
    Note** version;
    bool etat; //true = active, false = archive
    void autoSave();
    virtual QString setId() = 0; //different par rapport aux differents types de note

public:
    Note(const QString ti): id(setId()), title(ti), dateCreation(QDateTime::currentDateTime()),
        dateModif(QDateTime::currentDateTime()), etat(true), version(loadOldVersions()){}

    //lectures
    const QString& getId() const { return id; }
    const QString& getTitle() const { return title; }
    const QDateTime& getDateCreation() const { return dateCreation; }
    const QDateTime& getDateModif() const { return dateModif; }
    //ecritures
    void setTitle(const QString& t);
};


class Article : public Note{

private:
    QString text;
    QString setId();

public:
    Article(const QString ti, const QString te): Note(ti), text(te){}

    const QString& getText() const { return text; }
    void setText(const QString& t) { text = t; }
};


class Tache: public Note{

};


class Image: public Note{


};

#endif
