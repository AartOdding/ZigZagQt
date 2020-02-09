#-------------------------------------------------
#
# Project created by QtCreator 2019-06-27T20:02:12
#
#-------------------------------------------------

QT       += core gui widgets opengl multimedia

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

INCLUDEPATH += src

SOURCES += \
    src/application.cpp \
    src/library/standard/control/ParameterView.cpp \
    src/library/standard/control/clockoperator.cpp \
    src/library/standard/control/increasingvalueoperator.cpp \
    src/library/standard/control/noisewavecontroloperator.cpp \
    src/library/standard/control/sinewavecontroloperator.cpp \
    src/library/standard/texture/blendoperator.cpp \
    src/library/standard/texture/cameraoperator.cpp \
    src/library/standard/texture/coloroperator.cpp \
    src/library/standard/texture/displacementoperator.cpp \
    src/library/standard/texture/fadeoperator.cpp \
    src/library/standard/texture/kinecttwotextureoperator.cpp \
    src/library/standard/texture/noiseoperator.cpp \
    src/library/standard/texture/sawtoothwaveoperator.cpp \
    src/library/standard/texture/sinewaveoperator.cpp \
    src/library/standard/texture/squarewaveoperator.cpp \
    src/library/standard/texture/texturedata.cpp \
    src/library/standard/texture/textureview.cpp \
    src/library/standard/texture/textureviewwindow.cpp \
    src/library/standard/texture/thresholdoperator.cpp \
    src/model/BaseDataType.cpp \
    src/model/BaseOperator.cpp \
    src/model/BaseZigZagObject.cpp \
    src/model/ExecutionEngine.cpp \
    src/model/OperatorLibrary.cpp \
    src/model/OperatorNetwork.cpp \
    src/model/clock.cpp \
    src/model/datainput.cpp \
    src/model/parameter/BaseComponent.cpp \
    src/model/parameter/BaseParameter.cpp \
    src/model/parameter/ButtonParameter.cpp \
    src/model/parameter/ColorParameter.cpp \
    src/model/parameter/EnumParameter.cpp \
    src/model/parameter/Float64Component.cpp \
    src/model/parameter/FloatParameter.cpp \
    src/model/parameter/Int64Component.cpp \
    src/model/parameter/IntParameter.cpp \
    src/model/parameter/ParameterFlags.cpp \
    src/model/parameter/TextComponent.cpp \
    src/model/parameter/Transform2DParameter.cpp \
    src/model/parameter/TriggerComponent.cpp \
    src/utility/Deserializer.cpp \
    src/utility/Serializer.cpp \
    src/view/BaseConnector.cpp \
    src/view/ConnectionManager.cpp \
    src/view/DataConnector.cpp \
    src/view/ExecutionEngineWindow.cpp \
    src/view/OperatorNetworkView.cpp \
    src/view/OperatorSelectorDialog.cpp \
    src/view/ParameterConnector.cpp \
    src/view/PopupWindow.cpp \
    src/view/Viewport.cpp \
    src/view/basedataview.cpp \
    src/view/cable.cpp \
    src/view/connection/ConnectionEditor.cpp \
    src/view/connection/ConnectionTreeView.cpp \
    src/view/opengldataview.cpp \
    src/view/operatornametag.cpp \
    src/view/operatorview.cpp \
    src/view/parameter/ButtonParameterWidget.cpp \
    src/view/parameter/DoubleParameterWidget.cpp \
    src/view/parameter/EnumParameterWidget.cpp \
    src/view/parameter/IntParameterWidget.cpp \
    src/view/parameter/Transform2DParameterWidget.cpp \
    src/view/parameter/parametereditor.cpp \
    src/view/parameter/parametergroup.cpp \
    src/main.cpp \
    src/renderer.cpp

