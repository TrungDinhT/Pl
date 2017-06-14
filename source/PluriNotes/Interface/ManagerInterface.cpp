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

  for(; itn!= NM->end();itn++){
      liste_note->addItem((*itn)->getId());
  }
  ajouter = new QPushButton("ajouter");
  sauvegarder = new QPushButton("sauvegarder");
  bouttons->addWidget(ajouter);
  bouttons->addWidget(sauvegarder);

  principale->addWidget(liste_note);

  //connect(liste_note, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this, SLOT(changerNote(QListWidgetItem*)));

  //connect(NIE,SIGNAL(sauvegarde(Version*)),this,SLOT(sauverNote(Version*)));

  //connect(ajouter,SIGNAL(clicked()),this,SLOT(creationNote())); à créer
  //connect(sauvegarder,SIGNAL(clicked()),this,SLOT(sauvegardeNotes()));

}


/*
list_note_item::list_note_item(Note *n):QListWidgetItem(n->get){
    this->setText();
}
*/
