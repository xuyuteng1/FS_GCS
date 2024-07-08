#include "globalObserver.h"

globalObserver *globalObserver::m_pInst = NULL;
globalObserver *globalObserver::getGlobalObserver()
{
    if (m_pInst == NULL)
    {
        m_pInst = new globalObserver();
    }
    return m_pInst;
}

void globalObserver::release()
{
    if (m_pInst != NULL)
    {
        delete m_pInst;
        m_pInst = NULL;
    }
}

void globalObserver::attach(const QString type, QObject *reciver, const char *method)
{
    obesrverApater *oA = obesrverApaterFactory::getInst()->createObesrverApater();
    connect(oA, SIGNAL(notify()), reciver, method);
    relationData *data = new relationData();
    data->type = type;
    data->reciver = reciver;
    data->obesrverApater = oA;
    m_oRelationList.append(data);
}

void globalObserver::detach(const QString type, const QObject *reciver)
{
    QList<relationData*>::iterator iter = m_oRelationList.begin();

    while (iter != m_oRelationList.end())
    {
        if ((*iter)->type.compare(type) == 0 && (*iter)->reciver == reciver)
        {
            relationData *data = *iter;
            m_oRelationList.removeOne((*iter));

            delete data->obesrverApater;
            delete data;
            return;
        }
        iter++;
    }
}

void globalObserver::notify(const QString type)
{
    QList<relationData*>::iterator iter = m_oRelationList.begin();
    while (iter != m_oRelationList.end())
    {
        if ((*iter)->type.compare(type) == 0)
        {
            emit (*iter)->obesrverApater->notify();
        }
        iter++;
    }
}

globalObserver::globalObserver(QObject *parent) : QObject(parent)
{

}

globalObserver::~globalObserver()
{
    //释放列表数据
    QList<relationData*>::iterator iter = m_oRelationList.begin();

    while (iter != m_oRelationList.end())
    {
        delete (*iter)->obesrverApater;
        delete *iter;
        iter++;
    }

}
