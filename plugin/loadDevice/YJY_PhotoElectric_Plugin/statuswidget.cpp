#include "statuswidget.h"
#include "DMMM.h"
StatusWidget::StatusWidget()
{
    statusWidgetInit();
    connect(Qt::DMMM(),&Q_DMMM::Signal_DMMM_Event,this,&StatusWidget::Slot_DMMM_Event);
}

void StatusWidget::statusWidgetInit()
{
    if(this->checkSelfStatusName == nullptr){
        this->checkSelfStatusName = new QLabel(QStringLiteral("自检状态"));
        this->checkSelfStatusName->setObjectName("statusNameLabel");
        this->checkSelfStatusName->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    }

    if(this->checkSelfStatusValue == nullptr){
        this->checkSelfStatusValue = new QLabel();
        this->checkSelfStatusValue->setObjectName("statusValueLabel");
        this->checkSelfStatusValue->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    }

    if(this->workStatusName == nullptr){
        this->workStatusName = new QLabel(QStringLiteral("工作状态"));
        this->workStatusName->setObjectName("statusNameLabel");
        this->workStatusName->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    }

    if(this->workStatusValue == nullptr){
        this->workStatusValue = new QLabel();
        this->workStatusValue->setObjectName("statusValueLabel");
        this->workStatusValue->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    }

    if(this->pitchAngleiffName == nullptr){
        this->pitchAngleiffName = new QLabel(QStringLiteral("俯仰偏差角"));
        this->pitchAngleiffName->setObjectName("statusNameLabel");
        this->pitchAngleiffName->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    }

    if(this->pitchAngleDiffValue == nullptr){
        this->pitchAngleDiffValue = new QLabel();
        this->pitchAngleDiffValue->setObjectName("statusValueLabel");
        this->pitchAngleDiffValue->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    }

    if(this->headDiffName == nullptr){
        this->headDiffName = new QLabel(QStringLiteral("航向偏差角"));
        this->headDiffName->setObjectName("statusNameLabel");
        this->headDiffName->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    }

    if(this->headDiffValue == nullptr){
        this->headDiffValue = new QLabel();
        this->headDiffValue->setObjectName("statusValueLabel");
        this->headDiffValue->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    }

    if(this->localXName == nullptr){
        this->localXName = new QLabel(QStringLiteral("波门位置X"));
        this->localXName->setObjectName("statusNameLabel");
        this->localXName->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    }

    if(this->localXValue == nullptr){
        this->localXValue = new QLabel();
        this->localXValue->setObjectName("statusValueLabel");
        this->localXValue->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    }

    if(this->localYName == nullptr){
        this->localYName = new QLabel(QStringLiteral("波门位置Y"));
        this->localYName->setObjectName("statusNameLabel");
        this->localYName->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    }

    if(this->localYValue == nullptr){
        this->localYValue = new QLabel();
        this->localYValue->setObjectName("statusValueLabel");
        this->localYValue->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    }


    if(this->localXSizeName == nullptr){
        this->localXSizeName = new QLabel(QStringLiteral("波门大小X"));
        this->localXSizeName->setObjectName("statusNameLabel");
        this->localXSizeName->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    }

    if(this->localXSizeValue == nullptr){
        this->localXSizeValue = new QLabel();
        this->localXSizeValue->setObjectName("statusValueLabel");
        this->localXSizeValue->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    }

    if(this->localYSizeName == nullptr){
        this->localYSizeName = new QLabel(QStringLiteral("波们大小Y"));
        this->localYSizeName->setObjectName("statusNameLabel");
        this->localYSizeName->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    }

    if(this->localYSizeValue == nullptr){
        this->localYSizeValue = new QLabel();
        this->localYSizeValue->setObjectName("statusValueLabel");
        this->localYSizeValue->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    }

    if(this->responsivityName == nullptr){
        this->responsivityName = new QLabel(QStringLiteral("响应度"));
        this->responsivityName->setObjectName("statusNameLabel");
        this->responsivityName->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    }

    if(this->responsivityValue == nullptr){
        this->responsivityValue = new QLabel();
        this->responsivityValue->setObjectName("statusValueLabel");
        this->responsivityValue->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    }

    if(this->focalLengthName == nullptr){
        this->focalLengthName = new QLabel(QStringLiteral("焦距值"));
        this->focalLengthName->setObjectName("statusNameLabel");
        this->focalLengthName->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    }

    if(this->focalLengthValue == nullptr){
        this->focalLengthValue = new QLabel();
        this->focalLengthValue->setObjectName("statusValueLabel");
        this->focalLengthValue->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    }

    if(this->pixelSizeName == nullptr){
        this->pixelSizeName = new QLabel(QStringLiteral("像元大小"));
        this->pixelSizeName->setObjectName("statusNameLabel");
        this->pixelSizeName->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    }

    if(this->pixelSizeValue == nullptr){
        this->pixelSizeValue = new QLabel();
        this->pixelSizeValue->setObjectName("statusValueLabel");
        this->pixelSizeValue->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    }

    if(this->perspectiveName == nullptr){
        this->perspectiveName = new QLabel(QStringLiteral("下视角"));
        this->perspectiveName->setObjectName("statusNameLabel");
        this->perspectiveName->setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    }

    if(this->perspectiveValue == nullptr){
        this->perspectiveValue = new QLabel();
        this->perspectiveValue->setObjectName("statusValueLabel");
        this->perspectiveValue->setAlignment(Qt::AlignLeft | Qt::AlignHCenter);
    }

    if(this->statusLayout == nullptr){
        this->statusLayout = new QGridLayout();
    }

    this->statusLayout->addWidget(this->workStatusValue,0,0,1,10,Qt::AlignCenter);
    this->statusLayout->addWidget(this->pitchAngleDiffValue,1,0,1,4,Qt::AlignRight|Qt::AlignVCenter);
    this->statusLayout->addWidget(this->headDiffValue,1,4,1,4,Qt::AlignCenter);
    this->statusLayout->addWidget(this->responsivityValue,1,8,1,2,Qt::AlignLeft|Qt::AlignVCenter);
    this->statusLayout->setRowStretch(0,1);
    this->statusLayout->setRowStretch(1,1);
    this->statusLayout->setRowStretch(2,5);

//    this->statusLayout->addWidget(this->checkSelfStatusName,0,0,1,2);
//    this->statusLayout->addWidget(this->checkSelfStatusValue,0,2,1,1);

//    this->statusLayout->addWidget(this->workStatusName,0,4,1,2);
//    this->statusLayout->addWidget(this->workStatusValue,0,5,1,1);

//    this->statusLayout->addWidget(this->pitchAngleiffName,1,0,1,2);
//    this->statusLayout->addWidget(this->pitchAngleDiffValue,1,2,1,1);

//    this->statusLayout->addWidget(this->headDiffName,1,4,1,2);
//    this->statusLayout->addWidget(this->headDiffValue,1,5,1,1);

//    this->statusLayout->addWidget(this->localXName,2,0,1,2);
//    this->statusLayout->addWidget(this->localXValue,2,2,1,1);

//    this->statusLayout->addWidget(this->localYName,2,4,1,2);
//    this->statusLayout->addWidget(this->localYValue,2,5,1,1);

//    this->statusLayout->addWidget(this->localXSizeName,3,0,1,2);
//    this->statusLayout->addWidget(this->localXSizeValue,3,2,1,1);

//    this->statusLayout->addWidget(this->localYSizeName,3,4,1,2);
//    this->statusLayout->addWidget(this->localYSizeValue,3,5,1,1);

//    this->statusLayout->addWidget(this->responsivityName,4,0,1,2);
//    this->statusLayout->addWidget(this->responsivityValue,4,2,1,1);

//    this->statusLayout->addWidget(this->focalLengthName,4,4,1,2);
//    this->statusLayout->addWidget(this->focalLengthValue,4,5,1,1);

//    this->statusLayout->addWidget(this->pixelSizeName,5,0,1,2);
//    this->statusLayout->addWidget(this->pixelSizeValue,5,2,1,1);

//    this->statusLayout->addWidget(this->perspectiveName,5,4,1,2);
//    this->statusLayout->addWidget(this->perspectiveValue,5,5,1,1);

    this->setLayout(this->statusLayout);

    this->setObjectName("StatusWidget");
}

