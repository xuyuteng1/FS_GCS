#ifndef HANDLEWIDGET_H
#define HANDLEWIDGET_H

#include <QWidget>
#include <QDial>
#include <gaugeprogressbar.h>
#include <QPushButton>
#include <QGridLayout>
class HandleWidget : public QWidget
{
    Q_OBJECT
public:
    HandleWidget();



private:
    GaugeProgressBar *gaugeprocess = nullptr;
    QPushButton *fineTuningButton = nullptr;

    QGridLayout *widgetLayout = nullptr;


private:
    void widgetInit();
    void connectSignalAndSlot();



private slots:
    void      handleProcessValueChangedSlot(int x,int y);

public:
signals:
    void      handleProcessValueChangedSignal(bool status,int x,int y);

};

#endif // HANDLEWIDGET_H
