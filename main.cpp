

#include "mainwindow.h"
#pragma execution_character_set("utf-8")
#include <QApplication>
#include <QQmlApplicationEngine>
#ifdef GOOGLEMAP_LIBRARY
#include <QtPlugin>
#endif
#include <QCoreApplication>
#include <QPluginLoader>
#include <QMessageBox>
#include "loggermanagement.h"
#include <QByteArray>
#include "pluginmanager.h"
#include "loadingwidget.h"


//#include "externprocess.h"

using namespace Log;
Q_DMMM    *datapool = nullptr;


int main(int argc, char *argv[])
{
#ifdef GOOGLEMAP_LIBRARY
    Q_IMPORT_PLUGIN(QGeoServiceProviderFactoryGooglemaps);
#endif

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec); //解决汉字乱码问题
    QApplication a(argc, argv);

    Q_DMMM datapool;
    auto mythread = new QThread(); //新建
    datapool.moveToThread(mythread);
    mythread ->start();//信号：开始工作！

    MainWindow w;
    w.show();

//    LoadingWidget *loading = new LoadingWidget();
//    loading->show();
//    LoggerManagement *log = new LoggerManagement;
    return a.exec();
}
