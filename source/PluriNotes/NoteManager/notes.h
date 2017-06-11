/* Different types of note (tache, image, article,...) defined here

  classe Note abstrait grace au methode createID() = 0;
  ID inmodifiable et creee automatiquement par combiner le type de note ("A"=article,"I"=image,"T"=tache)

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
#include <QtWidgets>
#include "iterator.h"

using namespace std;

enum EtatTache {EN_ATTENTE, EN_COURS, TERMINE};
enum EtatNote {ARCHIVE, ACTIVE, RIP};

class articleInterface;

class Version;

class Note {
private:
    QDateTime dateCreation;
    QString id;
    EtatNote etat;
    Version** versions;
    unsigned int nbVer;
    unsigned int nbMaxVer;
public:
    Note(const QString& id): dateCreation(QDateTime::currentDateTime()), id(id),
        etat(ACTIVE), versions(nullptr), nbVer(0), nbMaxVer(0){}
    Note(const QDateTime dC, const QString id, EtatNote etat):
        dateCreation(dC),id(id),etat(etat),versions(nullptr),nbVer(0),nbMaxVer(0){}
    //lectures
    const QString& getId() const { return id; }
    const QDateTime& getDateCreation() const { return dateCreation; }
    const EtatNote getEtat() const { return etat; }
    ~Note(){
        for(unsigned int i=0;i<nbVer;i++) delete versions[i];
        delete[] versions;
    }
    void addVersion(Version* v);
    Note* getNewNote(const QString& id, Version *v);
    Version* getVer(const QString& titre);

    //iterator + methodes servent a parcourir
    class Iterator: public _Iterator<Version>{
        friend class Note;
        Iterator(Version** v, unsigned int n): _Iterator(v,n){}
    };
    Iterator begin() const { return Iterator(versions,nbVer); }
    Iterator end() const { return Iterator(versions + nbVer,nbVer); }
    class Const_Iterator: public _const_iterator<Version>{
        friend class Note;
        Const_Iterator(Version** v, unsigned int n): _const_iterator(v,n){}
    };
    Const_Iterator cbegin() const { return Const_Iterator(versions,nbVer); }
    Const_Iterator cend() const { return Const_Iterator(versions + nbVer,nbVer); }

    void save(QXmlStreamWriter& stream) const;
};

class Version {

protected:
    QString titre;
    QDateTime dateModif;

protected:
    void autoLoad();

public:
    Version(const QString& titre=""): titre(titre),dateModif(QDateTime::currentDateTime()){}
    Version(const QString titre, const QDateTime dM): titre(titre),dateModif(dM){}
    const QDateTime& getDateModif() const { return dateModif; }
    QString getTitre() const {return titre;}
    void setTitre(const QString& t){titre=t;}
    virtual void save(QXmlStreamWriter& stream) const = 0;
};

class Article : public Version{

private:
    QString text;
    friend class articleInterface;
public:
    Article(const QString ti, const QDateTime d, const QString te): Version(ti,d), text(te) {}
    Article(const QString te=""): Version(),text(te){}

    //accesseurs
    const QString& getText() const { return text; }
    void setText(const QString& t) { text = t; }

    void save(QXmlStreamWriter& stream) const;
};

class Image: public Version{
  private:
    QString description;
    QString nomFichier;
    //friend class imageInterface;

public:
    Image(const QString ti, const QDateTime d, const QString& f, const QString desc=""): Version(ti,d), description(desc), nomFichier(f){}
    Image(const QString& f, const QString desc=""): description(desc), nomFichier(f){}

    //accesseurs
    const QString& getDesc() const { return description; }
    const QString& getNomFichier() const { return nomFichier; }
    void setDesc(const QString& d) { description = d; }

    void save(QXmlStreamWriter& str) const;
};


class Tache: public Version{
private:
    QString action;
    unsigned int priorite;
    EtatTache statut;
    QDateTime dateEcheance;
public:
    Tache(const QDateTime& dE, const QString& action ="", const int p= 0, const EtatTache e = EN_COURS):
        Version(),action(action),priorite(p),statut(e),dateEcheance(dE){}  //Une priorité faible=0
    Tache(const QString ti, const QDateTime d, const QDateTime& dE, const QString& action ="", const int p= 0, const EtatTache e = EN_COURS):
        Version(ti,d),action(action),priorite(p),statut(e),dateEcheance(dE){}  //Une priorité faible=0

    //accesseurs
    const QString& getAction() const { return action; }
    const int getPriorite() const { return priorite; }
    const QDateTime& getDateEcheance() const { return dateEcheance; }
    const EtatTache getStatut() const { return statut; }
    void setAction(const QString& a) { action = a; }  
    void setPriorite(const int p) { priorite = p; }
    void setDateEcheance(const QDateTime& d) { dateEcheance = d; }
    void setStatut(const EtatTache s) {statut = s; }

    void save(QXmlStreamWriter& str) const;
};


#endif
