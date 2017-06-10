GlobalInterface::GlobalIterface(){
  NM = getManager();
  iterator<Note, NotesManager> it = NM.beginIt();
  principale = new QHBoxLayout(this);
  NI = new NoteInterface(it.current());
  //RI = new RelationInterface() ;
  //MI = ManagerInterface();
  //TB  =MyQToolbar();

}

GlobalInterface::modifierNote(){
//à completer
}
GlobalInterface::sauverNote(){
//à completer
}
GlobalInterface::supprimerNote(){
//à completer
}
GlobalInterface::miseEnRelationNote(){
//à completer
}
