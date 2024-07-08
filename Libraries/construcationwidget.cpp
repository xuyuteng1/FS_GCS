#include "construcationwidget.h"


ConstrucationListView::ConstrucationListView(QWidget *parent) :QWidget(parent)
{
    widgetInit();
    connectSignalAndSlot();
    this->setAttribute(Qt::WA_QuitOnClose,false);
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    QFile file(QString(":/style/communiicationswidget.qss"));

    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}

QMap<uint8_t, QString> ConstrucationListView::getConstrucationName()
{
    QMap<uint8_t,QString> construcatioMap;
    for(int i = FlyLink::Frame_UNDIFINE;i < FlyLink::FrameEnd ; i++){
        construcatioMap.insert(i,FlyLink::getCopterFrame(i));
    }
    return construcatioMap;
}

QMap<uint8_t, QString> ConstrucationListView::getConstrucationIconPath()
{
    QMap<uint8_t,QString> construcatioIconPathMap;
    for(int i = FlyLink::Frame_UNDIFINE;i < FlyLink::FrameQuad_User_X4 ; i++){
        // 非官方支持构型
        construcatioIconPathMap[i]= QStringLiteral(":/img/frame/Undef.png");
    }

    /* 四旋翼 USER Frame */
    construcatioIconPathMap[FlyLink::FrameQuad_User_X4]          = QStringLiteral(":/img/frame/X4.png");
    construcatioIconPathMap[FlyLink::FrameQuad_User_X4R]         = QStringLiteral(":/img/frame/X4R.png");
    construcatioIconPathMap[FlyLink::FrameQuad_User_I4]          = QStringLiteral(":/img/frame/I4.png");
    construcatioIconPathMap[FlyLink::FrameQuad_User_I4R]         = QStringLiteral(":/img/frame/I4R.png");
    construcatioIconPathMap[FlyLink::FrameQuad_User_H4]          = QStringLiteral(":/img/frame/H4.png");
    /* 六旋翼 USER Frame */
    construcatioIconPathMap[FlyLink::FrameHex_User_I6R]          = QStringLiteral(":/img/frame/I6R.png");
    construcatioIconPathMap[FlyLink::FrameHex_User_I6]           = QStringLiteral(":/img/frame/I6.png");
    construcatioIconPathMap[FlyLink::FrameHex_User_V6]           = QStringLiteral(":/img/frame/V6.png");
    construcatioIconPathMap[FlyLink::FrameHex_User_V6R]          = QStringLiteral(":/img/frame/V6R.png");
    /* 8旋翼 USER Frame */
    construcatioIconPathMap[FlyLink::FrameOctA_User_I8]          = QStringLiteral(":/img/frame/I8.png");
    construcatioIconPathMap[FlyLink::FrameOctA_User_I8R]         = QStringLiteral(":/img/frame/I8R.png");
    construcatioIconPathMap[FlyLink::FrameOctA_User_O8]          = QStringLiteral(":/img/frame/O8.png");
    construcatioIconPathMap[FlyLink::FrameOctA_User_O8R]         = QStringLiteral(":/img/frame/O8R.png");
    /* 4轴8桨 USER Frame */
    construcatioIconPathMap[FlyLink::FrameOctAQuad_User_X8]      = QStringLiteral(":/img/frame/X8.png");
    construcatioIconPathMap[FlyLink::FrameOctAQuad_User_X8R]     = QStringLiteral(":/img/frame/X8R.png");
    construcatioIconPathMap[FlyLink::FrameOctAQuad_User_X8CRP]   = QStringLiteral(":/img/frame/X8CRP.png");
    construcatioIconPathMap[FlyLink::FrameOctAQuad_User_IX8]     = QStringLiteral(":/img/frame/IX8.png");
    construcatioIconPathMap[FlyLink::FrameOctAQuad_User_IX8R]    = QStringLiteral(":/img/frame/IX8R.png"); ///////////////
    /* Y6 3轴6桨 USER Frame */
    construcatioIconPathMap[FlyLink::FrameY6_User_Y6]            = QStringLiteral(":/img/frame/Y6.png");
    construcatioIconPathMap[FlyLink::FrameY6_User_Y6R]           = QStringLiteral(":/img/frame/Y6R.png");
    construcatioIconPathMap[FlyLink::FrameY6_User_IY6]           = QStringLiteral(":/img/frame/IY6.png");
    construcatioIconPathMap[FlyLink::FrameY6_User_IY6R]          = QStringLiteral(":/img/frame/IY6R.png");
    /* 6轴12桨 USER Frame */
    construcatioIconPathMap[FlyLink::FrameDodecaHexA_User_I12R]  = QStringLiteral(":/img/frame/R6I12R.png");
    construcatioIconPathMap[FlyLink::FrameDodecaHexA_User_I12]   = QStringLiteral(":/img/frame/R6I12.png");
    construcatioIconPathMap[FlyLink::FrameDodecaHexA_User_X12]   = QStringLiteral(":/img/frame/R6X12.png");
    construcatioIconPathMap[FlyLink::FrameDodecaHexA_User_X12R]  = QStringLiteral(":/img/frame/R6X12R.png");
    construcatioIconPathMap[FlyLink::FrameDodecaHexA_User_X12CRP]= QStringLiteral(":/img/frame/R6X12CRP.png");

    return construcatioIconPathMap;
}

