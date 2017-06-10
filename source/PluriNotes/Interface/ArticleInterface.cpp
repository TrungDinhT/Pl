#include "ArticleInterface.h"

//void articleInterface::modifArticle(){
//  articleInterfaceEditable a = new articleInterfaceEditable(article);
//  delete this;
//}

//articleInterface::articleInterface(){
//  delete this;
//}
articleInterface::articleInterface(article& a){
  article = a;
  titre = new QLineEdit(article.titre);
  texte = new QLineEdit(article.texte);
  modifier = new QPushButton(/*objet QIcon,*/"modifier");
  //connect(modifier,SIGNAL(clicked()),this,SLOT(modifArticle()));
  //disposition à revoir

  principale = new QVBoxLayout(this);
  principale->addWidget(titre);
  principale->addWidget(texte);
  principale->addWidget(modifier);
  this->setLayout(principale);
}
