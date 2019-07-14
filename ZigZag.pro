#-------------------------------------------------
#
# Project created by QtCreator 2019-06-27T20:02:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZigZag
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17 console

SOURCES += \
        main.cpp \
        model/data/basedatablock.cpp \
        model/data/baseparameter.cpp \
        model/data/datablockinput.cpp \
        model/data/enumdefinition.cpp \
        model/data/enumparameter.cpp \
        model/data/integerparameter.cpp \
        model/data/texturedatablock.cpp \
        model/operator/baseoperator.cpp \
        model/operator/operatorlibrary.cpp \
        model/operator/shadertop.cpp \
        model/program/programmodel.cpp \
        renderer.cpp \
        view/connectorview.cpp \
        view/operatorview.cpp \
        view/programview.cpp \
        view/viewport.cpp

HEADERS += \
        command/addcommand.h \
        command/connectcommand.h \
        command/connectparameterscommand.h \
        command/disconnectcommand.h \
        command/movecommand.h \
        command/removecommand.h \
        model/data/basedatablock.h \
        model/data/baseparameter.h \
        model/data/datablockinput.h \
        model/data/enumdefinition.h \
        model/data/enumparameter.h \
        model/data/integerparameter.h \
        model/data/texturedatablock.h \
        model/operator/baseoperator.h \
        model/operator/operatorlibrary.h \
        model/operator/shadertop.h \
        model/program/namemanager.h \
        model/program/programmodel.h \
        renderer.h \
        view/connectorview.h \
        view/operatorview.h \
        view/programview.h \
        view/viewport.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md
