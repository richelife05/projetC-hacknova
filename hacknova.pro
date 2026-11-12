QT += widgets sql

CONFIG += c++17

TARGET = hacknova
TEMPLATE = app

SOURCES += \
    employe.cpp \
    main.cpp \
    connection.cpp

HEADERS += \
    employe.h \
    connection.h

FORMS += \
    integration.ui

DISTFILES += \
    .gitignore