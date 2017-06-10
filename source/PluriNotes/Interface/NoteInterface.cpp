NoteInterface::NoteInterface(Note n){
  titre = new QLabel(n->titre);
//titre = new QLabel(n->titre,this);
  modifier = new QPushbutton("modifier");
  supprimer = new QPushbutton("supprimer");
  relier = new QPushbutton("relier");
//connect(modifier,SIGNAL(clicked()),this,SLOT(modifArticle()));

}
