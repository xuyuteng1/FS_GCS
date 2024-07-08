#include "applicatinconfigure.h"

ApplicatinConfigure::ApplicatinConfigure(QWidget *parent) : QWidget(parent)
{
    initWidget();
    listWidgetInit();
    connectSignalAndSlot();
    this->setAttribute(Qt::WA_StyledBackground,false);
//    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setWindowTitle(QStringLiteral("地面站配置"));
    this->setWindowFlags(this->windowFlags() |Qt::Dialog);
    this->setWindowModality(Qt::ApplicationModal);
    this->setMinimumSize(800,600);
}

void ApplicatinConfigure::initWidget()
{
    if(this->splitterWidget == nullptr){
        this->splitterWidget = new QSplitter();
        this->splitterWidget->setOrientation(Qt::Horizontal);
        this->splitterWidget->setSizes(QList<int>()<<50<<200);
        this->splitterWidget->setObjectName("widgetSplitter");
    }

    if(this->listViewModel == nullptr){
        this->listViewModel = new StringListModel();
    }

    if(this->actionWidget == nullptr){
        this->actionWidget = new QListView();
        this->actionWidget->setModel(this->listViewModel);
        this->actionWidget->setMaximumWidth(300);
        this->actionWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->actionWidget->setObjectName("widgetListView");
        this->splitterWidget->addWidget(this->actionWidget);

    }

    if(this->listWidget == nullptr){
        this->listWidget = new QListWidget();
        this->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        QScroller::grabGesture(this->listWidget,QScroller::LeftMouseButtonGesture);
        this->listWidget->verticalScrollBar()->setSingleStep(8);
        this->splitterWidget->addWidget(this->listWidget);
        this->listWidget->setObjectName("widgetListView");
        this->listWidget->verticalScrollBar()->setVisible(false);

    }

    if(this->w_title == nullptr){
        QPixmap pix(":/img/png/plane.png");
        w_title = new WidgetTitle(pix,QStringLiteral("系统参数配置"));
        w_title->setMaximumHeight(40);
        this->w_title->setObjectName("TitleWidget");
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

//    this->widgetLayout->addWidget(this->w_title,0,0,1,10);
    this->widgetLayout->addWidget(this->splitterWidget,1,0,5,10);
    this->widgetLayout->setSpacing(0);
    this->widgetLayout->setMargin(0);
    this->setLayout(this->widgetLayout);

    this->setObjectName("systemWidget");
}

void ApplicatinConfigure::connectSignalAndSlot()
{
//    connect(this->w_title,&WidgetTitle::signalCloseEvent,this,[=]{this->close();emit signalCloseEvent();});
    connect(this->actionWidget,&QListView::pressed,this,&ApplicatinConfigure::listWidgetItemPressedSlot);
//    connect(this->configWidget,&QListWidget::currentTextChanged,this,&SystemConfigWidget::configWidgetItemPressedSlot);
//    connect(this->mapSourcesConfigWidget,&MapSourcesWidget::mapSourcesChangedSignal,this,&ApplicatinConfigure::mapSourcesChangedSignal);
    connect(this->mapSourcesConfigWidget,&MapSourcesWidget::mapSourcesChangedSignal,this,[ = ]{QMessageBox::information(this,QStringLiteral("提示"),QStringLiteral("地图源修改已完成，重启地面站软件后生效"));});
//    connect(this->photoConfigWidget,&PhotoelectricConfigWidget::photoelectricConnectSignal,this,&ApplicatinConfigure::photoelectricConnectSignal);


}

void ApplicatinConfigure::listWidgetInit()
{

    if(this->displayConfigWidget == nullptr){
        this->displayConfigWidget = new DisplayConfigWidget();
        this->addNewWidget(QStringLiteral("显示设置"),this->displayConfigWidget);
    }

//    if(this->photoConfigWidget == nullptr){
//        this->photoConfigWidget = new PhotoelectricConfigWidget();
//        this->addNewWidget(QStringLiteral("光电吊舱设置"),this->photoConfigWidget);
//    }

    if(this->voiceAlarmConfigWidget == nullptr){
        this->voiceAlarmConfigWidget = new VoiceAlarmWidget();
        this->addNewWidget(QStringLiteral("语音告警设置"),this->voiceAlarmConfigWidget);
    }

    if(this->languageConfigWidget == nullptr){
        this->languageConfigWidget = new LanguageWidget();
        this->addNewWidget(QStringLiteral("语言设置"),this->languageConfigWidget);
    }

    if(this->mapSourcesConfigWidget == nullptr){
        this->mapSourcesConfigWidget = new MapSourcesWidget();
        this->addNewWidget(QStringLiteral("地图源设置"),this->mapSourcesConfigWidget);
    }

    if(this->hudConfigWidget == nullptr){
        this->hudConfigWidget = new HUDConfigWidget();
//        this->addNewWidget(QStringLiteral("HUD显示设置"),this->hudConfigWidget);
    }

    if(this->logSystemConfigWidget == nullptr){
        this->logSystemConfigWidget = new LogSystemConfigWidget();
//        this->addNewWidget(QStringLiteral("日志系统设置"),this->logSystemConfigWidget);
    }

    if(this->transmitWidget == nullptr){
        this->transmitWidget = new TransmitWidget();
//        this->addNewWidget(QStringLiteral("转发与透传设置"),this->transmitWidget);
    }

    if(this->storageClearWidget == nullptr){
        this->storageClearWidget = new StorageAndCachingClearWidget();
//        this->addNewWidget(QStringLiteral("内存清理"),this->storageClearWidget);
    }

    if(this->shortcutsConfigWidget == nullptr){
        this->shortcutsConfigWidget = new ShortcutsConfigWidget();
//        this->addNewWidget(QStringLiteral("快捷键设置"),this->shortcutsConfigWidget);
    }

    if(this->systemResetWidget == nullptr){
        this->systemResetWidget = new SystemResetWidget();
//        this->addNewWidget(QStringLiteral("系统还原"),this->systemResetWidget);
    }




}

void ApplicatinConfigure::addNewWidget(QString name, QGridLayout *widgetLayout)
{
    if(this->widgetMap.find(name) == this->widgetMap.end()){
        this->listViewModel->insertRow(this->listViewModel->rowCount());
        QModelIndex index = this->listViewModel->index(this->listViewModel->rowCount() - 1,0);
        this->listViewModel->setData(index,name);

        QGroupBox *widget = new QGroupBox(name);
        widget->setObjectName("widgetGroupBox");
        widget->setLayout(widgetLayout);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(widget->sizeHint());
        this->listWidget->addItem(item);
        item->setSizeHint(widget->sizeHint());
        this->listWidget->setItemWidget(item,widget);
        this->widgetMap.insert(name,item);
    }
}

void ApplicatinConfigure::listWidgetItemPressedSlot(QModelIndex index)
{

    QString text = this->listViewModel->data(index).toString();
    qDebug()<<"text = "<<text;
    if(this->widgetMap.find(text) != this->widgetMap.end()){
        QListWidgetItem * item = this->widgetMap.find(text).value();
        if(item != nullptr){
            qDebug()<<"item->setSelected(true);";
            item->setSelected(true);
            this->listWidget->scrollToItem(item,QListWidget::PositionAtTop);
        }
    }
}








DisplayConfigWidget::DisplayConfigWidget(QWidget *parent) : QGridLayout(parent)
{
    widgetInit();
    connectSignalAndSlot();
    initialize();
}

void DisplayConfigWidget::widgetInit()
{
    if(this->gammaValueLabel == nullptr){
        this->gammaValueLabel = new QLabel(QStringLiteral("屏幕亮度:"));
        this->gammaValueLabel->setObjectName("widgetNameLabel");
    }
    if(this->gammaValueEdit == nullptr){
        this->gammaValueEdit = new QSpinBox();
        this->gammaValueEdit->setObjectName("widgetSpinBox");
        this->gammaValueEdit->setMinimum(20);
        this->gammaValueEdit->setMaximum(255);
    }
    if(this->gammaValueSlider == nullptr){
        this->gammaValueSlider = new QSlider();
        this->gammaValueSlider->setOrientation(Qt::Horizontal);
        this->gammaValueSlider->setMinimum(20);
        this->gammaValueSlider->setMaximum(255);
        this->gammaValueSlider->setObjectName("widgetSlider");
    }

    if(this->modeLabel == nullptr){
        this->modeLabel = new QLabel(QStringLiteral("模式选择:"));
        this->modeLabel->setObjectName("widgetNameLabel");
    }
    if(this->powerSavingModel == nullptr){
        this->powerSavingModel = new QCheckBox(QStringLiteral("省电模式"));
        this->powerSavingModel->setObjectName("widgetCheckBox");
    }
    if(this->brightLightModel == nullptr){
        this->brightLightModel = new QCheckBox(QStringLiteral("强光模式"));
        this->brightLightModel->setObjectName("widgetCheckBox");
        this->brightLightModel->setChecked(true);
    }
    if(this->modelButtonGroup == nullptr){
        this->modelButtonGroup = new QButtonGroup();
        this->modelButtonGroup->addButton(this->powerSavingModel);
        this->modelButtonGroup->addButton(this->brightLightModel);
    }

    this->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding),0,0,1,2);
    this->addWidget(this->gammaValueLabel,0,2,1,2);
    this->addWidget(this->gammaValueEdit,0,4,1,1);
    this->addWidget(this->gammaValueSlider,0,5,1,2);

    this->addWidget(this->modeLabel,1,2,2,2);
    this->addWidget(this->powerSavingModel,1,4,1,2);
    this->addWidget(this->brightLightModel,2,4,1,2);
    this->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding),0,7,1,2);

    /*设置拉伸因子*/
    this->setColumnStretch(0,2);
    this->setColumnStretch(5,2);
    this->setColumnStretch(7,2);




