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
        library/standard/shadertop.cpp \
        library/standard/testdatablock.cpp \
        library/standard/testoperator.cpp \
        library/standard/texturedatablock.cpp \
        model/parameter/baseparameter.cpp \
        model/parameter/enumparameter.cpp \
        model/parameter/integerparameter.cpp \
        model/basedatablock.cpp \
        model/baseoperator.cpp \
        model/datablockinput.cpp \
        model/enumdefinition.cpp \
        model/operatorlibrary.cpp \
        model/programmodel.cpp \
        view/baseconnectable.cpp \
        view/baseconnectablesurface.cpp \
        view/datacableview.cpp \
        view/dataconnectorview.cpp \
        view/operatornametag.cpp \
        view/operatorview.cpp \
        view/programview.cpp \
        view/viewport.cpp \
        main.cpp \
        renderer.cpp

HEADERS += \
        command/addcommand.h \
        command/connectcommand.h \
        command/connectparameterscommand.h \
        command/disconnectcommand.h \
        command/movecommand.h \
        command/removecommand.h \
        library/standard/shadertop.h \
        library/standard/testdatablock.h \
        library/standard/testoperator.h \
        library/standard/texturedatablock.h \
        model/parameter/baseparameter.h \
        model/parameter/enumparameter.h \
        model/parameter/integerparameter.h \
        model/basedatablock.h \
        model/baseoperator.h \
        model/datablockinput.h \
        model/enumdefinition.h \
        model/namemanager.h \
        model/operatorlibrary.h \
        model/programmodel.h \
        view/baseconnectable.h \
        view/baseconnectablesurface.h \
        view/connectionrequestmimedata.h \
        view/datacableview.h \
        view/dataconnectorview.h \
        view/operatornametag.h \
        view/operatorview.h \
        view/programview.h \
        view/viewport.h \
        renderer.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    bugs-todos
