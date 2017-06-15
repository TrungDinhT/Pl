QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11


HEADERS += \
    RelationManager/relation.h \
    RelationManager/RelationManager.h \
    NoteManager/NoteManager.h \
    NoteManager/notes.h \
    Interface/ArticleInterface.h \
    Interface/ManagerInterface.h \
#    Interface/TacheInterface.h \
#    Interface/ImageInterface.h \
#    Interface/UI.h \
    Interface/NoteInterfaceEditable.h \
    Interface/NoteInterface.h \
#    Interface/MyQToolbar.h \
    Interface/globalInterface.h \
    Interface/ArticleInterfaceEditable.h \
    iterator.h \
    exception.h \
    Interface/corbeilleinterface.h


SOURCES += \
    NoteManager/notes.cpp \
    NoteManager/NoteManager.cpp \
 #   Interface/UI.cpp \
    main.cpp \
    RelationManager/relation.cpp \
    RelationManager/RelationManager.cpp \
    Interface/NoteInterfaceEditable.cpp \
    Interface/NoteInterface.cpp \
    Interface/GlobalInterface.cpp \
    Interface/ArticleInterfaceEditable.cpp \
    Interface/ArticleInterface.cpp \
    Interface/ManagerInterface.cpp \
    Interface/corbeilleinterface.cpp



QT += widgets xml