#ifdef Q_OS_WIN32
    CGammaRamp GammaRamp;
    int gamma = 0;
    GammaRamp.getBrightness(NULL,gamma);
    if(gamma != this->gammaValueSlider->value()){
        this->gammaValueSlider->setValue(gamma);
    }
#endif



}

void DisplayConfigWidget::connectSignalAndSlot()
{
    connect(this->gammaValueEdit,&QSpinBox::textChanged,this,&DisplayConfigWidget::gammaValueEditChangedSlot);
    connect(this->gammaValueSlider,&QSlider::valueChanged,this,&DisplayConfigWidget::gammaValueSliderChangedSlot);
    connect(this->modelButtonGroup,QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,&DisplayConfigWidget::buttonClickedSlot);
}

void DisplayConfigWidget::initialize()
{
    if(data->getDisplayGamma() < 20){
        this->gammaValueEdit->setValue(20);
        this->gammaValueSlider->setValue(20);
        this->data->setDisplayGamma(20);
    }else{
        if(data->getDisplayGamma() > 255){
            this->gammaValueEdit->setValue(255);
            this->gammaValueSlider->setValue(255);
            this->data->setDisplayGamma(255);
        }else{
            this->gammaValueEdit->setValue(data->getDisplayGamma());
            this->gammaValueSlider->setValue(data->getDisplayGamma());
            this->gammaValueSlider->update();
        }
    }
}

