#include "ArticleInterfaceEditable.h"

//articleInterfaceEditable::saveArticle(){
//  article.texte = texte.text;
//  //article.titre = titre.text;
//  article.actualiserDateModif(); //à définir
//  articleInterface a = new articleInterface(article);
//  delete this;
//}

articleInterfaceEditable::articleInterfaceEditable(Article* a){
  article = a;
  //titre = new QLineEdit(article.titre,this);
  if (a == 0){texte = new QLineEdit("");}
  else{texte = new QLineEdit(article->texte);}
  texte = new QLineEdit(article->texte);
  save = new QPushButton(/*objet QIcon,*/"sauvegarder");
  //connect(save,SIGNAL(clicked()),this,SLOT(saveArticle()));
  //disposition à revoir
  principale = new QVBoxLayout(this);
  principale->addWidget(titre);
  principale->addWidget(texte);
  principale->addWidget(save);
  this->setLayout(principale);
}