HEADERS += \
    src/application.h \
    src/command/connectcommand.h \
    src/command/connectparameterscommand.h \
    src/command/disconnectcommand.h \
    src/command/disconnectparameterscommand.h \
    src/command/movecommand.h \
    src/library/standard/control/clockoperator.h \
    src/library/standard/control/increasingvalueoperator.h \
    src/library/standard/control/noisewavecontroloperator.h \
    src/library/standard/control/parameterview.h \
    src/library/standard/control/sinewavecontroloperator.h \
    src/library/standard/texture/blendoperator.h \
    src/library/standard/texture/cameraoperator.h \
    src/library/standard/texture/coloroperator.h \
    src/library/standard/texture/displacementoperator.h \
    src/library/standard/texture/fadeoperator.h \
    src/library/standard/texture/kinecttwotextureoperator.h \
    src/library/standard/texture/noiseoperator.h \
    src/library/standard/texture/sawtoothwaveoperator.h \
    src/library/standard/texture/sinewaveoperator.h \
    src/library/standard/texture/squarewaveoperator.h \
    src/library/standard/texture/texturedata.h \
    src/library/standard/texture/textureview.h \
    src/library/standard/texture/textureviewwindow.h \
    src/library/standard/texture/thresholdoperator.h \
    src/model/BaseDataType.hpp \
    src/model/BaseOperator.hpp \
    src/model/BaseZigZagObject.hpp \
    src/model/ExecutionEngine.hpp \
    src/model/OperatorLibrary.hpp \
    src/model/OperatorNetwork.hpp \
    src/model/clock.h \
    src/model/datainput.h \
    src/model/parameter/BaseComponent.hpp \
    src/model/parameter/BaseParameter.hpp \
    src/model/parameter/ButtonParameter.hpp \
    src/model/parameter/ColorParameter.hpp \
    src/model/parameter/EnumParameter.hpp \
    src/model/parameter/Float64Component.hpp \
    src/model/parameter/FloatParameter.hpp \
    src/model/parameter/Int64Component.hpp \
    src/model/parameter/IntParameter.hpp \
    src/model/parameter/ParameterFlags.hpp \
    src/model/parameter/TextComponent.hpp \
    src/model/parameter/Transform2DParameter.hpp \
    src/model/parameter/TriggerComponent.hpp \
    src/utility/Deserializer.hpp \
    src/utility/FrameRateMonitor.hpp \
    src/utility/Serializer.hpp \
    src/utility/frameratecontroller.h \
    src/utility/numericHelpers.hpp \
    src/utility/stdLibraryHelpers.hpp \
    src/view/BaseConnector.hpp \
    src/view/ConnectionManager.hpp \
    src/view/DataConnector.hpp \
    src/view/ExecutionEngineWindow.hpp \
    src/view/OperatorNetworkView.hpp \
    src/view/OperatorSelectorDialog.hpp \
    src/view/ParameterConnector.hpp \
    src/view/PopupWindow.hpp \
    src/view/Viewport.hpp \
    src/view/basedataview.h \
    src/view/cable.h \
    src/view/connection/ConnectionEditor.hpp \
    src/view/connection/ConnectionTreeView.hpp \
    src/view/opengldataview.h \
    src/view/operatornametag.h \
    src/view/operatorview.h \
    src/view/parameter/ButtonParameterWidget.hpp \
    src/view/parameter/DoubleParameterWidget.hpp \
    src/view/parameter/EnumParameterWidget.hpp \
    src/view/parameter/IntParameterWidget.hpp \
    src/view/parameter/Transform2DParameterWidget.hpp \
    src/view/parameter/parametereditor.h \
    src/view/parameter/parametergroup.h \
    src/renderer.h

FORMS += \
    forms/librarydialogpanel.ui \
    forms/mainwindow.ui \
    forms/parameterconnectionscreen.ui \
    forms/transform2dparameterwidget.ui

RESOURCES += \
    resources/resources.qrc


INCLUDEPATH += third_party/glm

INCLUDEPATH += third_party/stb


# kinect for xbox one
win32 {
    INCLUDEPATH += third_party/Kinect2/include
    LIBS += -L"$$PWD/third_party/Kinect2/lib" -lKinect20
}

# copied december 2019
# https://github.com/randrew/phantomstyle
include( third_party/phantom/phantom.pri )

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
