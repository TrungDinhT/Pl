GlobalInterface::GlobalIterface(){
  NM = getManager();
  iterator<Note, NotesManager> it = NM.beginIt();
  principale = new QGridLayout(this);
  NI = new NoteInterface(it.current());
  principale.addWidget(NI,0,1);
  //RI = new RelationInterface() ;
  //MI = ManagerInterface();
  //TB  =MyQToolbar();
  connect(NI->modifier,SIGNAL(clicked()),this,SLOT(modifierNote()));
  connect(NI->relier,SIGNAL(clicked()),this,SLOT(miseEnRelationNote()));
  connect(NI->supprimer,SIGNAL(clicked()),this,SLOT(sypprimerNote()));


}

GlobalInterface::modifierNote(Note n){
  delete NI;
  NIE = new NoteInterfaceEditable(n);
  principale.addWidget(NIE,0,1);
  connect(NI->save,SIGNAL(clicked()),this,SLOT(sauverNote()));
}
GlobalInterface::sauverNote(Note n){
  delete NIE;
  NI = new NoteInterface(n);
  principale.addWidget(NI,0,1);
  connect(NI->modifier,SIGNAL(clicked()),this,SLOT(modifierNote()));
  connect(NI->relier,SIGNAL(clicked()),this,SLOT(miseEnRelationNote()));
  connect(NI->supprimer,SIGNAL(clicked()),this,SLOT(sypprimerNote()));
}
GlobalInterface::supprimerNote(){
//à completer
}
GlobalInterface::miseEnRelationNote(){
//à completer
}
