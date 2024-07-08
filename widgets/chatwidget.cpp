#include "chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent)
    : QListView(parent)
{
    this->setWindowFlags (this->windowFlags()| Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    ChatWidgetInit();
    this->setAutoScroll(true);
    this->setObjectName("ChatWidget");
    connect(this->timer,&QTimer::timeout,this,&ChatWidget::HandleTimeOut_Slot);
    this->setWindowOpacity(0.8);
    QFile file(QString(":/style/system_cfg.qss"));
    if(file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
        file.close();
    }
}

void ChatWidget::ChatWidgetInit()
{
    if(this->model == nullptr){
        this->model = new ChatWidgetModel();
        this->setModel(this->model);
    }
    if(this->degelate == nullptr){
        this->degelate = new ChatWidgetItemDelegate();
        this->setItemDelegate(this->degelate);
    }
    if(timer == nullptr){
        timer = new QTimer(this);
    }
}

void ChatWidget::RestartTimer()
{
    if(timer != nullptr){
        timer->start(15000);
    }
}

void ChatWidget::HandleTimeOut_Slot()
{
    timer->stop();
    this->setVisible(false);
}

void ChatWidget::addNewPromptMessageSlot(QString text,bool parent_isMinimized, int src, QDateTime time)
{
    if(!this->isHidden()){
        this->setVisible(false);
    }
    if(this->isHidden()&& !parent_isMinimized){
        this->setVisible(true);

    }
    this->scrollToBottom();
    this->model->addNewPromptMessage(text,src,time);
    RestartTimer();
}

bool ChatWidget::event(QEvent *e)
{
    switch(e->type()){
        case QEvent::Wheel:
        case QEvent::Enter:                           // mouse enters widget
        case QEvent::Leave:
        case QEvent::FocusIn:                           // keyboard focus received
        case QEvent::FocusOut:                           // keyboard focus received
        case QEvent::UpdateRequest:                           // keyboard focus received
            RestartTimer();
            break;
        default:break;
    }
    return QListView::event(e);
}


ChatWidgetModel::ChatWidgetModel()
{

}

Qt::ItemFlags ChatWidgetModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemFlag::NoItemFlags;
}

QModelIndex ChatWidgetModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return createIndex(row,column);
}

QModelIndex ChatWidgetModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QModelIndex();
}


int ChatWidgetModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return this->chatMsgList.count();
}

int ChatWidgetModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 1;
}

QVariant ChatWidgetModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row();
    int column = index.column();
    if(row >= 0 && row < this->chatMsgList.count()&& column < 3){
        switch(role){
        case Qt::DisplayRole:{
            return QVariant(this->chatMsgList.at(row).text);
        }case ChatMessageRoles::ChatMessageBody:{
            return QVariant(this->chatMsgList.at(row).text);
        }case ChatMessageRoles::ChatMessageSrc:{
            return QVariant(this->chatMsgList.at(row).src);
        }case ChatMessageRoles::ChatMessageTime:{
            return QVariant(this->chatMsgList.at(row).time);
        }case Qt::TextAlignmentRole:{
            if(this->chatMsgList.at(row).src == -1){
                return Qt::AlignLeft;
            }else{
                return Qt::AlignRight;
            }
        }case Qt::TextColorRole:{
            return QVariant();
        }case Qt:: DecorationRole:{
            if(this->chatMsgList.at(row).src == -1){
                return QVariant(QIcon(":/img/prompt/gcs.png"));
            }else{
                return QVariant(QIcon(":/img/prompt/uav.png"));
            }
            break;
        }case Qt::BackgroundRole:{
            if(this->chatMsgList.at(row).src == -1){
                return QColor(0,100,100,0);
            }else{
                return QColor(0,255,255,0);
            }
        }case Qt::SizeHintRole:{
            return QSize(20,20);
        }
        default:{
            return QVariant();
        }
        }

    }
    return QVariant();
}

bool ChatWidgetModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

void ChatWidgetModel::addNewPromptMessage(QString text, int src, QDateTime time)
{
    ChatMessage msg;
    msg.text = text;
    msg.time = time;
    msg.src = src;
    this->beginResetModel();
    this->chatMsgList.append(msg);
    if(this->chatMsgList.count() > 1000){

        this->chatMsgList.removeFirst();
    }
    this->endResetModel();

}