void DisplayConfigWidget::changedSystemGamma(int gamma)
{
    this->data->setDisplayGamma(gamma);
#ifdef Q_OS_WIN32
    unsigned short currentGamma = 0;
    CGammaRamp GammaRamp;
    GammaRamp.getBrightness(NULL,currentGamma);
    if(currentGamma != gamma){
//        GammaRamp.SetDeviceGammaRamp(NULL, &gamma);
        GammaRamp.SetBrightness(NULL,gamma);
    }
#endif
}

void DisplayConfigWidget::gammaValueEditChangedSlot(QString val)
{
    if(this->gammaValueSlider->value() != val.toInt()){
        this->gammaValueSlider->setValue(val.toInt());
        changedSystemGamma(val.toInt());
    }
}

void DisplayConfigWidget::gammaValueSliderChangedSlot(int val)
{
    if(this->gammaValueEdit->value() != val){
        this->gammaValueEdit->setValue(val);
        changedSystemGamma(val);
    }
}

void DisplayConfigWidget::buttonClickedSlot(QAbstractButton * button)
{
    QCheckBox *box = static_cast<QCheckBox *>(button);
    if(box->isChecked()){
        if(box == this->powerSavingModel){
            this->gammaValueEdit->setValue(20);
            this->gammaValueSlider->setValue(20);
            this->data->setDisplayGamma(20);
        }else if(box == this->brightLightModel){
            this->gammaValueEdit->setValue(255);
            this->gammaValueSlider->setValue(255);
            this->data->setDisplayGamma(255);
        }
    }


}

DisplayConfigWidget::CGammaRamp::CGammaRamp()
{
    hGDI32 = NULL;
    hScreenDC = NULL;
    pGetDeviceGammaRamp = NULL;
    pSetDeviceGammaRamp = NULL;
}

DisplayConfigWidget::CGammaRamp::~CGammaRamp()
{
    FreeLibrary();
}

BOOL DisplayConfigWidget::CGammaRamp::LoadWinLibrary()
{
    BOOL bReturn = FALSE;
#ifdef Q_OS_WIN32
    FreeLibrary();
    //Load the GDI library.

    hGDI32 = ::LoadLibrary(TEXT("Gdi32.dll"));

    if (hGDI32 != NULL)
    {
        //Get the addresses of GetDeviceGammaRamp and SetDeviceGammaRamp API functions.
        pGetDeviceGammaRamp = (Type_GetDeviceGammaRamp)GetProcAddress(hGDI32, "GetDeviceGammaRamp");
        pSetDeviceGammaRamp = (Type_SetDeviceGammaRamp)GetProcAddress(hGDI32, "SetDeviceGammaRamp");
        //Return TRUE only if these functions exist.
        if (pGetDeviceGammaRamp == NULL || pSetDeviceGammaRamp == NULL)
            FreeLibrary();
        else
            bReturn = TRUE;
    }else{
        qDebug()<<"Gdi32.dll load falied!";
    }

    hUser32= ::LoadLibrary(TEXT("User32.dll"));
    if (hUser32 != NULL)
    {
        pGetDC = (Type_getDC)GetProcAddress(hUser32, "GetDC");
        pReleaseDC = (Type_releaseDC)GetProcAddress(hUser32, "ReleaseDC");
        if (pGetDC == NULL || pReleaseDC == NULL){

            bReturn = false;
            FreeLibrary();
        }
        else
            bReturn = TRUE;
    }else{
        qDebug()<<"User32.dll load falied!";
    }

#endif
    return bReturn;
}

