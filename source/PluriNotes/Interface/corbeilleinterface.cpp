#include "corbeilleinterface.h"

corbeille& c = corbeille::getCorbeille();

corbeilleInterface::corbeilleInterface():QDialog(){
    QVBoxLayout* mainLay = new QVBoxLayout;

    mainView = new QListWidget;
    mainLay->addWidget(mainView);
    for(corbeille::Iterator it = c.begin();it!=c.end();it++)
    {
        mainView->addItem((*it)->getId());
    }

    QHBoxLayout* buttonLay = new QHBoxLayout;
    del = new QPushButton("Supprimer");
    rstore = new QPushButton("Restaurer");
    vider = new QPushButton("Vider");
    close = new QPushButton("Fermer");
    buttonLay->addWidget(del);
    buttonLay->addWidget(rstore);
    buttonLay->addWidget(vider);
    buttonLay->addWidget(close);

    mainLay->addLayout(buttonLay);

    setLayout(mainLay);
}


void corbeilleInterface::restore(){

}

void corbeilleInterface::emptyBin(){}
