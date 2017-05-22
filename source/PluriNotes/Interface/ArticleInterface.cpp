#include "ArticleInterface.h"

articleInterface::articleInterface(): QDialog(){
    //texte et titre layout
    QFormLayout *layoutT = new QFormLayout;
    titre = new QLineEdit;
    text = new QTextEdit;
    layoutT->addRow("T&itre",titre);
    layoutT->addRow("T&exte",text);

    //bouton layout
    QHBoxLayout *layoutB = new QHBoxLayout;
    save = new QPushButton("Sauvegarder");
    layoutB->setAlignment(Qt::AlignRight);
    layoutB->addWidget(save);

    //layout commun
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layoutT);
    layout->addLayout(layoutB);

    //decorer la fenetre
    setLayout(layout);
    setWindowTitle(titre->text());
    setMinimumSize(200,200);

    //connecter
        //connect bouton
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveArticle()));
        //connecter champ titre
    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave(QString)));
        //connecter champ text
    QObject::connect(text,SIGNAL(textChanged()),this,SLOT(activerSave1()));

}


void articleInterface::saveArticle(){
    //create objet Article et puis sauvegarder
    //Article* a = new Article(titre->text(),text->toPlainText());
    //a->autoSave();

    QMessageBox::information(this, "Sauvegarde", "Votre article a bien ete sauvegarde...");
    save->setEnabled(false); // le bouton est de nouveau desactive
}

void articleInterface::activerSave(QString){
save->setEnabled(true);
}

void articleInterface::activerSave1(){
save->setEnabled(true);
}
