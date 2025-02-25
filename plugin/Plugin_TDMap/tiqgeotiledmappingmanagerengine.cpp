﻿/**************************************************************************
 *   文件名	：tiqgeotiledmappingmanagerengine.cpp
 *   =======================================================================
 *   创 建 者	：田小帆
 *   创建日期	：2021-4-27
 *   邮   箱	：499131808@qq.com
 *   Q Q		：499131808
 *   公   司      
 *   功能描述      ：
 *   使用说明 ：
 *   ======================================================================
 *   修改者	：
 *   修改日期	：
 *   修改内容	：
 *   ======================================================================
 *
 ***************************************************************************/
#include "tiqgeotiledmappingmanagerengine.h"
#include "tigeotilefetcher.h"
#include <private/qgeofiletilecache_p.h>
#include <QDebug>
#include "tiqgeofiletilecache.h"

#include "timapengine.h"
#include "timapprovider.h"
#include <QCoreApplication>

TiQGeoTiledMappingManagerEngine::TiQGeoTiledMappingManagerEngine(const QVariantMap& parameters,
                                                                 QGeoServiceProvider::Error* error,
                                                                 QString* errorString)
{
    TiMapEngine::instance();
    QGeoCameraCapabilities cameraCaps;
    cameraCaps.setMinimumZoomLevel(2.0);
    cameraCaps.setMaximumZoomLevel(20.0);
    cameraCaps.setSupportsBearing(true);
    cameraCaps.setSupportsTilting(true);
    //    cameraCaps.setMinimumTilt(0);
    //    cameraCaps.setMaximumTilt(80);
    //    cameraCaps.setMinimumFieldOfView(20.0);
    //    cameraCaps.setMaximumFieldOfView(120.0);
    //    cameraCaps.setOverzoomEnabled(true);
    setCameraCapabilities(cameraCaps);

    setTileSize(QSize(256, 256));

#define GCS_MAP_TYPE(a, b, c, d, e, f) \
    QGeoMapType(a, b, c, d, e, f, QByteArray("TiMap"), cameraCaps)

    QList<QGeoMapType> _mapList;
    auto               _mapProviders = TiMapEngine::instance()->getUrlEngine()->getProviderTable();
    // hash 遍历方式:查看qhash 文档
    auto i = _mapProviders.begin();
    while (i != _mapProviders.end()) {
        _mapList << GCS_MAP_TYPE(i.value()->getMapStyle(), i.key(), i.key(), false, false,
                                 TiMapEngine::instance()->getUrlEngine()->getIdFromType(i.key()));
        qDebug() << i.key() << i.value()->getMapStyle();
        ++i;
    }

    setSupportedMapTypes(_mapList);

    //从网络中加载瓦片
    auto tileFetcher = new TiGeoTileFetcher(parameters, this);
    setTileFetcher(tileFetcher);

    //瓦片缓存-这部分参考QtLocation的esri部分源码
    //没有用QGeoFileTileCache，默认加载地缓存不会释放，还没找到原因，估计要分析它的源码    
    QString cacheDirectory;
    QString _cache = "cachefolder";
    if (parameters.contains(_cache)) {
        cacheDirectory = QAbstractGeoTileCache::baseCacheDirectory()+parameters.value(_cache).toString();
    } else {
//        cacheDirectory = QAbstractGeoTileCache::baseCacheDirectory() + QLatin1String("TiandiMap");
        cacheDirectory = QAbstractGeoTileCache::baseCacheDirectory()+ QLatin1String("/MapCache/TiandiMap");
    }
    qDebug() << cacheDirectory;

    const int szCache = 1000 * 1024 * 1024;
#if QT_VERSION < QT_VERSION_CHECK(5,6,0)
    if (m_cacheDirectory.isEmpty())
        m_cacheDirectory = QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation) + QLatin1String("googlemaps");
    QGeoTileCache *tileCache = createTileCacheWithDir(m_cacheDirectory);
    if (tileCache)
        tileCache->setMaxDiskUsage(szCache);
#else
    if (cacheDirectory.isEmpty())
        cacheDirectory = QCoreApplication::applicationDirPath() + QLatin1String("TiandiMap");
    QAbstractGeoTileCache *tileCache = new QGeoFileTileCache(cacheDirectory);
    tileCache->setMaxDiskUsage(szCache);
    setTileCache(tileCache);
#endif

    //设置地图缓冲,如果不需要缓存,可设置setMaxDiskUsage 大小,限制到小内存,,
    //无法 注释setTileCache(); 注释后会默认缓冲图片
    //    QGeoFileTileCache* tileCache = new QGeoFileTileCache(cacheDirectory, this);
//    auto tileCache = new TiQGeoFileTileCache(cacheDirectory, this);
//    tileCache->setMaxDiskUsage(1024 * 1024 * 1024);
//    tileCache->setMaxMemoryUsage(1024 * 1024 * 100);
//    setTileCache(tileCache);

    /*
     * Disk cache setup -- defaults to ByteSize (old behavior)
     */
    //    tileCache->setCostStrategyDisk(QGeoFileTileCache::ByteSize);

    /*
     * Memory cache setup -- defaults to ByteSize (old behavior)
     */
    //    tileCache->setCostStrategyMemory(QGeoFileTileCache::ByteSize);

    /*
     * Texture cache setup -- defaults to ByteSize (old behavior)
     */
    //    tileCache->setCostStrategyTexture(QGeoFileTileCache::ByteSize);

    m_prefetchStyle = QGeoTiledMap::NoPrefetching;
    *error = QGeoServiceProvider::NoError;
    errorString->clear();

}

TiQGeoTiledMappingManagerEngine::~TiQGeoTiledMappingManagerEngine() { }

QGeoMap* TiQGeoTiledMappingManagerEngine::createMap()
{
    auto map = new QGeoTiledMap(this, nullptr);
    map->setPrefetchStyle(m_prefetchStyle);
    return map;
}

void TiQGeoTiledMappingManagerEngine::setCache(const QVariant& parameters) { }
