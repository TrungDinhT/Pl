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


class Image: public Note{
  private:
    QString description;
    QString nomFichier;
    const QString createID(){
        return QString("A-" + getDateCreation().toString("dd.MM.yyyy-hh:mm:ss")); }
    //friend class imageInterface;

public:
    Image(const QString& f, const QString& ti="", const QString& d="");
    Image(const QString& i, const QString& f, const QString& ti="", const QString& d="");

    //accesseurs
    const QString& getDesc() const { return description; }
    void setDesc(const QString& d) { description = d; }
};


class Tache: public Note{
  private:
    QString action;
    int priorite;
    etat statut;
    QDateTime dateEcheance;
    const QString createID(){
        return QString("A-" + getDateCreation().toString("dd.MM.yyyy-hh:mm:ss")); }
    //friend class tacheInterface;

public:
    Tache(const QString& action ="", const QString& ti="", const int p= 0, const QDateTime& d = QDateTime::currentDateTime(), );  //Une priorité faible=0
    Tache(const QString& i, const QString& action ="", const QString& ti="", const int& p= 0, const QDateTime& d = QDateTime::currentDateTime(), );  //Une priorité faible=0

    //accesseurs
    const QString& getAction() const { return action; }
    const int getPriorite() const { return priorite; }
    const QDateTime& getDateEcheance() const { return dateEcheance; }
    const etat getStatut() const { return statut; }
    void setAction(const QString& a) { action = a; }  
    void setPriorite(const int p) { priorite = p; }
    void setDateEcheance(const QDateTime& d) { dateEcheance = d; }
    void setStatut(const etat s) {statut = s; }
};


Note** loadOldVersions();


#endif
