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
  //disposition à revoir
}
