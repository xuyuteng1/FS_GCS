#ifndef GLOBALOBSERVER_H
#define GLOBALOBSERVER_H

#include <QObject>
#include "obesrverApater.h"

struct relationData
{
    QString type;
    QObject *reciver;
    obesrverApater *obesrverApater;
};

class globalObserver : public QObject
{
    Q_OBJECT
public:
    static globalObserver* getGlobalObserver();
    static void release();
    static globalObserver *m_pInst;

    void attach(const QString type, QObject *reciver, const char *method);
    void detach(const QString type, const QObject* reciver);

    void notify(const QString type);

signals:

private:
    explicit globalObserver(QObject *parent = 0);
    ~globalObserver();

private:
    QList<relationData*> m_oRelationList;
};

#endif // GLOBALOBSERVER_H
