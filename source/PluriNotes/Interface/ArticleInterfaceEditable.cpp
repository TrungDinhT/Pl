#include "ArticleInterfaceEditable.h"

void articleInterfaceEditable::saveNote(){
  Article* a = new Article(titre->text(),text->toPlainText());
  qDebug()<<"test4";
  emit sauvegarde(a);
  qDebug()<<"test5";
}

articleInterfaceEditable::articleInterfaceEditable(Article* a):NoteInterfaceEditable(a){
  article = a;
  //titre = new QLineEdit(article.titre,this);
  if (a == 0){text = new QTextEdit("");}
  else{text = new QTextEdit(article->getText());}
  //text = new QLineEdit(article->texte);
  //this->save = new QPushButton(/*objet QIcon,*/"sauvegarder");
  //connect(save,SIGNAL(clicked()),this,SLOT(saveArticle()));
  //disposition à revoir
  principale = new QVBoxLayout(this);
  principale->addWidget(titre);
  principale->addWidget(text);
  principale->addWidget(save);
  principale->addWidget(supprimer);
  principale->addWidget(relier);
  principale->addWidget(changerversion);
  principale->addWidget(rendreversionactive);

  this->setLayout(principale);
}