void DisplayConfigWidget::CGammaRamp::FreeLibrary()
{
        if (hGDI32 != NULL)
        {
            ::FreeLibrary(hGDI32);
            hGDI32 = NULL;
        }
}

BOOL DisplayConfigWidget::CGammaRamp::LoadLibraryIfNeeded()
{
    BOOL bReturn = FALSE;
#ifdef Q_OS_WIN32
    if (hGDI32 == NULL || hUser32 == NULL)
            LoadWinLibrary();

    if (pGetDeviceGammaRamp != NULL && pSetDeviceGammaRamp != NULL)
            bReturn = TRUE;
#endif
        return bReturn;
}

BOOL DisplayConfigWidget::CGammaRamp::SetDeviceGammaRamp(HDC hDC, LPVOID lpRamp)
{
    if (LoadLibraryIfNeeded())
    {
        return pSetDeviceGammaRamp(hDC, lpRamp);
    }
    else
        return FALSE;
}

BOOL DisplayConfigWidget::CGammaRamp::GetDeviceGammaRamp(HDC hDC, LPVOID lpRamp)
{
    if (LoadLibraryIfNeeded())
        {
            return pGetDeviceGammaRamp(hDC, lpRamp);
        }
    else
        return FALSE;
}

HDC DisplayConfigWidget::CGammaRamp::getDC(HDC hDC)
{
    if (LoadLibraryIfNeeded())
    {
        return pGetDC(hDC);
    }
    else
        return hDC;
}
#if 1
BOOL DisplayConfigWidget::CGammaRamp::SetBrightness(HDC hDC, WORD wBrightness)
{

    BOOL bReturn = FALSE;
    HDC hGammaDC = hDC;

    if (LoadLibraryIfNeeded())
    {
        if (hDC == NULL){
            hGammaDC = pGetDC(NULL);
        }

    if (hGammaDC != NULL)
    {
        //Generate the 256-colors array for the specified wBrightness value.
        WORD GammaArray[3][256];

        for (int iIndex = 0; iIndex < 256; iIndex++)
        {
            int iArrayValue = iIndex * (wBrightness + 128);

            if (iArrayValue > 65535){
                iArrayValue = 65535;
            }
            GammaArray[0][iIndex] =
            GammaArray[1][iIndex] =
            GammaArray[2][iIndex] = (WORD)iArrayValue;
        }

        //Set the GammaArray values into the display device context.
        bReturn = SetDeviceGammaRamp(hGammaDC, GammaArray);

    }

    if (hDC == NULL){
        pReleaseDC(NULL, hGammaDC);
    }


    }

    return bReturn;
}

BOOL DisplayConfigWidget::CGammaRamp::getBrightness(HDC hDC, WORD wBrightness)
{
    BOOL bReturn = FALSE;
    HDC hGammaDC = hDC;
    WORD GammaArray[3][256] = {};
    if (LoadLibraryIfNeeded())
    {
        if (hDC == NULL)
            hGammaDC = pGetDC(NULL);
            bReturn = GetDeviceGammaRamp(hGammaDC, GammaArray);
            if(bReturn == true){
                wBrightness = GammaArray[2][1] - 128;
            }
    }

    if (hDC == NULL)
        pReleaseDC(NULL, hGammaDC);

    return bReturn;
}
#endif








#if 0
PhotoelectricConfigWidget::PhotoelectricConfigWidget()
{
    widgetInit();
    connectSignalAndSlot();
    initialize();
}

void PhotoelectricConfigWidget::widgetInit()
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


    this->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding),0,0,1,2);
    this->addWidget(this->linkMode,0,2,1,1);
    this->addWidget(this->linkModeComboBox,0,3,1,2);
    this->addWidget(this->urlLabel,1,2,1,1);
    this->addWidget(this->urlComboBox,1,3,1,2);
    this->addWidget(this->codecMode,2,2,1,1);
    this->addWidget(this->codecModeComboBox,2,3,1,2);
    this->addWidget(this->bufferSize,3,2,1,1);
    this->addWidget(this->bufferSizeEdit,3,3,1,2);
    this->addWidget(this->maxDelay,4,2,1,1);
    this->addWidget(this->maxDelayEdit,4,3,1,2);
    this->addWidget(this->cfrLabel,5,2,1,1);
    this->addWidget(this->cfrComboBox,5,3,1,2);
    this->addWidget(this->stimeoutLabel,6,2,1,1);
    this->addWidget(this->stimeoutEdit,6,3,1,2);
    this->addWidget(this->fpsLabel,7,2,1,1);
    this->addWidget(this->fpsComboBox,7,3,1,2);
    this->addWidget(this->connectButton,9,2,2,1);
    this->addWidget(this->saveButton,9,4,2,1);

    this->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding),0,5,1,2);
    this->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum),8,2,1,3);
    this->setColumnStretch(0,2);
    this->setColumnStretch(3,1);
    this->setColumnStretch(5,2);

    this->setRowStretch(8,1);

    this->setVerticalSpacing(10);

}

