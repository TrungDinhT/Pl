#ifndef NOTES_H
#define NOTES_H

#include <QString>
#include <QDateTime>
#include <QtWidgets>
#include "iterator.h"
#include "Interface/ArticleInterfaceEditable.h"
#include "Interface/TacheInterface.h"
#include "Interface/ImageInterface.h"
#include "Interface/NoteInterfaceEditable.h"

using namespace std;

enum EtatTache {EN_ATTENTE, EN_COURS, TERMINE};
enum EtatNote {ARCHIVE, ACTIVE, RIP};
enum Media {VIDEO, AUDIO, IMAGE};

class Version {
protected:
    QString titre;
    QDateTime dateModif;
public:
    Version(const QString& titre=""): titre(titre),dateModif(QDateTime::currentDateTime()){}
    Version(const QString titre, const QDateTime dM): titre(titre),dateModif(dM){}
    const QDateTime& getDateModif() const { return dateModif; }
    QString getTitre() const {return titre;}
    void setTitre(const QString& t){titre=t;}
    virtual void save(QXmlStreamWriter& stream) const = 0;
    virtual NoteInterfaceEditable* creerInterface(const QString& id) const =0;
    virtual void afficher(QString& contenu) const = 0;
    virtual ~Version(){}
};

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
    ~Note(){
        for(unsigned int i=0;i<nbVer;i++) delete versions[i];
        delete[] versions;
    }
    const QString& getId() const { return id; }
    const QDateTime& getDateCreation() const { return dateCreation; }
    const EtatNote& getEtat() const { return etat; }
    void setEtat(const EtatNote status) { etat = status; }
    void addVersion(Version* v);
    void setVersionActive(Version* v);
    Version* VersionActive();
    static Note* getNewNote(const QString& id, Version *v);
    Version* getVer(const QString& titre);
    Version* getVerParDate(const QString& date);
    void save(QXmlStreamWriter& stream) const;
    void afficher(QString& contenu) const ;

    /** iterator.
     * On parcours publiquement tous les versions dans une note par iterator
     */
    class Iterator: public _Iterator<Version>{
        friend class Note;
        Iterator(Version** v, unsigned int n): _Iterator(v,n){}
    public:
        Iterator(): _Iterator(){}
    };
    Iterator begin() const { return Iterator(versions,nbVer); }
    Iterator end() const { return Iterator(versions + nbVer,nbVer); }

    class Const_Iterator: public _const_iterator<Version>{
        friend class Note;
        Const_Iterator(Version** v, unsigned int n): _const_iterator(v,n){}
    public:
        Const_Iterator(): _const_iterator(){}
    };
    Const_Iterator cbegin() const { return Const_Iterator(versions,nbVer); }
    Const_Iterator cend() const { return Const_Iterator(versions + nbVer,nbVer); }
};


class Article : public Version{
private:
    QString text;
    friend class articleInterface;
public:
    Article(const QString ti, const QDateTime d, const QString te): Version(ti,d), text(te) {}
    Article(const QString ti="", const QString te=""): Version(ti),text(te){}

    const QString& getText() const { return text; }
    void setText(const QString& t) { text = t; }
    void save(QXmlStreamWriter& stream) const;
    NoteInterfaceEditable* creerInterface(const QString& id) const{
        return new articleInterfaceEditable(id,this);
    }
    void afficher(QString &contenu) const;
};

class Multimedia: public Version{
private:
    QString description;
    QString nomFichier;
    Media typeEnregistrement;
public:
    Multimedia(const QString ti, const QDateTime d, const QString& f, const QString desc=""): Version(ti,d), description(desc), nomFichier(f){}
    Multimedia(const QString& f = "", const QString desc=""): Version(),description(desc), nomFichier(f){}

    const QString& getDesc() const { return description; }
    const QString& getNomFichier() const { return nomFichier; }
    const Media& getType() const { return typeEnregistrement; }
    void setDesc(const QString& d) { description = d; }
    void setType(const Media type) { typeEnregistrement = type; }
    void setPath(const QString& f) { nomFichier = f; }
    void save(QXmlStreamWriter& str) const;
    void afficher(QString &contenu) const;
    NoteInterfaceEditable* creerInterface(const QString& id) const{
        return new MultimediaInterfaceEditable(id,this);
    }
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
    Tache(const QString ti = "", const QDateTime d = QDateTime::currentDateTime(), const QDateTime& dE = QDateTime::currentDateTime().addDays(1), const QString& action ="", const int p= 0, const EtatTache e = EN_COURS):
        Version(ti,d),action(action),priorite(p),statut(e),dateEcheance(dE){}  //Une priorité faible=0

    const QString& getAction() const { return action; }
    const unsigned int& getPriorite() const { return priorite; }
    const QDateTime& getDateEcheance() const { return dateEcheance; }
    const EtatTache& getStatut() const { return statut; }
    void setAction(const QString& a) { action = a; }  
    void setPriorite(const unsigned int p) { priorite = p; }
    void setDateEcheance(const QDateTime& d) { dateEcheance = d; }
    void setStatut(const EtatTache s) {statut = s; }
    void afficher(QString &contenu) const;
    void save(QXmlStreamWriter& str) const;
    NoteInterfaceEditable* creerInterface(const QString& id) const{
        return new TacheInterfaceEditable(id,this);
    }
};

#endif