void StatusWidget::UpdateStatus()
{
    YJYProtocol::SeekerYJY_State_t state = Qt::DMMM()->getYJYPtlState();
    switch(state.selfcheckInfo){
        case 1:this->checkSelfStatusValue->setText(QStringLiteral("正常"));
        case 2:this->checkSelfStatusValue->setText(QStringLiteral("故障"));
        case 3:this->checkSelfStatusValue->setText(QStringLiteral("进行中"));
        default:this->checkSelfStatusValue->setText(QStringLiteral("-"));
    }

    ///////////////////////////////////////////////////////////////////////
    QString str;
    uint8_t workstate = state.WorkState;
    if(Qt::DMMM()->getYJYPtl()->getE_DeviceState() == YJYProtocol::DeviceState_Connect){
        switch(Qt::DMMM()->getYJYPtl()->getE_DeviceType()){
            case YJYProtocol::DeviceType_SerialPort:
                str += QStringLiteral("串口控制 - ");
            break;
            case YJYProtocol::DeviceType_NetUDP:
                str += QStringLiteral("网络控制 - ");
            break;
            default:break;
        }
    }
    else{
        str += QStringLiteral("控制中断 - ");
    }


    if(workstate & 0b1){
        str += QStringLiteral("跟踪有效 - ");
    }else{
        str += QStringLiteral("目标丢失 - ");
    }

    if(workstate & 0b10){
        str += QStringLiteral("攻击 - ");
    }else{
        str += QStringLiteral("搜索 - ");
    }

    if(workstate & 0b10000){
        str += QStringLiteral("盲区 - ");
    }else{
        str += QStringLiteral("非盲区 - ");
    }

    workstate >>=2;
    switch(workstate&0b11){
        case 0b00:str += QStringLiteral("可见光");break;
        case 0b01:str += QStringLiteral("可见光");break;
        case 0b10:str += QStringLiteral("红外白热");break;
        case 0b11:str += QStringLiteral("红外黑热");break;
    }
    this->workStatusValue->setText(str);
    this->pitchAngleDiffValue->setText(QString::number(state.PitchErr_cd*0.01f,'f',2)+QStringLiteral("°"));
    this->headDiffValue->setText(QString::number(state.YawErr_cd*0.01f,'f',2)+QStringLiteral("°"));
    this->localXValue->setText(QString::number(state.WaveGatePos_x));                                                //波门位置Y
    this->localYValue       ->setText(QString::number(state.WaveGatePos_y));                                              //波门大小X
    this->localXSizeValue   ->setText(QString::number(state.WaveGateSize_x));                                              //波们大小Y
    this->localYSizeValue   ->setText(QString::number(state.WaveGateSize_y));
    //响应度
    this->responsivityValue ->setText(QString::number(state.TrackingResponsivity));                                        //焦距值
    this->focalLengthValue  ->setText(QString::number(state.FocalLength));                                      //焦距值
    this->pixelSizeValue    ->setText(QString::number(state.TargetSize));                                      //下视角
    this->perspectiveValue  ->setText(QString::number(state.BottomView));
}

void StatusWidget::Slot_DMMM_Event(quint16 event, qint16 a , qint16 b)
{
    Q_UNUSED(a);
    Q_UNUSED(b);
    switch(event){
    case Q_DMMM::DMMM_YJYEvent_Ptl_Update:
    case Q_DMMM::DMMM_YJYEvent_Timer10Hz:
        UpdateStatus();
        break;
    default:break;
    }
}
