#include "ManagerInterface.h"
#include "ArticleInterfaceEditable.h"



ManagerInterface::ManagerInterface(){
  NM = &(NotesManager::getManager());
  NotesManager::Iterator itn = NM->begin();
  NoteCurrent = *itn;
  principale = new QVBoxLayout(this);
  bouttons = new QHBoxLayout();
  principale->addLayout(bouttons);
  liste_note = new QListWidget();

  c = new corbeilleInterface;

  for(; itn!= NM->end();itn++){
      if((*itn)->getEtat()==ACTIVE)
          liste_note->addItem((*itn)->getId());
  }
  ajouter = new QPushButton("ajouter");
  sauvegarder = new QPushButton("sauvegarder");
  corbeille = new QPushButton("corbeille");
  rafrachir = new QPushButton("raffraichir");
  bouttons->addWidget(ajouter);
  bouttons->addWidget(sauvegarder);
  bouttons->addWidget(corbeille);

  principale->addWidget(liste_note);
  principale->addWidget(rafrachir);
  connect(corbeille,SIGNAL(clicked()),this,SLOT(ouvrirCorbeille()));
  connect(ajouter, SIGNAL(clicked()),this, SLOT(ajoutNote()));
}

void ManagerInterface::ouvrirCorbeille(){
    c->exec();
}


void ManagerInterface::ajoutNote(){
    qDebug()<<"ajout Note\n";
    listeVersion = new QListWidget();

    QVariant vA = qVariantFromValue((void *) new Article);
    //yourPointer = (YourClass *) v.value<void *>();
    QListWidgetItem* a = new QListWidgetItem("Article");
    a->setData(Qt::UserRole,vA);
    listeVersion->addItem(a);
    QVariant vT = qVariantFromValue((void *) new Tache);
    //yourPointer = (YourClass *) v.value<void *>();
    QListWidgetItem* t = new QListWidgetItem("Tache");
    t->setData(Qt::UserRole,vT);
    listeVersion->addItem(t);
    QVariant vM = qVariantFromValue((void *) new Multimedia);
    //yourPointer = (YourClass *) v.value<void *>();
    QListWidgetItem* m = new QListWidgetItem("Multimedia");
    m->setData(Qt::UserRole,vM);
    listeVersion->addItem(m);
    extension_choix_version();

    connect(listeVersion, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this, SLOT(choixAjoutNote(QListWidgetItem*)));
    listeVersion->show();
    qDebug()<<"fin ajout Note\n";
}

void ManagerInterface::choixAjoutNote(QListWidgetItem *item){
    Version* v = (Version *) item->data(Qt::UserRole).value<void *>();
    qDebug()<<"choix Note\n";
    listeVersion->close();
    qDebug()<<"titre : \""<<v->getTitre()<<"\", date modif : \""<<v->getDateModif().toString("dd.MM.yyyy-hh:mm:ss")<<"\", texte : "<<static_cast <Article*>(v)->getText()<<"\n";
    NoteCurrent = Note::getNewNote(QDateTime::currentDateTime().toString("dd.MM.yyyy-hh:mm:ss"),v);
    //delete principale;
    NM->addNotes(NoteCurrent);
    emit refresh();
    qDebug()<<"fin choix Note\n";
}


