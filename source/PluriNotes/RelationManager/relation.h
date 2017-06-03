#ifndef RELATION_H
#define RELATION_H

#include "NoteManager/notes.h"
#include <QString>

class couple{
    Note* fromNote;
    Note* toNote;

public:
    couple(Note* fn, Note* tn): fromNote(fn), toNote(tn){}
    const Note& getFromNote() const { return *fromNote; }
    const Note& getToNote() const { return *toNote; }
};

class relationException{

};

class relation{
protected:
    QString titre;
    QString description;
    bool oriente;
    couple** couples;
    unsigned int nbCouples;
    unsigned int nbMaxCouples;
    void addCouple(couple*c);
    void deleteCouple(couple* c);

public:
    relation(const QString& ti, const QString& desc, Note* fn, Note* tn, bool ori=true):
        titre(ti), description(desc), nbCouples(1), nbMaxCouples(10), oriente(ori)
    {
        couples = new couple*[nbMaxCouples];
        addCouple(new couple(fn,tn));
    }
    virtual ~relation(){
        for (unsigned int i=0;i<nbCouples;i++)
             delete couples[i];
        delete[] couples;
    }

    //accesseurs
    const QString& getTitre() const { return titre; }
    virtual void setTitre(const QString& ti) =0;
    const QString& getDescription() const { return description; }
    virtual void setDescription(const QString& d) =0;
    bool getOriente() const { return oriente; }
    virtual void setOriente(bool ori) =0;

    class iterator<couple,relation>;

};

class relationNonPreexistance: public relation{
public:
    void setTitre(const QString& ti) { return ti;}
    void setDescription(const QString& d) { return description; }
    void setOriente(bool ori) { oriente = ori; }
    relationNonPreexistance(const QString& ti, const QString& desc, Note* fn, Note* tn, bool ori=true):
        relation(ti,desc,fn,tn,ori){}
};


class relationPreexistance: public relation{
private:
    void setTitre(const QString& ti) { return ti;}
    void setDescription(const QString& d) { return description; }
    void setOriente(bool ori) { oriente = ori; }

    static relationPreexistance* instance;
    relationPreexistance(): relation("reference","reference vers une note",nullptr,nullptr){}
    relationPreexistance(const relationPreexistance& re){}
    relationPreexistance& operator=(const relationPreexistance& re){}
    ~relationPreexistance(){}
public:
    static relationPreexistance* getInstance();
    static void freeInstance();

};


#endif // RELATION_H
