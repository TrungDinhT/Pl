#include "ImageInterface.h"
#include "NoteManager/NoteManager.h"
#include "RelationManager/RelationManager.h"
#include "RelationManager/relation.h"
#include <QRegExp>
#include <QSet>

#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"

MultimediaInterfaceEditable::MultimediaInterfaceEditable(const QString id, const Multimedia *m):NoteInterfaceEditable(m,id){
    multimedia = m;
    description = new QTextEdit(m->getDesc());
    changer_media = new QPushButton("changer le contenu");
    chemin = m->getNomFichier();
    image = new QPixmap(m->getNomFichier());
    im = new QLabel;
    im->setPixmap(*image);
    im->setScaledContents(true);
    principale = new QVBoxLayout(this) ;
    principale->addWidget(titre);
    //principale->addWidget(image);


    principale->addWidget(im);
    principale->addWidget(description);
    principale->addWidget(changer_media);
    principale->addWidget(save);
    principale->addWidget(supprimer);
    principale->addWidget(relier);
    principale->addWidget(changerversion);
    principale->addWidget(rendreversionactive);
    connect(changer_media,SIGNAL(clicked()),this,SLOT(changer_chemin()));
    this->setLayout(principale);
}

void MultimediaInterfaceEditable::ajouteReference() const {
    NotesManager& notemanager2 = NotesManager::getManager();
    RelationsManager& relaman2 = RelationsManager::getInstance();
    QSet<QString> listeRef;
    QRegExp regex("\\\\ref[{]([\\w]+)[}]");
    bool suite = false;
    qDebug()<<"ajoute ref---\n";
    for(int pos=0; (pos=regex.indexIn(description->toPlainText(), pos)) != -1; pos += regex.matchedLength())
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

void MultimediaInterfaceEditable::saveNote(){
  Multimedia* m = new Multimedia(titre->text(),QDateTime::currentDateTime(),chemin,description->toPlainText());
  ajouteReference();
  emit sauvegarde(m);
}


void MultimediaInterfaceEditable::changer_chemin(){
//
}
