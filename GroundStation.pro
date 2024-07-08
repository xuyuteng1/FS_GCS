QT       += core gui quick qml quickwidgets positioning location serialport network opengl xml designer multimedia printsupport sql svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QML_IMPORT_NAME = GIS_AirPositionModel
QML_IMPORT_MAJOR_VERSION = 1

QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += \
    GCS_DEBUG_ENABLE \
    CUSTOMER_KEYWAY=1 \
    CUSTOMER_NUAA=2 \
    CUSTOMER_CHENGGONG=3 \
    CUSTOMER_NAME=3

SOURCES += \
    gis/gis_RTLmodel.cpp \
    gis/gis_airmaptoolmodel.cpp \
    gis/gis_airnoflyzonemodel.cpp \
    gis/gis_airpointmodel.cpp \
    gis/gis_airpositionmodel.cpp \
    gis/gis_airroutesmodel.cpp \
    gis/gis_mapview.cpp \
    gis/gis_model.cpp \
    gis/gis_model_target.cpp \
    hudview/hudopenglview.cpp \
    main.cpp \
    mainwindow.cpp \
    widgets/FCBoardInfo.cpp \
    widgets/FunDbg.cpp \
    widgets/PlaneConfig.cpp \
    widgets/applicatinconfigure.cpp \
    widgets/chartwidget.cpp \
    widgets/chatwidget.cpp \
    widgets/command_widget.cpp \
    widgets/communicationswidget.cpp \
    widgets/dataview.cpp \
    widgets/general_config.cpp \
    widgets/loadingwidget.cpp \
    widgets/loadwidget.cpp \
    widgets/parameterconfigwidget.cpp \
    widgets/promptwidget.cpp \
    widgets/rangingtoolbarwidget.cpp \
    widgets/routeswidget.cpp \
    widgets/systemcommondwidget.cpp \
    widgets/systemconfigwidget.cpp \
    widgets/systeminfowidget.cpp \
    widgets/systemmsgwidget.cpp \
    widgets/systemtoolbar.cpp \
    widgets/titlewidget.cpp \
    widgets/videowidget.cpp

HEADERS += \
    EnumDef.h \
    ReleaseNotes.h \
    errorCode.h \
    gis/gis_RTLmodel.h \
    gis/gis_airmaptoolmodel.h \
    gis/gis_airnoflyzonemodel.h \
    gis/gis_airpointmodel.h \
    gis/gis_airpositionmodel.h \
    gis/gis_airroutesmodel.h \
    gis/gis_mapview.h \
    gis/gis_model.h \
    gis/gis_model_target.h \
    hudview/hudopenglview.h \
    mainwindow.h \
    widgets/FCBoardInfo.h \
    widgets/FunDbg.h \
    widgets/PlaneConfig.h \
    widgets/applicatinconfigure.h \
    widgets/chartwidget.h \
    widgets/chatwidget.h \
    widgets/command_widget.h \
    widgets/communicationswidget.h \
    widgets/dataview.h \
    widgets/general_config.h \
    widgets/loadingwidget.h \
    widgets/loadwidget.h \
    widgets/parameterconfigwidget.h \
    widgets/promptwidget.h \
    widgets/rangingtoolbarwidget.h \
    widgets/routeswidget.h \
    widgets/systemcommondwidget.h \
    widgets/systemconfigwidget.h \
    widgets/systeminfowidget.h \
    widgets/systemmsgwidget.h \
    widgets/systemtoolbar.h \
    widgets/titlewidget.h \
    widgets/videowidget.h
INCLUDEPATH += gis \
               widgets \
               observer\
               DMMM\
               communication\
               hudview\
               dbg\
               WidgetSub\
               WidgetSub/sidebar\
               WidgetSub/Command\
               WidgetSub/vehicleCFG/general\
               WidgetSub/vehicleCFG/copter\
               WidgetSub/vehicleCFG/SIM\
               WidgetSub/vehicleCFG/Plane\
               Libraries\
               configuration\
               Libraries/qcustomplot\
#               VideoPlayer\
               charts\
               logger\
               ThreadPool\
               HUDWidget\
               DeviceInterface\
               DeviceInterface/Device\
               PluginManager\
#               ExternProcessmanager\
               PayloadLink \
               Protocol \
               SvgDesignerModule \

TRANSLATIONS += \
    GroundStation_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    GIS_Map.qml \
    README.md

RESOURCES += \
    conf.qrc \
    img.qrc \
    qml.qrc \
    shader.qrc \
    style.qrc

include($$PWD/observer/observer.pri)
include($$PWD/DMMM/DMMM.pri)
include($$PWD/configuration/configuration.pri)
include($$PWD/WidgetSub/sidebar/SUB_sidebar.pri)
include($$PWD/Libraries/Libraries.pri)
include($$PWD/WidgetSub/vehicleCFG/copter/SUB_cfg_Copter.pri)
include($$PWD/WidgetSub/vehicleCFG/SIM/SUB_SIM.pri)
include($$PWD/WidgetSub/vehicleCFG/Plane/SUB_cfg_Plane.pri)
include($$PWD/WidgetSub/vehicleCFG/general/SUB_cfg_general.pri)
include($$PWD/WidgetSub/Command/SUB_CMD.pri)
#include($$PWD/plugin/Plugin_googlemaps/Plugin_googlemaps.pri)
#include($$PWD/VideoPlayer/videoplayer.pri)
include($$PWD/charts/chartview.pri)
include($$PWD/logger/loggermanagement.pri)
include($$PWD/ThreadPool/ThreadPool.pri)
include($$PWD/HUDWidget/hudwidget.pri)
include($$PWD/DeviceInterface/DeviceInterface.pri)
include($$PWD/PluginManager/pluginmanager.pri)
#include($$PWD/ExternProcessmanager/ExternProcessmanager.pri)
include($$PWD/PayloadLink/PayloadLink.pri)
include($$PWD/Protocol/protocol.pri)
include($$PWD/SvgDesignerModule/SvgDesignerModule.pri)

RC_ICONS = logo.ico

FORMS +=

win32:CONFIG(release, debug|release): {
    win32: LIBS += -L$$PWD/log4cplus/lib/ -llog4cplusU
}else:win32:CONFIG(debug, debug|release):{
    win32: LIBS += -L$$PWD/log4cplus/lib/ -llog4cplusUD
}


INCLUDEPATH += $$PWD/log4cplus/include
DEPENDPATH += $$PWD/log4cplus/include

win32: LIBS += -L$$PWD/VideoCodec/ -lVideoCodec

INCLUDEPATH += $$PWD/VideoCodec
DEPENDPATH += $$PWD/VideoCodec

LIBS += -luser32

message($$OUT_PWD)




