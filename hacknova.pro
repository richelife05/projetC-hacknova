QT += widgets sql printsupport

CONFIG += c++17

TARGET = hacknova
TEMPLATE = app

SOURCES += \
    main.cpp \
    salle.cpp \
    libraries/qrcodegen/qrcodegen.cpp

HEADERS += \
    salle.h \
    libraries/qrcodegen/qrcodegen.hpp

FORMS += \
    salle.ui

INCLUDEPATH += $$PWD/libraries/qrcodegen

# ============================================================
#  ZXing-C++ (Scan d'image)
# ============================================================
INCLUDEPATH += "C:/zxing/zxing-cpp-3.1.1/core/src"
INCLUDEPATH += "C:/zxing/zxing-cpp-build/core"
DEPENDPATH += "C:/zxing/zxing-cpp-3.1.1/core/src"
LIBS += -L"C:/zxing/zxing-cpp-build/core" -lZXing

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target