void PhotoelectricConfigWidget::connectSignalAndSlot()
{
    connect(this->linkModeComboBox,&QComboBox::currentTextChanged,this,&PhotoelectricConfigWidget::linkModelChangedSlot);
    connect(this->connectButton,&QPushButton::clicked,this,&PhotoelectricConfigWidget::connectButtonClickedSlot);
    connect(this->saveButton,&QPushButton::clicked,this,&PhotoelectricConfigWidget::saveButtonClickedSlot);
}

void PhotoelectricConfigWidget::initialize()
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

void PhotoelectricConfigWidget::linkModelChangedSlot(QString text)
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

void PhotoelectricConfigWidget::connectButtonClickedSlot()
{
    saveButtonClickedSlot();
    emit photoelectricConnectSignal();
}

void PhotoelectricConfigWidget::saveButtonClickedSlot()
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
#endif








LanguageWidget::LanguageWidget()
{
    widgetInit();
}

void LanguageWidget::widgetInit()
{
    if(this->languageSwitchLabel == nullptr){
        this->languageSwitchLabel = new QLabel(QStringLiteral("语言选择:"));
        this->languageSwitchLabel->setObjectName("widgetNameLabel");
    }
    if(this->languageSwitchC0mboBox == nullptr){
        this->languageSwitchC0mboBox = new QComboBox();
        this->languageSwitchC0mboBox->setObjectName("widgetComboBox");
    }

    if(this->selectButton == nullptr){
        this->selectButton = new QPushButton(QStringLiteral("选择"));
        this->selectButton->setObjectName("widgetButton");
    }

    this->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding),0,0,1,2);
    this->addWidget(this->languageSwitchLabel,0,2,1,2);
    this->addWidget(this->languageSwitchC0mboBox,0,4,1,2);
    this->addWidget(this->selectButton,0,6,1,2);
    this->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding),0,8,1,2);

    /*设置拉伸因子*/
    this->setColumnStretch(0,2);
    this->setColumnStretch(8,2);

    this->setVerticalSpacing(10);

}

void LanguageWidget::connectSignalAndSlot()
{

}











MapSourcesWidget::MapSourcesWidget()
{
    widgetInit();
    connectSignalAndSlot();
    initialize();
}

