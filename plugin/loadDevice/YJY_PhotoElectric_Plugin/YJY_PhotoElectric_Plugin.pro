QT += gui network serialport widgets multimediawidgets

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gaugeprogressbar.cpp \
    handlewidget.cpp \
    statuswidget.cpp \
    toolwidget.cpp \
    widget.cpp \
    yjy_photoelectric_plugin.cpp

HEADERS += \
    gaugeprogressbar.h \
    handlewidget.h \
    statuswidget.h \
    toolwidget.h \
    widget.h \
    yjy_photoelectric_plugin.h

DISTFILES += YJY_PhotoElectric_Plugin.json \
    logo.ico

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

include($$PWD/../../../DeviceInterface/DeviceInterface.pri)
include($$PWD/Library/Library.pri)
include($$PWD/Protocol/Protocol.pri)

INCLUDEPATH += \
            Library \
            Protocol \
            $$PWD/../../../DeviceInterface


# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

TARGET          = $$qtLibraryTarget(YJY_PhotoElectric_Plugin)
win32: LIBS += -L$$PWD/../../../VideoCodec/ -lVideoCodec

INCLUDEPATH += $$PWD/../../../VideoCodec
DEPENDPATH += $$PWD/../../../VideoCodec



message($$OUT_PWD)
win32:CONFIG(release, debug|release):DESTDIR = $$OUT_PWD/../../../release/plugins/YJY_PhotoElectric_Plugin
else:win32:CONFIG(debug, debug|release):DESTDIR = $$OUT_PWD/../../../debug/plugins/YJY_PhotoElectric_Plugin

RESOURCES += \
    image.qrc \
    style.qrc
