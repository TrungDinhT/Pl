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

}

GlobalInterface::modifierNote(Note n){
  delete NI;
  NIE = new NoteInterfaceEditable(n);
  principale.addWidget(NIE);
}
GlobalInterface::sauverNote(Note n){
  delete NIE;
  NI = new NoteInterface(n);
  principale.addWidget(NI);
}
GlobalInterface::supprimerNote(){
//à completer
}
GlobalInterface::miseEnRelationNote(){
//à completer
}