void MapSourcesWidget::widgetInit()
{
    if(this->mapLabel == nullptr){
        this->mapLabel = new QLabel(QStringLiteral("地图选择:"));
        this->mapLabel->setObjectName("widgetNameLabel");
    }
    if(this->mapNameComboBox == nullptr){
        this->mapNameComboBox = new QComboBox();
        this->mapNameComboBox->setObjectName("widgetComboBox");
    }

    if(this->mapTypeLabel == nullptr){
        this->mapTypeLabel = new QLabel(QStringLiteral("类型选择:"));
        this->mapTypeLabel->setObjectName("widgetNameLabel");
    }
    if(this->mapTypeComboBox == nullptr){
        this->mapTypeComboBox = new QComboBox();
        this->mapTypeComboBox->setObjectName("widgetComboBox");
    }

    if(this->levelLabel == nullptr){
        this->levelLabel = new QLabel(QStringLiteral("级别设置:"));
        this->levelLabel->setObjectName("widgetNameLabel");
        this->levelLabel->setToolTip(QStringLiteral("  1.最小级别不得大于最大级别和默认级别\r\n  2.最大级别不得小于最小级别和默认级别\r\n  3.默认级别不得大于最大级别和小于最小级别。"));
    }
    if(this->mapMinLevelLabel == nullptr){
        this->mapMinLevelLabel = new QLabel(QStringLiteral("最小级别:"));
        this->mapMinLevelLabel->setObjectName("widgetSubNameLabel");
    }
    if(this->mapMinLevelSpinBox == nullptr){
        this->mapMinLevelSpinBox = new QSpinBox();
        this->mapMinLevelSpinBox->setObjectName("widgetSpinBox");
    }

    if(this->mapMaxLevelLabel == nullptr){
        this->mapMaxLevelLabel = new QLabel(QStringLiteral("最大级别:"));
        this->mapMaxLevelLabel->setObjectName("widgetSubNameLabel");
    }
    if(this->mapMaxLevelSpinBox == nullptr){
        this->mapMaxLevelSpinBox = new QSpinBox();
        this->mapMaxLevelSpinBox->setObjectName("widgetSpinBox");
    }

    if(this->mapLevelLabel == nullptr){
        this->mapLevelLabel = new QLabel(QStringLiteral("默认级别:"));
        this->mapLevelLabel->setObjectName("widgetSubNameLabel");
    }
    if(this->mapLevelSpinBox == nullptr){
        this->mapLevelSpinBox = new QSpinBox();
        this->mapLevelSpinBox->setObjectName("widgetSpinBox");
    }

    if(this->connectButton == nullptr){
        this->connectButton = new QPushButton(QStringLiteral("连接"));
        this->connectButton->setObjectName("widgetButton");
    }
    if(this->saveButton == nullptr){
        this->saveButton = new QPushButton(QStringLiteral("保存"));
        this->saveButton->setObjectName("widgetButton");
    }

    this->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding),0,0,1,2);
    this->addWidget(this->mapLabel,0,2,1,1);
    this->addWidget(this->mapNameComboBox,0,3,1,2);
    this->addWidget(this->mapTypeLabel,1,2,1,1);
    this->addWidget(this->mapTypeComboBox,1,3,1,2);
    this->addWidget(this->levelLabel,2,2,3,1);
    this->addWidget(this->mapMinLevelLabel,2,3,1,1);
    this->addWidget(this->mapMinLevelSpinBox,2,4,1,1);
    this->addWidget(this->mapMaxLevelLabel,3,3,1,1);
    this->addWidget(this->mapMaxLevelSpinBox,3,4,1,1);
    this->addWidget(this->mapLevelLabel,4,3,1,1);
    this->addWidget(this->mapLevelSpinBox,4,4,1,1);
    this->addWidget(this->connectButton,5,2,2,1);
    this->addWidget(this->saveButton,5,4,2,1);
    this->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding),0,5,1,2);
    /*设置拉伸因子*/
    this->setColumnStretch(0,2);
//    this->setColumnStretch(4,1);
    this->setColumnStretch(5,2);

    this->setVerticalSpacing(10);
}

void MapSourcesWidget::connectSignalAndSlot()
{
    connect(this->mapNameComboBox,&QComboBox::currentTextChanged,this,&MapSourcesWidget::mapNameChangedSlot);
    connect(this->connectButton,&QPushButton::clicked,this,&MapSourcesWidget::connectButtonClickedSlot);
    connect(this->saveButton,&QPushButton::clicked,this,&MapSourcesWidget::saveButtonClickedSlot);

    connect(this->mapMinLevelSpinBox,QOverload<int>::of(&QSpinBox::valueChanged),this,&MapSourcesWidget::spinValueChangedSlot);
    connect(this->mapMaxLevelSpinBox,QOverload<int>::of(&QSpinBox::valueChanged),this,&MapSourcesWidget::spinValueChangedSlot);
    connect(this->mapLevelSpinBox,QOverload<int>::of(&QSpinBox::valueChanged),this,&MapSourcesWidget::spinValueChangedSlot);
}

void MapSourcesWidget::initialize()
{
    QMap<QString,QStringList>mapInfo = this->data->getSupportedMap();
    this->mapNameComboBox->clear();
    this->mapNameComboBox->addItems(mapInfo.keys());
    this->mapNameComboBox->setCurrentText(this->data->getMapNameStr());
    this->mapMinLevelSpinBox->setValue(this->data->getMinLevel());
    this->mapMaxLevelSpinBox->setValue(this->data->getMaxLevel());
    this->mapLevelSpinBox->setValue(this->data->getDefLevel());

    this->mapMinLevelSpinBox->setRange(2,21);
    this->mapMaxLevelSpinBox->setRange(2,21);
    this->mapLevelSpinBox->setRange(this->data->getMinLevel(),this->data->getMaxLevel());

}

void MapSourcesWidget::mapNameChangedSlot(QString name)
{
    QMap<QString,QStringList>mapInfo = this->data->getSupportedMap();
    if(mapInfo.find(name) != mapInfo.end()){
         this->mapTypeComboBox->clear();
        this->mapTypeComboBox->addItems(mapInfo.find(name).value());
    }
    this->mapTypeComboBox->setCurrentText(this->data->getMapTypeStr());
}

void MapSourcesWidget::connectButtonClickedSlot()
{
    saveButtonClickedSlot();
    emit mapSourcesChangedSignal();
}

void MapSourcesWidget::saveButtonClickedSlot()
{
    this->data->setMapNameStr(this->mapNameComboBox->currentText());
    this->data->setMapTypeStr(this->mapTypeComboBox->currentText());
    this->data->setMinLevel(this->mapMinLevelSpinBox->value());
    this->data->setMaxLevel(this->mapMaxLevelSpinBox->value());
    this->data->setDefLevel(this->mapLevelSpinBox->value());
}

