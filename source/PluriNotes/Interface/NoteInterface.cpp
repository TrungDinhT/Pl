NoteInterface::NoteInterface(Version v){
  titre = new QLabel(v->titre);
//titre = new QLabel(v->titre,this);
  modifier = new QPushbutton("modifier");
  supprimer = new QPushbutton("supprimer");
  relier = new QPushbutton("relier");
//connect(modifier,SIGNAL(clicked()),this,SLOT(modifArticle()));

}
