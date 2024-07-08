#include "obesrverApater.h"

obesrverApaterFactory* obesrverApaterFactory::inst = NULL;
obesrverApater::obesrverApater(QObject *parent) : QObject(parent)
{

}

obesrverApaterFactory *obesrverApaterFactory::getInst()
{
    if (inst == NULL) {
        inst = new obesrverApaterFactory();
    }
    return inst;
}

void obesrverApaterFactory::realese()
{
    if (inst != NULL) {
        delete inst;
        inst = NULL;
    }
}

obesrverApater *obesrverApaterFactory::createObesrverApater()
{
    return new obesrverApater();
}