void MapSourcesWidget::spinValueChangedSlot(int val)
{
    Q_UNUSED(val)
    if((this->mapMinLevelSpinBox->value() < this->mapMaxLevelSpinBox->value()) &&( this->mapLevelSpinBox->value() >= this->mapMinLevelSpinBox->value()) && (this->mapLevelSpinBox->value() <= this->mapMaxLevelSpinBox->value()))
    {
        this->lastMinVal = this->mapMinLevelSpinBox->value();
        this->lastMaxVal = this->mapMaxLevelSpinBox->value();
        this->lastDefVal = this->mapLevelSpinBox->value();
    }else{
        this->mapMinLevelSpinBox->setValue(this->lastMinVal);
        this->mapMaxLevelSpinBox->setValue(this->lastMaxVal);
        this->mapLevelSpinBox->setValue(this->lastDefVal);
    }
}











HUDConfigWidget::HUDConfigWidget()
{

}

void HUDConfigWidget::widgetInit()
{

}

void HUDConfigWidget::connectSignalAndSlot()
{

}













ShortcutsConfigWidget::ShortcutsConfigWidget()
{

}

void ShortcutsConfigWidget::widgetInit()
{

}

void ShortcutsConfigWidget::connectSignalAndSlot()
{

}












LogSystemConfigWidget::LogSystemConfigWidget()
{

}

TransmitWidget::TransmitWidget()
{

}

void TransmitWidget::widgetInit()
{

}

void TransmitWidget::connectSignalAndSlot()
{

}




StorageAndCachingClearWidget::StorageAndCachingClearWidget()
{

}

void StorageAndCachingClearWidget::widgetInit()
{

}

void StorageAndCachingClearWidget::connectSignalAndSlot()
{

}









SystemResetWidget::SystemResetWidget()
{

}

void SystemResetWidget::widgetInit()
{

}

void SystemResetWidget::connectSignalAndSlot()
{

}





VoiceAlarmWidget::VoiceAlarmWidget()
{
    widgetInit();
}

