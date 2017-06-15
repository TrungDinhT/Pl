#ifndef CORBEILLEINTERFACE_H
#define CORBEILLEINTERFACE_H

#include <QtWidgets>
#include "ManagerInterface.h"
#include "NoteManager/NoteManager.h"

class GlobalInterface;

class corbeilleInterface: public QDialog{
    Q_OBJECT


public slots:
    void regarderNote();
    void supprimerNote();
    void restaurer();
    void viderCorbeille();

public:
    corbeilleInterface();

private:
    QPushButton *del;
    QPushButton *rstore;
    QPushButton *vider;
    QPushButton * view;
    QListWidget* mainView;
    ManagerInterface* MI;
    void refreshCorbeille() const;
    friend class GlobalInterface;

};


#endif // CORBEILLEINTERFACE_H
