TEMPLATE = app
TARGET   = openglax

QT       += core gui
QT       += serialport
QT       += core
QT       += widgets printsupport
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    about.cpp \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    rocket.cpp

HEADERS += \
    about.h \
    glwidget.h \
    mainwindow.h \
    qcustomplot.h \
    rocket.h

RC_ICONS = ikona_O3d_icon.ico

FORMS += \
    about.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

