TEMPLATE += app
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


HEADERS += \
    Carte.h \
    Joueur.h \
    Plateau.h \
    VueCarte.h \
    VueJeu.h \
    VueMenu.h \
    const_and_enum.h \
    controleur.h



SOURCES += \
    Carte.cpp \
    Joueur.cpp \
    Plateau.cpp \
    VueJeu.cpp \
    VueMenu.cpp \
    controleur.cpp \
    main.cpp




RESOURCES += \
    images.qrc

FORMS +=

