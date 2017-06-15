
#include "ArticleInterfaceEditable.h"
#include <QRegExp>
#include <QSet>
#include "RelationManager/RelationManager.h"
#include "RelationManager/relation.h"
#include "NoteManager/NoteManager.h"
#include "NoteManager/notes.h"

NotesManager& notemanager = NotesManager::getManager();
RelationsManager& relaman = RelationsManager::getInstance();

void articleInterfaceEditable::saveNote(){
  Article* a = new Article(titre->text(),text->toPlainText());
  ajouteReference();
  emit sauvegarde(a);
}

articleInterfaceEditable::articleInterfaceEditable(const QString id, const Article *a):NoteInterfaceEditable(a,id){
   article = a;
  if (a == 0){text = new QTextEdit("");}
  else{text = new QTextEdit(article->getText());}
  principale = new QVBoxLayout(this);
  principale->addWidget(titre);
  principale->addWidget(text);
  principale->addWidget(save);
  principale->addWidget(supprimer);
  principale->addWidget(addRela);
  principale->addWidget(changerversion);
  principale->addWidget(rendreversionactive);

  this->setLayout(principale);
}


/*fonction pour ajouter reference
 *quand l'utilisateur entre \ref{id} dans n'importe quel champs de l'note (où on peut avoir texte)
 */
void articleInterfaceEditable::ajouteReference() const {
    QSet<QString> listeRef;
    QRegExp regex("\\\\ref[{]([\\w]+)[}]");
    bool suite = false;
    qDebug()<<"ajoute ref---\n";
    for(int pos=0; (pos=regex.indexIn(text->toPlainText(), pos)) != -1; pos += regex.matchedLength())
    {
        if(notemanager.load(regex.cap(1)) && regex.cap(1)!=id)
        {
            qDebug() << "id ref: ";
            qDebug() << regex.cap(1)<<"\n";
            listeRef.insert(regex.cap(1));
            suite = true;
        }
    }
    for(int pos=0; (pos=regex.indexIn(titre->text(), pos)) != -1; pos += regex.matchedLength())
    {
        if(notemanager.load(regex.cap(1)) && regex.cap(1)!=id)
        {
            qDebug() << "id ref: ";
            qDebug() << regex.cap(1)<<"\n";
            listeRef.insert(regex.cap(1));
            suite = true;
        }
    }
    if(suite)
    {
        relation* ref = relaman.getRelation("reference");
        for(relation::Iterator it = ref->begin();it!=ref->end();it++)
        {
            if((*it)->getFromNote()->getId() == id)
            {
                ref->deleteCouple(id,(*it)->getToNote()->getId());
            }
        }
        for(auto it: listeRef)
        {
            ref->addCouple(notemanager.load(id),notemanager.load(it),id+"->"+it);
        }
    }
}

