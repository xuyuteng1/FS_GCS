QT += gui multimediawidgets \
    widgets

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    genericplugin.cpp \
    videoconfigwidget.cpp \
    videoparameter.cpp \
    videoplaywidget.cpp

HEADERS += \
    genericplugin.h \
    videoconfigwidget.h \
    videoparameter.h \
    videoplaywidget.h

INCLUDEPATH += ../../../DeviceInterface\
                             ../../../configuration\

DISTFILES += NetCamera.json

include($$PWD/../../../DeviceInterface/DeviceInterface.pri)
include($$PWD/../../../configuration/configuration.pri)

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

TARGET          = $$qtLibraryTarget(NetCamera)
win32: LIBS += -L$$PWD/../../../VideoCodec/ -lVideoCodec

INCLUDEPATH += $$PWD/../../../VideoCodec
DEPENDPATH += $$PWD/../../../VideoCodec



message($$OUT_PWD)
win32:CONFIG(release, debug|release):DESTDIR = $$OUT_PWD/../../../release/plugins/NetCamera
else:win32:CONFIG(debug, debug|release):DESTDIR = $$OUT_PWD/../../../debug/plugins/NetCamera