ChatWidgetItemDelegate::ChatWidgetItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void ChatWidgetItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }

    QString text = index.data(ChatWidgetModel::ChatMessageRoles::ChatMessageBody).toString().toLocal8Bit();
    int src = index.data(ChatWidgetModel::ChatMessageRoles::ChatMessageSrc).toInt();
    QDateTime time = index.data(ChatWidgetModel::ChatMessageRoles::ChatMessageTime).toDateTime();
    QIcon icon = index.data(Qt::DecorationRole).value<QIcon>();
    painter->save();
    if(src == -1){
        /*绘制icon*/
        QRect dst = option.rect;
        dst.setRight(option.rect.right());
        QRect area(0,0,32,32);
        area.moveCenter(dst.center());
        area.moveRight(dst.right());
        QPixmap pixmapPic(icon.pixmap(area.size()));
        painter->drawPixmap(area, pixmapPic);

        /*绘制文字*/
        QRect roundRect = option.rect;
        roundRect.setHeight(option.rect.height() - 30);
        roundRect.setWidth(option.rect.width() * 0.7);
        roundRect.setLeft(option.rect.left() + option.rect.width() * 0.3 );
        roundRect.setRight(area.left());
        roundRect.moveCenter(dst.center());
        roundRect.moveRight(area.left() - 10);

        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(QColor(20,180,20,255));
        painter->setPen(Qt::transparent);
        painter->drawRoundedRect(roundRect, 10, 10);

        QRect timeRect = option.rect;
        timeRect.setRight(roundRect.right());
        timeRect.setBottom(roundRect.top());

        QFont font;//字体属性类对象，可以设置字体的属性
         //设置字体属性
        font.setFamily(QStringLiteral("微软雅黑"));
        font.setPixelSize(11);//设置字体大小
        font.setUnderline(false);//设置下划线
        font.setOverline(false);//设置上划线
        font.setItalic(true);//设置斜体
        font.setBold(false);//设置加粗
//        font.setCapitalization(QFont::SmallCaps);//设置字母大小写
        font.setLetterSpacing(QFont::AbsoluteSpacing,1);//设置字符间距
        painter->setFont(font);//使用字体属性
        painter->setPen(QColor(255,255,255,255));//设置画笔颜色
        painter->drawText(timeRect, Qt::AlignRight | Qt::AlignVCenter,time.toString("yyyy-MM-dd hh:mm:ss"));


        font.setPixelSize(14);//设置字体大小
        font.setUnderline(false);//设置下划线
        font.setOverline(false);//设置上划线
        font.setItalic(false);//设置斜体
        font.setBold(false);//设置加粗
        font.setLetterSpacing(QFont::AbsoluteSpacing,1);//设置字符间距
        painter->setFont(font);//使用字体属性
        painter->setPen(QColor(0,0,0,255));//设置画笔颜色

        QRect textRect = roundRect.adjusted(10,5,-10,-5);
        painter->drawText(textRect,Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap,text);

    }else{

        /*绘制icon*/
        QRect dst = option.rect;
        dst.setLeft(option.rect.left());
        QRect area(0,0,32,32);
        area.moveCenter(dst.center());
        area.moveLeft(dst.left());

        QPixmap pixmapPic(icon.pixmap(area.size()));
        painter->drawPixmap(area, pixmapPic);

        QRect roundRect = option.rect;
        roundRect.setLeft(area.right());
        roundRect.setHeight(option.rect.height() - 30);
        roundRect.setWidth(option.rect.width() * 0.7);
        roundRect.moveCenter(dst.center());
        roundRect.moveLeft(area.right() + 10);

        painter->setRenderHint(QPainter::Antialiasing);

        painter->setBrush(QColor(47,79,79,255));
//        painter->setBrush(QColor(22,25,41,255));
        painter->setPen(Qt::transparent);
        painter->drawRoundedRect(roundRect, 10, 10);

        QRect timeRect = option.rect;
        timeRect.setLeft(roundRect.left());
        timeRect.setBottom(roundRect.top());

        QFont font;//字体属性类对象，可以设置字体的属性
         //设置字体属性
        font.setFamily(QStringLiteral("微软雅黑"));
        font.setPixelSize(11);//设置字体大小
        font.setUnderline(false);//设置下划线
        font.setOverline(false);//设置上划线
        font.setItalic(true);//设置斜体
        font.setBold(false);//设置加粗
//        font.setCapitalization(QFont::SmallCaps);//设置字母大小写
        font.setLetterSpacing(QFont::AbsoluteSpacing,1);//设置字符间距
        painter->setFont(font);//使用字体属性
        painter->setPen(QColor(255,255,255,255));//设置画笔颜色

        painter->drawText(timeRect, Qt::AlignLeft | Qt::AlignVCenter,time.toString("yyyy-MM-dd hh:mm:ss"));

        QRect nameRect = area;

//        nameRect.moveBottom(area.top());

        nameRect.setWidth(area.width()+5);
        nameRect.moveLeft(area.left());
        font.setItalic(false);//设置斜体
        font.setBold(true);//设置加粗
        font.setPixelSize(16);//设置字体大小
        painter->setFont(font);//使用字体属性
        painter->setPen(QColor(255,0,0,255));//设置画笔颜色
        painter->drawText(nameRect, Qt::AlignBottom|Qt::AlignRight,QStringLiteral("%1").arg(QString::number(src)));

        font.setPixelSize(14);//设置字体大小
        font.setUnderline(false);//设置下划线
        font.setOverline(false);//设置上划线
        font.setItalic(false);//设置斜体
        font.setBold(false);//设置加粗
//        font.setCapitalization(QFont::SmallCaps);//设置字母大小写
        font.setLetterSpacing(QFont::AbsoluteSpacing,1);//设置字符间距
        painter->setFont(font);//使用字体属性
        painter->setPen(QColor(255,255,255,255));//设置画笔颜色

        QRect textRect = roundRect.adjusted(10,5,-10,-5);
        painter->drawText(textRect,Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap,text);
//        painter->drawText(textRect,Qt::AlignJustify| Qt::TextLongestVariant,text);

    }

    painter->restore();

}

QSize ChatWidgetItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);

    size.setHeight(80);

    return size;
}
