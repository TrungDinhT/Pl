
#include "globalInterface.h"
#include "ArticleInterfaceEditable.h"
#include "ImageInterface.h"
#include "ManagerInterface.h"
#include "TacheInterface.h"

#include <QWidget>


GlobalInterface::GlobalInterface(): QWidget(){
  principale = new QGridLayout(this);
  MI = new ManagerInterface;
  raffraichissementMI();
  NM = &(NotesManager::getManager());
  RM = &(RelationsManager::getInstance());
  NotesManager::Iterator itn = NM->begin();

  NoteCurrent = *itn;
  VersionCurrent = NoteCurrent->VersionActive();
  NIE = VersionCurrent->creerInterface(NoteCurrent->getId());
  principale->addWidget(NIE,0,1);

  this->setMinimumSize(600,600);

  connect(NIE,SIGNAL(sauvegarde(Version*)),this,SLOT(sauverNote(Version*)));
  connect(NIE->addRela,SIGNAL(clicked()),this,SLOT(miseEnRelationNote()));
  connect(NIE->supprimer,SIGNAL(clicked()),this,SLOT(supprimerNote()));
  connect(NIE->changerversion,SIGNAL(clicked()),this,SLOT(changerVersionNote()));
  connect(NIE->rendreversionactive,SIGNAL(clicked()),this,SLOT(versionActiveNote()));
}


void GlobalInterface::raffraichissementMI(){
    qDebug()<<"raffraichissement\n";
    MI = new ManagerInterface;
    connect(MI->liste_note, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this, SLOT(changerNote(QListWidgetItem*)));
    connect(MI, SIGNAL(refresh()),this, SLOT(raffraichissementMI()));
    connect(MI->rafrachir,SIGNAL(clicked()),this,SLOT(raffraichissementMI()));
    connect(MI->c,SIGNAL(refreshCor()),this,SLOT(raffraichissementMI()));
    connect(MI->sauvegarder, SIGNAL(clicked()),this, SLOT(sauvegardeGeneral()));
    principale->addWidget(MI,0,0);
}


void GlobalInterface::sauverNote(Version* v){
    VersionCurrent = v;
    NoteCurrent->addVersion(v);
    NoteCurrent->setVersionActive(v);
}

void GlobalInterface::supprimerNote(){
    qDebug()<<"delete Item\n";
    QString idDel = MI->liste_note->currentItem()->text();
    NM->deleteNote(idDel);
    qDebug()<<"idDel (view Interface): "<<idDel<<"\n";
    raffraichissementMI();
}

void GlobalInterface::sauvegardeGeneral(){
    qDebug()<<"save";
    NM->save();
    RM->save();
}

void GlobalInterface::miseEnRelationNote(){
    QVBoxLayout* lay = new QVBoxLayout;
    listRela = new QListWidget;
    for(RelationsManager::Iterator it = RM->begin();it!=RM->end();it++)
    {
        listRela->addItem((*it)->getTitre());
    }
    AfficherRela = new QPushButton("afficher couples");
    lay->addWidget(listRela);
    lay->addWidget(AfficherRela);
    principale->addLayout(lay,0,2);

    connect(AfficherRela,SIGNAL(clicked()),this,SLOT(afficherCouple()));
}

void GlobalInterface::afficherCouple(){
    QDialog* boxCouples = new QDialog;
    QHBoxLayout* lay = new QHBoxLayout;
    QTextEdit* conCouples = new QTextEdit;
    conCouples->setReadOnly(true);
    conCouples->setFont(QFont("Courier"));
    conCouples->setLineWrapMode(QTextEdit::NoWrap);
    QString couples;
    relation* r = RM->getRelation(listRela->currentItem()->text());
    for(relation::Iterator it = r->begin();it!=r->end();it++)
    {
        couples+= (*it)->label + "\n";
    }
    conCouples->setPlainText(couples);
    lay->addWidget(conCouples);
    boxCouples->setLayout(lay);
    boxCouples->exec();
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
    delete NIE;
    NIE = VersionCurrent->creerInterface(NoteCurrent->getId());
    connect(NIE,SIGNAL(sauvegarde(Version*)),this,SLOT(sauverNote(Version*)));
    connect(NIE->addRela,SIGNAL(clicked()),this,SLOT(miseEnRelationNote()));
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
    NIE = VersionCurrent->creerInterface(NoteCurrent->getId());
 connect(NIE,SIGNAL(sauvegarde(Version*)),this,SLOT(sauverNote(Version*)));
 connect(NIE->addRela,SIGNAL(clicked()),this,SLOT(miseEnRelationNote()));
 connect(NIE->supprimer,SIGNAL(clicked()),this,SLOT(supprimerNote()));
 connect(NIE->changerversion,SIGNAL(clicked()),this,SLOT(changerVersionNote()));
 connect(NIE->rendreversionactive,SIGNAL(clicked()),this,SLOT(versionActiveNote()));
 principale->addWidget(NIE,0,1);
}
void GlobalInterface::versionActiveNote(){
    NoteCurrent->setVersionActive(VersionCurrent);
}
