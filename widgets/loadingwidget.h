#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H
//程序加载界面
#include <QWidget>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QProgressBar>



class LoadingWidget : public QWidget
{
public:
    LoadingWidget();


private:
    QGridLayout *widgetLayout = nullptr;




private:
    void widgetInit();


};

#endif // LOADINGWIDGET_H
