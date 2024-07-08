TARGET = qtgeoservices_TianDimaps
QT += location-private positioning-private network location concurrent sql location-private positioning-private
PLUGIN_TYPE = geoservices
PLUGIN_CLASS_NAME = QGeoServiceProviderFactoryTianDiMaps
load(qt_plugin)

CONFIG(debug,debug|release){
    DESTDIR=../bin
}else{
    DESTDIR=../bin
}

HEADERS += \
    TiMapTile.h \
    tidataworker.h \
    tigeotilefetcher.h \
    timapengine.h \
    timapprovider.h \
    timapurlengine.h \
    tiqgeocodereply.h \
    tiqgeocodingmanagerengine.h \
    tiqgeofiletilecache.h \
    tiqgeoserviceproviderfactory.h \
    tiqgeotiledmappingmanagerengine.h \
    tiqgeotiledmapreply.h \
    titianditumapprovider.h

SOURCES += \
    tidataworker.cpp \
    tigeotilefetcher.cpp \
    timapengine.cpp \
    timapprovider.cpp \
    timapurlengine.cpp \
    tiqgeocodereply.cpp \
    tiqgeocodingmanagerengine.cpp \
    tiqgeofiletilecache.cpp \
    tiqgeoserviceproviderfactory.cpp \
    tiqgeotiledmappingmanagerengine.cpp \
    tiqgeotiledmapreply.cpp \
    titianditumapprovider.cpp

DISTFILES += \
    timap_plugin.json

