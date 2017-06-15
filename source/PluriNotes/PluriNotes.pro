QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11


HEADERS += \
    RelationManager/relation.h \
    RelationManager/RelationManager.h \
    NoteManager/NoteManager.h \
    NoteManager/notes.h \
    Interface/ManagerInterface.h \
    Interface/TacheInterface.h \
    Interface/ImageInterface.h \
    Interface/NoteInterfaceEditable.h \
    Interface/globalInterface.h \
    Interface/ArticleInterfaceEditable.h \
    iterator.h \
    exception.h \
    Interface/corbeilleinterface.h \


SOURCES += \
    NoteManager/notes.cpp \
    NoteManager/NoteManager.cpp \
    main.cpp \
    RelationManager/relation.cpp \
    RelationManager/RelationManager.cpp \
    Interface/NoteInterfaceEditable.cpp \
    Interface/GlobalInterface.cpp \
    Interface/ArticleInterfaceEditable.cpp \
    Interface/ManagerInterface.cpp \
    Interface/corbeilleinterface.cpp \
    Interface/TacheInterface.cpp \
    Interface/ImageInterface.cpp


QT += widgets xml
