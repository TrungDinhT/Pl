#include "ArticleInterface.h"

void articleInterface::modifArticle(){
  articleInterfaceEditable a = new articleInterfaceEditable(article);
  delete this;
}

articleInterface::articleInterface(article& a){
  article = a;
  titre = new QLineEdit(article.titre,this);
  texte = new QLineEdit(article.texte,this);
  modifier = new QPushButton(/*objet QIcon,*/"modifier",this);
  connect(modifier,SIGNAL(clicked()),this,SLOT(modifArticle()));
  //disposition à revoir
}
