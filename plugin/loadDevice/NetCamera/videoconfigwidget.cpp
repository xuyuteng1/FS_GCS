#include "videoconfigwidget.h"

VideoConfigWidget::VideoConfigWidget()
{
    if(this->data == nullptr){
        this->data = new VideoParameter();
    }
    widgetInit();
    connectSignalAndSlot();
    initialize();
}

void VideoConfigWidget::widgetInit()
{
    if(this->linkMode == nullptr){
        this->linkMode = new QLabel(QStringLiteral("连接方式:"));
        this->linkMode->setObjectName("widgetNameLabel");
    }
    if(this->linkModeComboBox == nullptr){
        this->linkModeComboBox = new QComboBox();
        this->linkModeComboBox->setObjectName("widgetComboBox");
    }

    if(this->urlLabel == nullptr){
        this->urlLabel = new QLabel(QStringLiteral("连接地址:"));
        this->urlLabel->setObjectName("widgetNameLabel");
    }
    if(this->urlComboBox == nullptr){
        this->urlComboBox = new QComboBox();
        this->urlComboBox->setEditable(true);
        this->urlComboBox->setObjectName("widgetComboBox");
    }

    if(this->codecMode == nullptr){
        this->codecMode = new QLabel(QStringLiteral("解码速度:"));
        this->codecMode->setObjectName("widgetNameLabel");
    }
    if(this->codecModeComboBox == nullptr){
        this->codecModeComboBox = new QComboBox();
        this->codecModeComboBox->addItems(QStringList()<<"ultrafast"<<"superfast"<<"veryfast"<<"faster"<<"fast"<<"medium"<<"slow"<<"slower"<<"veryslow"<<"placebo");
         this->codecModeComboBox->setCurrentText("fast");
        this->codecModeComboBox->setObjectName("widgetComboBox");
    }
    if(this->bufferSize == nullptr){
        this->bufferSize = new QLabel(QStringLiteral("缓  冲  区:"));
        this->bufferSize->setObjectName("widgetNameLabel");
    }
    if(this->bufferSizeEdit == nullptr){
        this->bufferSizeEdit = new QLineEdit("1024000");
        this->bufferSizeEdit->setObjectName("widgetLineEdit");
    }
    if(this->maxDelay == nullptr){
        this->maxDelay = new QLabel(QStringLiteral("延时约束:"));
        this->maxDelay->setObjectName("widgetNameLabel");
    }
    if(this->maxDelayEdit == nullptr){
        this->maxDelayEdit = new QLineEdit("5000");
        this->maxDelayEdit->setObjectName("widgetLineEdit");
    }
    if(this->cfrLabel == nullptr){
        this->cfrLabel = new QLabel(QStringLiteral("视频质量:"));
        this->cfrLabel->setObjectName("widgetNameLabel");
    }
    if(this->cfrComboBox == nullptr){
        this->cfrComboBox = new QComboBox();
        QStringList list;
        for(int i = 0; i < 51; i++){
            list<<QString::number(i);
        }
        this->cfrComboBox->addItems(list);
        this->cfrComboBox->setCurrentText("23");
        this->cfrComboBox->setObjectName("widgetComboBox");
    }
    if(this->stimeoutLabel == nullptr){
        this->stimeoutLabel = new QLabel(QStringLiteral("连接超时:"));
        this->stimeoutLabel->setObjectName("widgetNameLabel");
    }
    if(this->stimeoutEdit == nullptr){
        this->stimeoutEdit = new QLineEdit("1000000");
        this->stimeoutEdit->setObjectName("widgetLineEdit");
    }
    if(this->fpsLabel == nullptr){
        this->fpsLabel = new QLabel(QStringLiteral("fps:"));
        this->fpsLabel->setObjectName("widgetNameLabel");
    }
    if(this->fpsComboBox == nullptr){
        this->fpsComboBox = new QComboBox();
        this->fpsComboBox->addItems(QStringList()<<"5"<<"10"<<"15"<<"20"<<"25"<<"30"<<"35"<<"40"<<"45"<<"50"<<"55"<<"60");
        this->fpsComboBox->setCurrentText("25");
        this->fpsComboBox->setObjectName("widgetComboBox");
    }
    if(this->connectButton == nullptr){
        this->connectButton = new QPushButton(QStringLiteral("连接"));
        this->connectButton->setObjectName("widgetButton");
    }
    if(this->saveButton == nullptr){
        this->saveButton = new QPushButton(QStringLiteral("保存"));
        this->saveButton->setObjectName("widgetButton");
    }


    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    this->widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding),0,0,1,2);
    this->widgetLayout->addWidget(this->linkMode,0,2,1,1);
    this->widgetLayout->addWidget(this->linkModeComboBox,0,3,1,2);
    this->widgetLayout->addWidget(this->urlLabel,1,2,1,1);
    this->widgetLayout->addWidget(this->urlComboBox,1,3,1,2);
    this->widgetLayout->addWidget(this->codecMode,2,2,1,1);
    this->widgetLayout->addWidget(this->codecModeComboBox,2,3,1,2);
    this->widgetLayout->addWidget(this->bufferSize,3,2,1,1);
    this->widgetLayout->addWidget(this->bufferSizeEdit,3,3,1,2);
    this->widgetLayout->addWidget(this->maxDelay,4,2,1,1);
    this->widgetLayout->addWidget(this->maxDelayEdit,4,3,1,2);
    this->widgetLayout->addWidget(this->cfrLabel,5,2,1,1);
    this->widgetLayout->addWidget(this->cfrComboBox,5,3,1,2);
    this->widgetLayout->addWidget(this->stimeoutLabel,6,2,1,1);
    this->widgetLayout->addWidget(this->stimeoutEdit,6,3,1,2);
    this->widgetLayout->addWidget(this->fpsLabel,7,2,1,1);
    this->widgetLayout->addWidget(this->fpsComboBox,7,3,1,2);
    this->widgetLayout->addWidget(this->connectButton,9,2,2,1);
    this->widgetLayout->addWidget(this->saveButton,9,4,2,1);

    this->widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding),0,5,1,2);
    this->widgetLayout->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum),8,2,1,3);
    this->widgetLayout->setColumnStretch(0,2);
    this->widgetLayout->setColumnStretch(3,1);
    this->widgetLayout->setColumnStretch(5,2);

    this->widgetLayout->setRowStretch(8,1);

    this->widgetLayout->setVerticalSpacing(10);

    this->setLayout(this->widgetLayout);


}

