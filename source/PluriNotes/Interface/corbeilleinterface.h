#ifndef CORBEILLEINTERFACE_H
#define CORBEILLEINTERFACE_H

#include "Corbeille/corbeille.h"
#include <QtWidgets>

class GlobalInterface;

class corbeilleInterface: public QDialog{
    Q_OBJECT


public slots:
    void restore();
    void emptyBin();

public:
    corbeilleInterface();

private:
    QPushButton *del;
    QPushButton *rstore;
    QPushButton *vider;
    QPushButton *close;
    QListWidget* mainView;

    friend class GlobalInterface;

};


#endif // CORBEILLEINTERFACE_H
