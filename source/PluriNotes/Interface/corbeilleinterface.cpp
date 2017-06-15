#include "corbeilleinterface.h"

NotesManager& managerNote = NotesManager::getManager();

corbeilleInterface::corbeilleInterface():QDialog(){

    mainView = new QListWidget;
    refreshCorbeille();

    QHBoxLayout* buttonLay1 = new QHBoxLayout;
    view = new QPushButton("Regarder");
    del = new QPushButton("Supprimer");
    rstore = new QPushButton("Restaurer");
    vider = new QPushButton("Vider corbeille");
    buttonLay1->addWidget(view);
    buttonLay1->addWidget(rstore);
    buttonLay1->addWidget(del);
    QHBoxLayout* buttonLay2 = new QHBoxLayout;
    buttonLay2->addWidget(vider);

    QVBoxLayout* mainLay = new QVBoxLayout;
    mainLay->addLayout(buttonLay1);
    mainLay->addWidget(mainView);
    mainLay->addLayout(buttonLay2);

    setLayout(mainLay);

    connect(rstore,SIGNAL(clicked()),this,SLOT(restaurer()));
    connect(del,SIGNAL(clicked()),this,SLOT(supprimerNote()));
    connect(vider,SIGNAL(clicked()),this,SLOT(viderCorbeille()));
}

void corbeilleInterface::refreshCorbeille() const {

    mainView->clear();
    for(NotesManager::Iterator it = managerNote.begin(); it!=managerNote.end();it++)
    {
        if((*it)->getEtat()==RIP) mainView->addItem((*it)->getId());
    }
}

void corbeilleInterface::restaurer(){
    managerNote.restaurerNote(mainView->currentItem()->text());
    refreshCorbeille();
}

void corbeilleInterface::supprimerNote(){
    managerNote.reallyDeleteNote(mainView->currentItem()->text());
    refreshCorbeille();
}

void corbeilleInterface::regarderNote(){

}

void corbeilleInterface::viderCorbeille(){
    managerNote.viderCorbeille();
    refreshCorbeille();
}

