QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = hacknova
TEMPLATE = app

SOURCES += \
    main.cpp \
    integration.cpp

HEADERS += \
    integration.h

FORMS += \
    integration.ui