void VoiceAlarmWidget::widgetInit()
{
    if(this->enableLabel == nullptr){
        this->enableLabel = new QLabel(QStringLiteral("语音告警:"));
        this->enableLabel->setObjectName("widgetNameLabel");
    }
    if(this->enableCheckBox == nullptr){
        this->enableCheckBox = new QCheckBox(QStringLiteral("启用"));
        this->enableCheckBox->setObjectName("widgetCheckBox");
    }
    if(this->disenableCheckBox == nullptr){
        this->disenableCheckBox = new QCheckBox(QStringLiteral("禁用"));
        this->disenableCheckBox->setObjectName("widgetCheckBox");
    }
    if(this->enableButtonGroup == nullptr){
        this->enableButtonGroup = new QButtonGroup();
        this->enableButtonGroup->addButton(this->enableCheckBox);
        this->enableButtonGroup->addButton(this->disenableCheckBox);
    }
    if(this->engineLabel == nullptr){
        this->engineLabel = new QLabel(QStringLiteral("引擎选择:"));
        this->engineLabel->setObjectName("widgetNameLabel");
    }
    if(this->engineComboBox == nullptr){
        this->engineComboBox = new QComboBox();
        this->engineComboBox->setObjectName("widgetComboBox");
    }
    if(this->languageLabel == nullptr){
        this->languageLabel = new QLabel(QStringLiteral("语言环境:"));
        this->languageLabel->setObjectName("widgetNameLabel");
    }
    if(this->languageComboBox == nullptr){
        this->languageComboBox = new QComboBox();
        this->languageComboBox->setObjectName("widgetComboBox");
    }
    if(this->ttsLevelLabel == nullptr){
        this->ttsLevelLabel = new QLabel(QStringLiteral("播报级别:"));
        this->ttsLevelLabel->setObjectName("widgetNameLabel");
    }
    if(this->infoLevelCheckBox == nullptr){
        this->infoLevelCheckBox = new QCheckBox(QStringLiteral("消息"));
        this->infoLevelCheckBox->setObjectName("widgetCheckBox");
    }
    if(this->worningLevelCheckBox == nullptr){
        this->worningLevelCheckBox = new QCheckBox(QStringLiteral("警告"));
        this->worningLevelCheckBox->setObjectName("widgetCheckBox");
    }
    if(this->errorLevelCheckBox == nullptr){
        this->errorLevelCheckBox = new QCheckBox(QStringLiteral("错误"));
        this->errorLevelCheckBox->setObjectName("widgetCheckBox");
    }
    if(this->levelSortLabel == nullptr){
        this->levelSortLabel = new QLabel(QStringLiteral("优  先  级:"));
        this->levelSortLabel->setObjectName("widgetNameLabel");
    }
    if(this->levelSortCheckBox == nullptr){
        this->levelSortCheckBox = new QCheckBox(QStringLiteral("按优先级播报"));
        this->levelSortCheckBox->setObjectName("widgetCheckBox");
    }
    if(this->orderCheckBox == nullptr){
        this->orderCheckBox = new QCheckBox(QStringLiteral("顺序播报"));
        this->orderCheckBox->setObjectName("widgetCheckBox");
    }
    if(this->levelBreakLabel == nullptr){
        this->levelBreakLabel = new QLabel(QStringLiteral("规        则:"));
        this->levelBreakLabel->setObjectName("widgetNameLabel");
    }
    if(this->levelBreakComboBox == nullptr){
        this->levelBreakComboBox = new QCheckBox(QStringLiteral("高优先级打断低优先级"));
        this->levelBreakComboBox->setObjectName("widgetCheckBox");
    }
    if(this->volumeLabel == nullptr){
        this->volumeLabel = new QLabel(QStringLiteral("音        量:"));
        this->volumeLabel->setObjectName("widgetNameLabel");
    }
    if(this->volumeSpinBox == nullptr){
        this->volumeSpinBox = new QSpinBox();
        this->volumeSpinBox->setObjectName("widgetSpinBox");
    }
    if(this->volumeSlider == nullptr){
        this->volumeSlider = new QSlider();
        this->volumeSlider->setOrientation(Qt::Horizontal);
        this->volumeSlider->setObjectName("widgetSlider");
    }
    if(this->rateLabel == nullptr){
        this->rateLabel = new QLabel(QStringLiteral("语        速:"));
        this->rateLabel->setObjectName("widgetNameLabel");
    }
    if(this->rateSpinBox == nullptr){
        this->rateSpinBox = new QSpinBox();
        this->rateSpinBox->setObjectName("widgetSpinBox");
    }
    if(this->rateSlider == nullptr){
        this->rateSlider = new QSlider();
        this->rateSlider->setOrientation(Qt::Horizontal);
        this->rateSlider->setObjectName("widgetSlider");
    }
    if(this->pitchLabel == nullptr){
        this->pitchLabel = new QLabel(QStringLiteral("音        高:"));
        this->pitchLabel->setObjectName("widgetNameLabel");
    }
    if(this->pitchSpinBox == nullptr){
        this->pitchSpinBox = new QSpinBox();
        this->pitchSpinBox->setObjectName("widgetSpinBox");
    }
    if(this->pitchSlider == nullptr){
        this->pitchSlider = new QSlider();
        this->pitchSlider->setOrientation(Qt::Horizontal);
        this->pitchSlider->setObjectName("widgetSlider");
    }

    this->addItem(new QSpacerItem(40,20,QSizePolicy::Expanding),0,0,1,2);
    this->addWidget(this->enableLabel,0,2,2,1);
    this->addWidget(this->enableCheckBox,0,3,1,1);
    this->addWidget(this->disenableCheckBox,1,3,1,1);
    this->addWidget(this->engineLabel,2,2,1,1);
    this->addWidget(this->engineComboBox,2,3,1,2);
    this->addWidget(this->languageLabel,3,2,1,1);
    this->addWidget(this->languageComboBox,3,3,1,2);
    this->addWidget(this->ttsLevelLabel,4,2,3,1);
    this->addWidget(this->infoLevelCheckBox,4,3,1,1);
    this->addWidget(this->worningLevelCheckBox,5,3,1,1);
    this->addWidget(this->errorLevelCheckBox,6,3,1,1);
    this->addWidget(this->levelSortLabel,7,2,2,1);
    this->addWidget(this->levelSortCheckBox,7,3,1,1);
    this->addWidget(this->orderCheckBox,8,3,1,1);
    this->addWidget(this->levelBreakLabel,9,2,1,1);
    this->addWidget(this->levelBreakComboBox,9,3,1,2);

    this->addWidget(this->volumeLabel,10,2,1,1);
    this->addWidget(this->volumeSpinBox,10,3,1,1);
    this->addWidget(this->volumeSlider,10,4,1,1);

    this->addWidget(this->rateLabel,11,2,1,1);
    this->addWidget(this->rateSpinBox,11,3,1,1);
    this->addWidget(this->rateSlider,11,4,1,1);

    this->addWidget(this->pitchLabel,12,2,1,1);
    this->addWidget(this->pitchSpinBox,12,3,1,1);
    this->addWidget(this->pitchSlider,12,4,1,1);

    this->addItem(new QSpacerItem(40,40,QSizePolicy::Expanding),0,5,1,2);

    this->setColumnStretch(0,2);
    this->setColumnStretch(4,1);
    this->setColumnStretch(5,2);

    this->setVerticalSpacing(10);
}

void VoiceAlarmWidget::connectSignalAndSlot()
{

}



