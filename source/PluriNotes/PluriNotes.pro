QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11


HEADERS += \
    RelationManager/relation.h \
    RelationManager/RelationManager.h \
#    Corbeille/corbeille.h \
    NoteManager/NoteManager.h \
    NoteManager/notes.h \
    Interface/ArticleInterface.h \
#    Interface/TacheInterface.h \
#    Interface/ImageInterface.h \
    Interface/UI.h \
    iterator.h \
    exception.h


SOURCES += \
 #   Corbeille/corbeille.cpp \
    NoteManager/notes.cpp \
    NoteManager/NoteManager.cpp \
    Interface/UI.cpp \
    main.cpp \
    RelationManager/relation.cpp \
    RelationManager/RelationManager.cpp



QT += widgets xml