void ConstrucationListView::widgetInit()
{

    if(this->buttonGroup == nullptr){
        this->buttonGroup = new QButtonGroup();
    }

    if(this->widgetLayout == nullptr){
        this->widgetLayout = new QGridLayout();
    }

    if(this->mainLayout == nullptr){
        this->mainLayout = new QGridLayout;
        this->mainLayout->setMargin(0);
        this->mainLayout->setSpacing(0);
    }



    QMap<uint8_t,QString >construcatioNameMap = getConstrucationName();
    QMap<uint8_t,QString >construcatioIconPathMap = getConstrucationIconPath();

    for(int i = FlyLink::FrameQuad_User_X4; i < FlyLink::FrameEnd;i++){
        this->actionMap.insert( i ,new ToolButton(construcatioNameMap.find(i).value(),  construcatioIconPathMap.find(i).value()));
        this->buttonGroup->addButton(this->actionMap.find(i).value() , i);
    }

    QLabel *r4p4Label = new QLabel(QStringLiteral("四轴四桨"));
    r4p4Label->setObjectName("ConstrucationListViewLabel");

    this->widgetLayout->addWidget(r4p4Label,0,0,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameQuad_User_X4 ).value(),0,1,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameQuad_User_X4R).value(),0,2,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameQuad_User_I4 ).value(),0,3,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameQuad_User_I4R).value(),0,4,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameQuad_User_H4 ).value(),0,5,1,1);

    QLabel *r6p6Label = new QLabel(QStringLiteral("六轴六桨"));
    r4p4Label->setObjectName("ConstrucationListViewLabel");
    this->widgetLayout->addWidget(r6p6Label,1,0,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameHex_User_I6R).value(),1,1,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameHex_User_I6 ).value(),1,2,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameHex_User_V6 ).value(),1,3,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameHex_User_V6R).value(),1,4,1,1);

    QLabel *r8p8Label = new QLabel(QStringLiteral("八轴八桨"));
    r4p4Label->setObjectName("ConstrucationListViewLabel");
    this->widgetLayout->addWidget(r8p8Label,2,0,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameOctA_User_I8  ).value(),2,1,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameOctA_User_I8R ).value(),2,2,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameOctA_User_O8  ).value(),2,3,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameOctA_User_O8R ).value(),2,4,1,1);


    QLabel *r3p6Label = new QLabel(QStringLiteral("三轴六桨"));
    r4p4Label->setObjectName("ConstrucationListViewLabel");
    this->widgetLayout->addWidget(r3p6Label,3,0,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameY6_User_Y6 ).value(),3,1,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameY6_User_Y6R).value(),3,2,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameY6_User_IY6 ).value(),3,3,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameY6_User_IY6R).value(),3,4,1,1);

    QLabel *r4p8Label = new QLabel(QStringLiteral("四轴八桨"));
    r4p4Label->setObjectName("ConstrucationListViewLabel");
    this->widgetLayout->addWidget(r4p8Label,4,0,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameOctAQuad_User_X8    ).value(),4,1,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameOctAQuad_User_X8R   ).value(),4,2,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameOctAQuad_User_X8CRP ).value(),4,3,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameOctAQuad_User_IX8   ).value(),4,4,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameOctAQuad_User_IX8R  ).value(),4,5,1,1);

    QLabel *r6p12Label = new QLabel(QStringLiteral("六轴十二桨"));
    r4p4Label->setObjectName("ConstrucationListViewLabel");

    this->widgetLayout->addWidget(r6p12Label,5,0,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameDodecaHexA_User_I12R  ).value(),5,1,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameDodecaHexA_User_I12   ).value(),5,2,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameDodecaHexA_User_X12   ).value(),5,3,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameDodecaHexA_User_X12R  ).value(),5,4,1,1);
    this->widgetLayout->addWidget(this->actionMap.find(FlyLink::FrameDodecaHexA_User_X12CRP).value(),5,5,1,1);

    this->widgetLayout->setSpacing(0);

    if(w_title == nullptr){
        QPixmap pix(":/img/png/plane.png");
        w_title = new WidgetTitle(pix,QStringLiteral("构型选择"));
        w_title->setMaximumHeight(40);
    }
    this->mainLayout->addWidget(this->w_title,0,0,1,1);
    this->mainLayout->addLayout(this->widgetLayout,1,0,1,1);

    this->mainLayout->setContentsMargins(0,0,0,0);
    this->mainLayout->setSpacing(0);

    this->setLayout(this->mainLayout);
}

void ConstrucationListView::connectSignalAndSlot()
{
    connect(this->buttonGroup,&QButtonGroup::idClicked,this,&ConstrucationListView::buttonGroupChangedSlot);
    connect(this->w_title,&WidgetTitle::signalCloseEvent,this,[=]{this->close();});
}

void ConstrucationListView::buttonGroupChangedSlot(int id)
{
    this->setVisible(false);
    emit construcationChangedSignal(id);
}



ToolButton::ToolButton(QString name, QString path)
{
    this->setText(name);
    this->setIconSize(QSize(140,140));
    this->setIcon(QIcon(path));
    this->setCheckable(true);
    this->setObjectName("ToolButton");
    this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}
