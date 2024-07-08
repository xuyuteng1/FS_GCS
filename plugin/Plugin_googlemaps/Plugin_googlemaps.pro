TARGET = qtgeoservices_googlemaps
QT += location-private positioning-private network location concurrent sql location-private positioning-private
PLUGIN_TYPE = geoservices
PLUGIN_CLASS_NAME = QGeoServiceProviderFactoryGooglemaps
load(qt_plugin)
#QT -= gui

#TEMPLATE = lib
#DEFINES += GOOGLEMAP_LIBRARY

#CONFIG += c++17

#TEMPLATE = lib
#CONFIG += plugin
#CONFIG += relative_qt_rpath  # Qt's plugins should be relocatable
#TARGET = qtgeoservices_googlemaps
#PLUGIN_TYPE = geoservices
#PLUGIN_CLASS_NAME = QGeoServiceProviderFactoryGooglemaps
#target.path = $$[QT_INSTALL_PLUGINS]/$$PLUGIN_TYPE
#INSTALLS += target
#TARGET = $$qt5LibraryTarget($$TARGET)


CONFIG(debug,debug|release){
    DESTDIR=../bin
}else{
    DESTDIR=../bin
}

qtHaveModule(location-private) {
	QT += location-private
} else {
	QT += location
}
qtHaveModule(positioning-private) {
	QT += positioning-private
} else {
	QT += positioning
}
QT += network
INCLUDEPATH += ../ ./

HEADERS += \
    qgeoserviceproviderplugingooglemaps.h \
    qgeocodingmanagerenginegooglemaps.h \
    qgeocodereplygooglemaps.h \
    qgeoroutingmanagerenginegooglemaps.h \
    qgeoroutereplygooglemaps.h \
    qplacemanagerenginegooglemaps.h \
    qplacesearchreplygooglemaps.h \
    qplacecategoriesreplygooglemaps.h \
    qgeomapreplygooglemaps.h \
    qgeotiledmapgooglemaps.h \
    qgeotiledmappingmanagerenginegooglemaps.h \
    qgeotilefetchergooglemaps.h \
    qplacesearchsuggestionreplyimpl.h \
    qgeoerror_messages.h

SOURCES += \
    qgeoserviceproviderplugingooglemaps.cpp \
    qgeocodingmanagerenginegooglemaps.cpp \
    qgeocodereplygooglemaps.cpp \
    qgeoroutingmanagerenginegooglemaps.cpp \
    qgeoroutereplygooglemaps.cpp \
    qplacemanagerenginegooglemaps.cpp \
    qplacesearchreplygooglemaps.cpp \
    qplacecategoriesreplygooglemaps.cpp \
    qgeomapreplygooglemaps.cpp \
    qgeotiledmapgooglemaps.cpp \
    qgeotiledmappingmanagerenginegooglemaps.cpp \
    qgeotilefetchergooglemaps.cpp \
    qplacesearchsuggestionreplyimpl.cpp \
    qgeoerror_messages.cpp


OTHER_FILES += \
    googlemaps_plugin.json

