
#include "globalInterface.h"
#include "ArticleInterfaceEditable.h"
#include "ManagerInterface.h"
#include <QWidget>

GlobalInterface::GlobalInterface(): QWidget(){
  principale = new QGridLayout(this);
  /*MI = new ManagerInterface();
  connect(MI->liste_note, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this, SLOT(changerNote(QListWidgetItem*)));
  connect(MI, SIGNAL(refresh()),this, SLOT(raffraichissementMI()));
  principale->addWidget(MI,0,0);*/
  raffraichissementMI();
  NM = &(NotesManager::getManager());
  NotesManager::Iterator itn = NM->begin();
  NoteCurrent = *itn;
  /*Note::Iterator itv = NoteCurrent->begin();
  VersionCurrent = *itv;*/
  VersionCurrent = NoteCurrent->VersionActive();

  //if(typeid(*VersionCurrent).name()=="Article"){
  NIE = new articleInterfaceEditable(static_cast <Article*>(VersionCurrent));
  //}

  principale->addWidget(NIE,0,1);
  //qDebug()<<"ajout article\n";

  //RI = new RelationInterface() ;

  //TB  =MyQToolbar();
  connect(NIE,SIGNAL(sauvegarde(Version*)),this,SLOT(sauverNote(Version*)));
  connect(NIE->relier,SIGNAL(clicked()),this,SLOT(miseEnRelationNote()));
  connect(NIE->supprimer,SIGNAL(clicked()),this,SLOT(supprimerNote()));
  connect(NIE->changerversion,SIGNAL(clicked()),this,SLOT(changerVersionNote()));
  connect(NIE->rendreversionactive,SIGNAL(clicked()),this,SLOT(versionActiveNote()));

}

void GlobalInterface::raffraichissementMI(){
    qDebug()<<"raffraichissement\n";
    MI = new ManagerInterface();
    connect(MI->liste_note, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this, SLOT(changerNote(QListWidgetItem*)));
    connect(MI, SIGNAL(refresh()),this, SLOT(raffraichissementMI()));
    connect(MI->sauvegarder, SIGNAL(clicked()),this, SLOT(sauvegardeGeneral()));
    principale->addWidget(MI,0,0);
}

/*
void GlobalInterface::modifierNote(){
  delete NI;
  NIE = new NoteInterfaceEditable(VersionCurrent);
  principale->addWidget(NIE,0,1);
  //connect(NIE->save,SIGNAL(clicked()),this,SLOT(sauverNote()));
  connect(NIE,SIGNAL(sauvegarde(Version*)),this,SLOT(sauverNote(Version*)));
}*/
void GlobalInterface::sauverNote(Version* v){
  //article->getText() = texte.text;
  //article.actualiserDateModif(); //à définir
  //articleInterface a = new articleInterface(article);

    VersionCurrent = v;
    NoteCurrent->addVersion(v);
    NoteCurrent->setVersionActive(v);

  /*delete NIE;
  NIE = new articleInterfaceEditable(static_cast <Article*>(VersionCurrent));
  qDebug()<<"test2";
  principale->addWidget(NIE,0,2);
  qDebug()<<"test3";
  connect(NIE,SIGNAL(sauvegarde(Version*)),this,SLOT(sauverNote(Version*)));
  connect(NIE->relier,SIGNAL(clicked()),this,SLOT(miseEnRelationNote()));
  connect(NIE->supprimer,SIGNAL(clicked()),this,SLOT(supprimerNote()));
  connect(NIE->changerversion,SIGNAL(clicked()),this,SLOT(changerVersionNote()));
  connect(NIE->rendreversionactive,SIGNAL(clicked()),this,SLOT(versionActiveNote()));*/

}
void GlobalInterface::supprimerNote(){
//à completer
}

void GlobalInterface::sauvegardeGeneral(){
    qDebug()<<"save";
    NM->save();
}

void GlobalInterface::miseEnRelationNote(){
//à completer
}

void GlobalInterface::changerVersionNote(){
    qDebug()<<"changement version\n";
    liste = new QListWidget();
    //VersionCurrent = *itv;
    for(Note::Iterator itv = NoteCurrent->begin();itv!= NoteCurrent->end();itv++){
        liste->addItem((*itv)->getDateModif().toString("dd.MM.yyyy-hh:mm:ss"));
    }
    connect(liste, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this, SLOT(choixVersionNote(QListWidgetItem*)));
    liste->show();
    qDebug()<<"fin changement version\n";
}
void GlobalInterface::choixVersionNote(QListWidgetItem* item){
    qDebug()<<"choix version\n";
    VersionCurrent = NoteCurrent->getVerParDate(item->text());
    //NoteCurrent->setVersionActive(VersionCurrent);
    delete NIE;
    NIE = new articleInterfaceEditable(static_cast <Article*>(VersionCurrent));
    connect(NIE,SIGNAL(sauvegarde(Version*)),this,SLOT(sauverNote(Version*)));
    connect(NIE->relier,SIGNAL(clicked()),this,SLOT(miseEnRelationNote()));
    connect(NIE->supprimer,SIGNAL(clicked()),this,SLOT(supprimerNote()));
    connect(NIE->changerversion,SIGNAL(clicked()),this,SLOT(changerVersionNote()));
    connect(NIE->rendreversionactive,SIGNAL(clicked()),this,SLOT(versionActiveNote()));
    principale->addWidget(NIE,0,1);
    liste->close();
    //liste->hide();
    //delete liste;
    qDebug()<<"fin choix version\n";
}

void GlobalInterface::changerNote(QListWidgetItem* item){
 delete NIE;
 NoteCurrent = NM->load(item->text());//item contient ID
 /*Note::Iterator itv = NoteCurrent->begin();
 VersionCurrent = *itv;*/
 VersionCurrent = NoteCurrent->VersionActive();
 NIE = new articleInterfaceEditable(static_cast <Article*>(VersionCurrent));
 connect(NIE,SIGNAL(sauvegarde(Version*)),this,SLOT(sauverNote(Version*)));
 connect(NIE->relier,SIGNAL(clicked()),this,SLOT(miseEnRelationNote()));
 connect(NIE->supprimer,SIGNAL(clicked()),this,SLOT(supprimerNote()));
 connect(NIE->changerversion,SIGNAL(clicked()),this,SLOT(changerVersionNote()));
 connect(NIE->rendreversionactive,SIGNAL(clicked()),this,SLOT(versionActiveNote()));
 principale->addWidget(NIE,0,1);
}
void GlobalInterface::versionActiveNote(){
    NoteCurrent->setVersionActive(VersionCurrent);
}
