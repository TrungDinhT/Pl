/* Different types of note (tache, image, article,...) defined here

  classe Note abstrait grace au methode createID() = 0;
  ID inmodifiable et creee automatiquement par combiner le type de note ("A"=article,"I"=image,"T"=tache)

  tableau de version de note n'est pas encore traite!!!
  -- Suggestion: utiliser vector pour ne pas devoir implementer 2 classes de Iterator
  -- Peut-etre il faut casting les pointeurs dans version pour des traitement ulterieur

  Gestion des versions ne sont pas encore traitee non plus!!!
  -- Different versions de note ont les meme ID, dateCreation mais different dateModif
  -- Je choisis a sauvegarder tous les versions dans un seul fichier xml (sauf les images mais on les traitera apres)
       => il faut avoir le methode autoLoad() qui serve a charger, creer tous les versions d'une note (au lancement de notre app)

  Il y a surement des problemes auxquelles j'avais pas encore pense

*/

#ifndef NOTES_H
#define NOTES_H

#include <QString>
#include <QDateTime>
using namespace std;



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
    void autoLoad();
    void setId(const QString& i){ id =i; }
    virtual const QString createID() = 0; //different par rapport aux differents types de note

public:
    Note(const QString& ti): title(ti), dateCreation(QDateTime::currentDateTime()),
        dateModif(QDateTime::currentDateTime()), etat(true){}
    virtual ~Note(){}
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
        return QString("A-" + getDateCreation().toString("dd.MM.yyyy-hh:mm:ss")); }
    friend class articleInterface;

public:
    Article(const QString& ti="", const QString& te="");
    Article(const QString& i, const QString& ti="", const QString& te="");

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
