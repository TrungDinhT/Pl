#ifndef RELATION_H
#define RELATION_H

#include "NoteManager/notes.h"
#include "iterator.h"
#include <QString>

class couple{
    Note* fromNote;
    Note* toNote;
public:
    QString label; ///< public car on peut le modifier et accéder aussi
    couple(Note* fn, Note* tn, const QString& lab): fromNote(fn), toNote(tn), label(lab){}
    Note* getFromNote() const { return fromNote; }
    Note* getToNote() const { return toNote; }
};

class relation{
protected:
    QString titre;
    QString description;
    bool oriente;
    couple** couples;
    unsigned int nbCouples;
    unsigned int nbMaxCouples;
    void deleteCouple(const QString& idNote);

public:
    void deleteCouple(const QString& idFromNote, const QString& idToNote);
    void addCouple(Note *fn, Note *tn, const QString& lab); ///< public pour pouvoir enrichir une relation
    relation(QString ti, QString desc="", bool ori=true):
        titre(ti), description(desc),oriente(ori),couples(nullptr), nbCouples(0), nbMaxCouples(0) {}
    virtual ~relation(){
        for (unsigned int i=0;i<nbCouples;i++)
             delete couples[i];
        delete[] couples;
    }

    const QString& getTitre() const { return titre; }
    const QString& getDescription() const { return description; }
    bool getOriente() const { return oriente; }
    virtual void setTitre(const QString& ti) =0;
    virtual void setDescription(const QString& d) =0;
    virtual void setOriente(bool ori) =0;

    /** iterator.
     * On parcours publique tous les couple dans une relation par iterator
     */
    class Iterator: public _Iterator<couple>{
        friend class relation;
        Iterator(couple** c, unsigned int n): _Iterator(c,n){}
    public:
        Iterator(): _Iterator(){}
    };
    Iterator begin() const { return Iterator(couples,nbCouples); }
    Iterator end() const { return Iterator(couples + nbCouples,nbCouples); }

    class Const_Iterator: public _const_iterator<couple>{
        friend class relation;
        Const_Iterator(couple** c, unsigned int n): _const_iterator(c,n){}
    public:
        Const_Iterator(): _const_iterator(){}
    };
    Const_Iterator cbegin() const { return Const_Iterator(couples,nbCouples); }
    Const_Iterator cend() const { return Const_Iterator(couples + nbCouples,nbCouples); }

};

class relationNonPreexistance: public relation{
public:
    void setTitre(const QString& ti) { titre = ti;}
    void setDescription(const QString& d) { description = d; }
    void setOriente(bool ori) { oriente = ori; }
    relationNonPreexistance(const QString& ti, const QString& desc, bool ori=true):
        relation(ti,desc,ori){}
};


class relationPreexistance: public relation{
private:
    void setTitre(const QString& ti) final {}
    void setDescription(const QString& d) final {}
    void setOriente(bool ori) final {}

    static relationPreexistance* instance;
    relationPreexistance(): relation("reference","reference vers une note",true){}
    relationPreexistance(const relationPreexistance& re);
    relationPreexistance& operator=(const relationPreexistance& re);
    ~relationPreexistance(){}
public:
    static relationPreexistance& getInstance();
    static void freeInstance();

};


#endif // RELATION_H
