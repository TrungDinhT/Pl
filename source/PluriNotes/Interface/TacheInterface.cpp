#include "TacheInterface.h"
#include "ImageInterface.h"
#include "RelationManager/RelationManager.h"
#include "RelationManager/relation.h"
#include <QRegExp>
#include <QSet>
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"


TacheInterfaceEditable::TacheInterfaceEditable(const QString id, const Tache *t):NoteInterfaceEditable(t,id){
    tache = t;
    action = new QTextEdit(t->getAction());
    priorite = new QSpinBox;
    priorite->setRange(0,1000);
    priorite->setValue(t->getPriorite());
    statut = new QComboBox;
    statut->addItem("en attente");
    statut->addItem("en cours");
    statut->addItem("terminé");

    statut->setCurrentIndex(t->getStatut());
    dateEcheance = new QDateTimeEdit(t->getDateEcheance());
    QVBoxLayout* principale;
    principale = new QVBoxLayout(this) ;
    principale->addWidget(titre);
    principale->addWidget(action);
    principale->addWidget(priorite);
    principale->addWidget(statut);
    principale->addWidget(dateEcheance);

    principale->addWidget(save);
    principale->addWidget(supprimer);
    principale->addWidget(addRela);
    principale->addWidget(changerversion);
    principale->addWidget(rendreversionactive);
    this->setLayout(principale);
}

void TacheInterfaceEditable::ajouteReference() const {
    NotesManager& notemanager2 = NotesManager::getManager();
    RelationsManager& relaman2 = RelationsManager::getInstance();
    QSet<QString> listeRef;
    QRegExp regex("\\\\ref[{]([\\w]+)[}]");
    bool suite = false;
    qDebug()<<"ajoute ref---\n";
    for(int pos=0; (pos=regex.indexIn(action->toPlainText(), pos)) != -1; pos += regex.matchedLength())
    {
        if(notemanager2.load(regex.cap(1)) && regex.cap(1)!=id)
        {
            qDebug() << "id ref: ";
            qDebug() << regex.cap(1)<<"\n";
            listeRef.insert(regex.cap(1));
            suite = true;
        }
    }
    for(int pos=0; (pos=regex.indexIn(titre->text(), pos)) != -1; pos += regex.matchedLength())
    {
        if(notemanager2.load(regex.cap(1)) && regex.cap(1)!=id)
        {
            qDebug() << "id ref: ";
            qDebug() << regex.cap(1)<<"\n";
            listeRef.insert(regex.cap(1));
            suite = true;
        }
    }
    if(suite)
    {
        relation* ref = relaman2.getRelation("reference");
        for(relation::Iterator it = ref->begin();it!=ref->end();it++)
        {
            if((*it)->getFromNote()->getId() == id)
            {
                ref->deleteCouple(id,(*it)->getToNote()->getId());
            }
        }
        for(auto it: listeRef)
        {
            ref->addCouple(notemanager2.load(id),notemanager2.load(it),id+"->"+it);
        }
    }
}

void TacheInterfaceEditable::saveNote(){
  int i = statut->currentIndex();
  Tache* t = new Tache(titre->text(),QDateTime::currentDateTime(),dateEcheance->dateTime(),action->toPlainText(),priorite->value(),EtatTache(i));
  ajouteReference();
  emit sauvegarde(t);
}


