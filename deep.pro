QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# Les fichiers sources (.cpp)
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    sponsormanager.cpp \
    clientmanager.cpp

# Les fichiers d'en-tête (.h)
HEADERS += \
    mainwindow.h \
    sponsormanager.h \
    clientmanager.h \
    connection.h

# Les fichiers d'interface (.ui) - ila mazel testa3mel wa7ed
FORMS += \
    mainwindow.ui

# Les règles par défaut lel Qt
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target