void VideoConfigWidget::connectSignalAndSlot()
{
    connect(this->linkModeComboBox,&QComboBox::currentTextChanged,this,&VideoConfigWidget::linkModelChangedSlot);
    connect(this->connectButton,&QPushButton::clicked,this,&VideoConfigWidget::connectButtonClickedSlot);
    connect(this->saveButton,&QPushButton::clicked,this,&VideoConfigWidget::saveButtonClickedSlot);
}

void VideoConfigWidget::initialize()
{
    QList<QString>linkMode = this->data->getLinkModelStrList();
    this->linkModeComboBox->addItems(linkMode);

    if(linkMode.indexOf(this->data->getLastLinkModelStr()) != -1){
        this->linkModeComboBox->setCurrentText(this->data->getLastLinkModelStr());
    }else{
        if(linkMode.count() > 0){
            this->linkModeComboBox->setCurrentText(linkMode.at(0));
            this->data->setLastLinkModelStr(linkMode.at(0));
        }
    }

    if(this->data->getLastLinkModelStr().compare("tcp") == 0){
        this->urlComboBox->clear();
        this->urlComboBox->addItems(this->data->getTcpLinkAddressHistoryList());
        if(this->data->getTcpLinkAddressHistoryList().lastIndexOf(this->data->getTcpLastLinkAddress()) != -1){
            this->urlComboBox->setCurrentText(this->data->getTcpLastLinkAddress());
        }else{
            if(this->data->getTcpLinkAddressHistoryList().count() > 0){
                this->urlComboBox->setCurrentText(this->data->getTcpLinkAddressHistoryList().at(0));
                this->data->setTcpLastLinkAddress(this->data->getTcpLinkAddressHistoryList().at(0));
            }
        }

    }else if(this->data->getLastLinkModelStr().compare("udp") == 0){
        this->urlComboBox->clear();
        this->urlComboBox->addItems(this->data->getUdpLinkAddressHistoryList());
        if(this->data->getUdpLinkAddressHistoryList().lastIndexOf(this->data->getUdpLastLinkAddress()) != -1){
            this->urlComboBox->setCurrentText(this->data->getUdpLastLinkAddress());
        }else{
            if(this->data->getUdpLinkAddressHistoryList().count() > 0){
                this->urlComboBox->setCurrentText(this->data->getUdpLinkAddressHistoryList().at(0));
                this->data->setTcpLastLinkAddress(this->data->getUdpLinkAddressHistoryList().at(0));
            }
        }
    }else if(this->data->getLastLinkModelStr().compare("rtsp") == 0){
        this->urlComboBox->clear();
        this->urlComboBox->addItems(this->data->getRtspLinkAddressHistoryList());
        if(this->data->getRtspLinkAddressHistoryList().lastIndexOf(this->data->getRtspLastLinkAddress()) != -1){
            this->urlComboBox->setCurrentText(this->data->getRtspLastLinkAddress());
        }else{
            if(this->data->getRtspLinkAddressHistoryList().count() > 0){
                this->urlComboBox->setCurrentText(this->data->getRtspLinkAddressHistoryList().at(0));
                this->data->setTcpLastLinkAddress(this->data->getRtspLinkAddressHistoryList().at(0));
            }
        }
    }

    this->codecModeComboBox->setCurrentText(this->data->getCodecLastStr());
    this->bufferSizeEdit->setText(QString::number(this->data->getBufferSize()));
    this->maxDelayEdit->setText(QString::number(this->data->getDelay_ms()));
    this->cfrComboBox->setCurrentText(QString::number(this->data->getCfr()));
    this->stimeoutEdit->setText(QString::number(this->data->getLinkTimeout()));
    this->fpsComboBox->setCurrentText(QString::number(this->data->getFps()));
}

