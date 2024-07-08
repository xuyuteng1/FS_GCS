#ifndef OBESRVERAPATER_H
#define OBESRVERAPATER_H

#include <QObject>

//中间层，用来连接信号槽
class obesrverApater : public QObject
{
    Q_OBJECT
public:
    explicit obesrverApater(QObject *parent = 0);

signals:
    void notify();
};

//工厂，方便构造对象
class obesrverApaterFactory
{
public:
    static obesrverApaterFactory *getInst();
    static void realese();
    static obesrverApaterFactory* inst;

    obesrverApater* createObesrverApater();

private:
    obesrverApaterFactory()
    {}
};



#endif // OBESRVERAPATER_H
