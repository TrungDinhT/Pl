QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11


HEADERS += \
#    RelationManager/relation.h \
#    Corbeille/corbeille.h \
#    NoteManager/NoteManager.h \
#    NoteManager/notes.h \
#    Interface/ArticleInterface.h \
#    Interface/TacheInterface.h \
#    Interface/ImageInterface.h \
    Interface/UI.h


SOURCES += \
 #   Corbeille/corbeille.cpp \
 #   NoteManager/notes.cpp \
 #   Interface/ArticleInterface.cpp \
    Interface/UI.cpp \
    main.cpp


QT += widgets xml