void VideoConfigWidget::linkModelChangedSlot(QString text)
{
    this->urlComboBox->clear();
    if(text.compare("tcp") == 0){
        this->urlComboBox->addItems(this->data->getTcpLinkAddressHistoryList());
        if(this->data->getTcpLinkAddressHistoryList().lastIndexOf(this->data->getTcpLastLinkAddress()) != -1){
            this->urlComboBox->setCurrentText(this->data->getTcpLastLinkAddress());
        }else{
            if(this->data->getTcpLinkAddressHistoryList().count() > 0){
                this->urlComboBox->setCurrentText(this->data->getTcpLinkAddressHistoryList().at(0));
                this->data->setTcpLastLinkAddress(this->data->getTcpLinkAddressHistoryList().at(0));
            }
        }

    }else if(text.compare("udp") == 0){
        this->urlComboBox->addItems(this->data->getUdpLinkAddressHistoryList());
        if(this->data->getUdpLinkAddressHistoryList().lastIndexOf(this->data->getUdpLastLinkAddress()) != -1){
            this->urlComboBox->setCurrentText(this->data->getUdpLastLinkAddress());
        }else{
            if(this->data->getUdpLinkAddressHistoryList().count() > 0){
                this->urlComboBox->setCurrentText(this->data->getUdpLinkAddressHistoryList().at(0));
                this->data->setTcpLastLinkAddress(this->data->getUdpLinkAddressHistoryList().at(0));
            }
        }
    }else if(text.compare("rtsp") == 0){
        this->urlComboBox->addItems(this->data->getRtspLinkAddressHistoryList());
        if(this->data->getRtspLinkAddressHistoryList().lastIndexOf(this->data->getRtspLastLinkAddress()) != -1){
            this->urlComboBox->setCurrentText(this->data->getRtspLastLinkAddress());
        }else{
            if(this->data->getRtspLinkAddressHistoryList().count() > 0){
                this->urlComboBox->setCurrentText(this->data->getRtspLinkAddressHistoryList().at(0));
                this->data->setTcpLastLinkAddress(this->data->getRtspLinkAddressHistoryList().at(0));
            }
        }
    }
}

void VideoConfigWidget::connectButtonClickedSlot()
{
    saveButtonClickedSlot();
    emit photoelectricConnectSignal();
}

void VideoConfigWidget::saveButtonClickedSlot()
{
    this->data->setLastLinkModelStr(this->linkModeComboBox->currentText());
    if(this->linkModeComboBox->currentText().compare("tcp") == 0){
        this->data->setTcpLastLinkAddress(this->urlComboBox->currentText());
    }else if(this->linkModeComboBox->currentText().compare("udp") == 0){
        this->data->setUdpLastLinkAddress(this->urlComboBox->currentText());
    }else if(this->linkModeComboBox->currentText().compare("rtsp") == 0){
        this->data->setRtspLastLinkAddress(this->urlComboBox->currentText());
    }

    this->data->setCodecLastStr(this->codecModeComboBox->currentText());
    this->data->setBufferSize(this->bufferSizeEdit->text().toInt());
    this->data->setDelay_ms(this->maxDelayEdit->text().toInt());
    this->data->setCfr(this->cfrComboBox->currentText().toInt());
    this->data->setLinkTimeout(this->stimeoutEdit->text().toInt());
    this->data->setFps(this->fpsComboBox->currentText().toInt());
}
