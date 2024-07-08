#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>

class StatusWidget : public QWidget
{
    Q_OBJECT
public:
    StatusWidget();


private:
    QLabel                  *checkSelfStatusName = nullptr;                                             //自检状态
    QLabel                  *checkSelfStatusValue        = nullptr;

    QLabel                  *workStatusName     = nullptr;                                                  //工作状态
    QLabel                  *workStatusValue               = nullptr;

    QLabel                  *pitchAngleiffName = nullptr;                                                      //俯仰偏差角
    QLabel                  *pitchAngleDiffValue = nullptr;

    QLabel                  *headDiffName = nullptr;                                                        //航向偏差角
    QLabel                  *headDiffValue = nullptr;

    QLabel                  *localXName = nullptr;                                                            //波门位置X
    QLabel                  *localXValue = nullptr;

    QLabel                  *localYName = nullptr;                                                          //波门位置Y
    QLabel                  *localYValue = nullptr;

    QLabel                  *localXSizeName = nullptr;                                                  //波门大小X
    QLabel                  *localXSizeValue = nullptr;

    QLabel                  *localYSizeName = nullptr;                                                  //波们大小Y
    QLabel                  *localYSizeValue = nullptr;

    QLabel                  *responsivityName = nullptr;                                            //响应度
    QLabel                  *responsivityValue = nullptr;

    QLabel                  *focalLengthName = nullptr;                                             //焦距值
    QLabel                  *focalLengthValue = nullptr;

    QLabel                  *pixelSizeName = nullptr;                                             //焦距值
    QLabel                  *pixelSizeValue = nullptr;

    QLabel                  *perspectiveName = nullptr;                                          //下视角
    QLabel                  *perspectiveValue = nullptr;


    QGridLayout         *statusLayout = nullptr;

private:
    void                        statusWidgetInit();

    void                        UpdateStatus();

private slots:
    void Slot_DMMM_Event(quint16 event,qint16 a,qint16 b);

};

#endif // STATUSWIDGET_H
