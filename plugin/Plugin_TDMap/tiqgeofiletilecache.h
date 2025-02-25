﻿/**************************************************************************
 *   文件名	：tiqgeofiletilecache.h
 *   =======================================================================
 *   创 建 者	：田小帆
 *   创建日期	：2021-5-13
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

#pragma once

#include <private/qgeofiletilecache_p.h>

#include <QSqlDatabase>

class TiQGeoFileTileCache : public QGeoFileTileCache
{
    Q_OBJECT
public:
    TiQGeoFileTileCache(const QString& directory = QString(), QObject* parent = nullptr);
    ~TiQGeoFileTileCache();

    QSharedPointer<QGeoTileTexture> get(const QGeoTileSpec& spec) override;

    void insert(const QGeoTileSpec& spec, const QByteArray& bytes, const QString& format,
                QAbstractGeoTileCache::CacheAreas areas = QAbstractGeoTileCache::AllCaches) override;

private:
    void addToSqlite(const QGeoTileSpec& spec, const QString& format, const QByteArray& bytes);

    QSharedPointer<QGeoTileTexture> getFromSqlite(const QGeoTileSpec& spec);


private:
    QSqlDatabase* m_db     = nullptr;
    bool          m_valid  = false;
    QString       m_dbName = "TUGSMapCache.db";
};
