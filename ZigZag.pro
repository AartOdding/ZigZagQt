#-------------------------------------------------
#
# Project created by QtCreator 2019-06-27T20:02:12
#
#-------------------------------------------------

QT       += core gui widgets multimedia

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

include( ext/phantom/phantom.pri )

SOURCES += \
        application.cpp \
    library/standard/control/ParameterView.cpp \
        library/standard/control/clockoperator.cpp \
        library/standard/control/increasingvalueoperator.cpp \
        library/standard/control/noisewavecontroloperator.cpp \
        library/standard/control/sinewavecontroloperator.cpp \
        library/standard/texture/blendoperator.cpp \
        library/standard/texture/cameraoperator.cpp \
        library/standard/texture/coloroperator.cpp \
        library/standard/texture/displacementoperator.cpp \
        library/standard/texture/fadeoperator.cpp \
    library/standard/texture/kinecttwotextureoperator.cpp \
        library/standard/texture/noiseoperator.cpp \
        library/standard/texture/sawtoothwaveoperator.cpp \
        library/standard/texture/sinewaveoperator.cpp \
        library/standard/texture/squarewaveoperator.cpp \
        library/standard/texture/texturedata.cpp \
        library/standard/texture/textureview.cpp \
        library/standard/texture/textureviewwindow.cpp \
        library/standard/texture/thresholdoperator.cpp \
    model/BaseDataType.cpp \
    model/BaseOperator.cpp \
    model/BaseZigZagObject.cpp \
    model/ExecutionEngine.cpp \
    model/OperatorLibrary.cpp \
        model/clock.cpp \
        model/datainput.cpp \
        model/enumdefinition.cpp \
    model/parameter/BaseComponent.cpp \
    model/parameter/BaseParameter.cpp \
    model/parameter/ButtonParameter.cpp \
    model/parameter/ColorParameter.cpp \
    model/parameter/EnumParameter.cpp \
    model/parameter/Float64Component.cpp \
    model/parameter/FloatParameter.cpp \
    model/parameter/Int64Component.cpp \
    model/parameter/IntParameter.cpp \
    model/parameter/TextComponent.cpp \
    model/parameter/Transform2DParameter.cpp \
    model/parameter/TriggerComponent.cpp \
        model/projectmodel.cpp \
        model/projectscope.cpp \
        model/types.cpp \
    utility/Deserializer.cpp \
    utility/Serializer.cpp \
    view/BaseConnector.cpp \
    view/ConnectionManager.cpp \
    view/DataConnector.cpp \
    view/ParameterConnector.cpp \
    view/PopupWindow.cpp \
        view/basedataview.cpp \
        view/cable.cpp \
    view/connection/ConnectionEditor.cpp \
    view/connection/ConnectionTreeView.cpp \
        view/opengldataview.cpp \
        view/operatornametag.cpp \
        view/operatorselectordialog.cpp \
        view/operatorview.cpp \
        view/parameter/buttonparameterbox.cpp \
        view/parameter/doubleparameterbox.cpp \
        view/parameter/enumwidget.cpp \
        view/parameter/int64parameterbox.cpp \
        view/parameter/parametereditor.cpp \
        view/parameter/parametergroup.cpp \
        view/parameter/transform2dwidget.cpp \
        view/projectscopeview.cpp \
        view/viewport.cpp \
        main.cpp \
        renderer.cpp \
        zigzaglib/xmldeserializer.cpp \
        zigzaglib/xmlserializer.cpp \
    zigzaglib/zz_functional.cpp \
        zigzaglib/zz_object.cpp \
        zigzaglib/zz_type.cpp \

HEADERS += \
        application.h \
        command/addcommand.h \
        command/connectcommand.h \
        command/connectparameterscommand.h \
        command/disconnectcommand.h \
        command/disconnectparameterscommand.h \
        command/movecommand.h \
        command/removecommand.h \
        library/standard/control/clockoperator.h \
        library/standard/control/increasingvalueoperator.h \
        library/standard/control/noisewavecontroloperator.h \
        library/standard/control/parameterview.h \
        library/standard/control/sinewavecontroloperator.h \
        library/standard/texture/blendoperator.h \
        library/standard/texture/cameraoperator.h \
        library/standard/texture/coloroperator.h \
        library/standard/texture/displacementoperator.h \
        library/standard/texture/fadeoperator.h \
        library/standard/texture/kinecttwotextureoperator.h \
        library/standard/texture/noiseoperator.h \
        library/standard/texture/sawtoothwaveoperator.h \
        library/standard/texture/sinewaveoperator.h \
        library/standard/texture/squarewaveoperator.h \
        library/standard/texture/texturedata.h \
        library/standard/texture/textureview.h \
        library/standard/texture/textureviewwindow.h \
        library/standard/texture/thresholdoperator.h \
        model/BaseDataType.hpp \
        model/BaseOperator.hpp \
        model/BaseZigZagObject.hpp \
        model/ExecutionEngine.hpp \
        model/OperatorLibrary.hpp \
        model/clock.h \
        model/datainput.h \
        model/enumdefinition.h \
        model/namemanager.h \
        model/parameter/BaseComponent.hpp \
        model/parameter/BaseParameter.hpp \
        model/parameter/ButtonParameter.hpp \
        model/parameter/ColorParameter.hpp \
        model/parameter/EnumParameter.hpp \
        model/parameter/Float64Component.hpp \
        model/parameter/FloatParameter.hpp \
        model/parameter/Int64Component.hpp \
        model/parameter/IntParameter.hpp \
        model/parameter/TextComponent.hpp \
        model/parameter/Transform2DParameter.hpp \
        model/parameter/TriggerComponent.hpp \
        model/projectmodel.h \
        model/projectscope.h \
        model/types.h \
        utility/Deserializer.hpp \
        utility/Serializer.hpp \
        utility/fpsmonitor.h \
        utility/frameratecontroller.h \
        utility/numeric.h \
        utility/stb_image_write.h \
        utility/std_containers_helpers.h \
        view/BaseConnector.hpp \
        view/ConnectionManager.hpp \
        view/DataConnector.hpp \
        view/ParameterConnector.hpp \
        view/PopupWindow.hpp \
        view/basedataview.h \
        view/cable.h \
        view/connection/ConnectionEditor.hpp \
        view/connection/ConnectionTreeView.hpp \
        view/opengldataview.h \
        view/operatornametag.h \
        view/operatorselectordialog.h \
        view/operatorview.h \
        view/parameter/buttonparameterbox.h \
        view/parameter/doubleparameterbox.h \
        view/parameter/enumwidget.h \
        view/parameter/int64parameterbox.h \
        view/parameter/parametereditor.h \
        view/parameter/parametergroup.h \
        view/parameter/transform2dwidget.h \
        view/projectscopeview.h \
        view/viewport.h \
        renderer.h \
        zigzaglib/xmldeserializer.h \
        zigzaglib/xmlserializer.h \
        zigzaglib/zz_functional.h \
        zigzaglib/zz_object.h \
        zigzaglib/zz_type.h

FORMS += \
        librarydialogpanel.ui \
        mainwindow.ui \
        parameterconnectionscreen.ui

win32 {
    INCLUDEPATH += ext/Kinect2/include
    LIBS += -L"C:\Users\aart_\Documents\ZigZag\ext\Kinect2\lib" -lKinect20
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    bugs-todos

RESOURCES += \
    resources/resources.qrc
