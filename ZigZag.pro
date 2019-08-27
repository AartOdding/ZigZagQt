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
        application.cpp \
        library/standard/shadertop.cpp \
        library/standard/test/testdataview.cpp \
        library/standard/test/testoperator.cpp \
        library/standard/texture/blendoperator.cpp \
        library/standard/texture/coloroperator.cpp \
        library/standard/texture/sinewaveoperator.cpp \
        library/standard/texture/texturedata.cpp \
        library/standard/texture/texturedataview.cpp \
        model/basedatatype.cpp \
        model/datainput.cpp \
        model/librarymodel.cpp \
        model/parameter/baseparameter.cpp \
        model/baseoperator.cpp \
        model/enumdefinition.cpp \
        model/parameter/enum.cpp \
        model/parameter/float.cpp \
        model/parameter/int.cpp \
        model/parameter/parameterowner.cpp \
        model/parameter/parameterrow.cpp \
        model/projectmodel.cpp \
        model/projectscope.cpp \
        view/baseconnector.cpp \
        view/basedataview.cpp \
        view/datablockcable.cpp \
        view/datablockconnector.cpp \
        view/opengldataview.cpp \
        view/operatornametag.cpp \
        view/operatorselectordialog.cpp \
        view/operatorview.cpp \
        view/parameter/enumwidget.cpp \
        view/parameter/floatwidget.cpp \
        view/parameter/intwidget.cpp \
        view/parameter/parametereditor.cpp \
        view/parameter/parameterpanel.cpp \
        view/parameter/parameterpanelheader.cpp \
        view/projectscopeview.cpp \
        view/projectsurface.cpp \
        view/viewport.cpp \
        main.cpp \
        renderer.cpp

HEADERS += \
        application.h \
        command/addcommand.h \
        command/connectcommand.h \
        command/connectparameterscommand.h \
        command/disconnectcommand.h \
        command/movecommand.h \
        command/removecommand.h \
        library/standard/shadertop.h \
        library/standard/test/testdata.h \
        library/standard/test/testdataview.h \
        library/standard/test/testoperator.h \
        library/standard/texture/blendoperator.h \
        library/standard/texture/coloroperator.h \
        library/standard/texture/sinewaveoperator.h \
        library/standard/texture/texturedata.h \
        library/standard/texture/texturedataview.h \
        model/basedatatype.h \
        model/datainput.h \
        model/librarymodel.h \
        model/parameter/baseparameter.h \
        model/baseoperator.h \
        model/enumdefinition.h \
        model/namemanager.h \
        model/parameter/enum.h \
        model/parameter/float.h \
        model/parameter/int.h \
        model/parameter/parameterowner.h \
        model/parameter/parameterrow.h \
        model/projectmodel.h \
        model/projectscope.h \
        utility/bounded_value.h \
        utility/fpsmonitor.h \
        utility/frameratecontroller.h \
        view/baseconnector.h \
        view/basedataview.h \
        view/datablockcable.h \
        view/datablockconnector.h \
        view/opengldataview.h \
        view/operatornametag.h \
        view/operatorselectordialog.h \
        view/operatorview.h \
        view/parameter/enumwidget.h \
        view/parameter/floatwidget.h \
        view/parameter/intwidget.h \
        view/parameter/parametereditor.h \
        view/parameter/parameterpanel.h \
        view/parameter/parameterpanelheader.h \
        view/projectscopeview.h \
        view/projectsurface.h \
        view/viewport.h \
        renderer.h

FORMS += \
        librarydialogpanel.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    bugs-todos

RESOURCES += \
    resources/resources.qrc
