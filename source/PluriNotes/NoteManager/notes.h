/* Different types of note (tache, image, article,...) defined here
*/

#ifndef NOTES_H
#define NOTES_H

#include <QString>
#include <QDateTime>
using namespace std;


//class Article;
//class NotesManager;


class articleInterface;

class Note {

private:
    QString id;
    QString title;
    QDateTime dateCreation;
    QDateTime dateModif;
    bool etat; //true = active, false = archive
    //Note** version;

protected:
    void autoSave();
    void setId(const QString i){ id =i; }
    virtual const QString createID() = 0; //different par rapport aux differents types de note

public:
    Note(const QString ti): title(ti), dateCreation(QDateTime::currentDateTime()),
        dateModif(QDateTime::currentDateTime()), etat(true){}

    //lectures
    const QString& getId() const { return id; }
    const QString& getTitle() const { return title; }
    const QDateTime& getDateCreation() const { return dateCreation; }
    const QDateTime& getDateModif() const { return dateModif; }
    bool getEtat() const { return etat; }

    //ecritures
    void setDateModif(const QDateTime dt){ dateModif = dt; }
    void setTitle(const QString& t) { title = t; }
};


class Article : public Note{

private:
    QString text;
    const QString createID(){
        return QString("A" + getDateCreation().toString("dd.MM.yyyy") + getDateCreation().toString("hh:mm:ss")); }
    friend class articleInterface;

public:
    Article(const QString ti, const QString te): Note(ti), text(te){ setId(createID()); }

    //accesseurs
    const QString& getText() const { return text; }
    void setText(const QString& t) { text = t; }
};


class Tache: public Note{

};


class Image: public Note{


};


Note** loadOldVersions();


#endif
