#include "ArticleInterfaceEditable.h"

articleInterfaceEditable::saveArticle(){
  article.texte = texte.text;
  article.titre = titre.text;
  article.actualiserDateModif(); //à définir
}

articleInterfaceEditable::articleInterfaceEditable(article& a){
  article = a;
  titre = new QLineEdit(article.titre,this);
  texte = new QLineEdit(article.texte,this);
  save = new QPushButton(/*objet QIcon,*/"sauvegarder",this);
  connect(save,SIGNAL(clicked()),this,SLOT(saveArticle()));
  //disposition à revoir
}
