NoteInterface::NoteInterface(Note n){
titre = new QLabel(n.titre,this);
modifier = new QPushbutton("modifier",this);
supprimer = new QPushbutton("supprimer",this);
relier = new QPushbutton("relier",this);
//connect(modifier,SIGNAL(clicked()),this,SLOT(modifArticle()));

}
