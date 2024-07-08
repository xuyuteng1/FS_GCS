#include "promptwidget.h"

PromptWidget::PromptWidget(QWidget *parent)
    : QListView(parent)
{

    initWidget();

    this->setViewMode(QListView::ListMode);
    this->setFlow(QListView::TopToBottom);

    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setObjectName("PromptWidget");
}

void PromptWidget::initWidget()
{
    if(this->model == nullptr){
        this->model = new PromptWidgetModel();
        this->setModel(this->model);
    }
    if(this->delegate == nullptr){
        this->delegate = new PromptWidgetItemDegelate(this);
        this->setItemDelegate(this->delegate);
    }


    connect(this->delegate,&PromptWidgetItemDegelate::leftButtonPressedSignal,this,&PromptWidget::promptWidgetLeftButtonPressedSignal);
    connect(this->delegate,&PromptWidgetItemDegelate::rightButtonPressedSignal,this,&PromptWidget::promptWidgetRightButtonPressedSignal);

}

int PromptWidget::getPos_y() const
{
    return pos_y;
}

int PromptWidget::getPos_x() const
{
    return pos_x;
}

void PromptWidget::addPromptMsgSlot(int type, QString msgBody, int scr, int dst)
{
    this->model->addNewPromptMessage(type,msgBody);
}

void PromptWidget::updatePromptMsgSlot()
{
    this->model->updatePromptMsg(this->timeout);
    static int i = 0;
//    if(i++ % 10 == 0){
    i++;
    this->model->addNewPromptMessage(i % 5,QStringLiteral("测试") + QString::number(i % 5));
    //    }
}


bool PromptWidget::event(QEvent *e)
{
    if (QEvent::Show == e->type())
    {
        //获取位置
        pos_x = this->geometry().x();
        pos_y = this->geometry().y();
    }
    return QListView::event(e);
}


PromptWidgetModel::PromptWidgetModel()
{


}


Qt::ItemFlags PromptWidgetModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex PromptWidgetModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return createIndex(row,column);
}

QModelIndex PromptWidgetModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QModelIndex();
}

int PromptWidgetModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    switch(this->promptMsgMode){
    case PromptMessageMode::MsgPrompt:
        return this->promptMsgList.count() > 0 ? 1 : 0;
    case PromptMessageMode::MsgDialogue:
        return this->promptMsgList.count();
    }
    return 0;
}

int PromptWidgetModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 1;
}

QVariant PromptWidgetModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row();
    int column = index.column();
    if(row >= 0 && row < this->promptMsgList.count()&& column < 3){
        switch(role){
        case Qt::DisplayRole:{
            return QVariant(this->promptMsgList.at(row).msgBody);
        }
        case PromptMessageRoles::PromptMessageType:{
            return QVariant(this->promptMsgList.at(row).type);
        }case PromptMessageRoles::PromptMessageBody:{
            return QVariant(this->promptMsgList.at(row).msgBody);
        }case PromptMessageRoles::PromptMessageTime:{
            return QVariant(this->promptMsgList.at(row).insertTime);
        }case Qt::TextAlignmentRole:{
            return Qt::AlignCenter;
        }case Qt::TextColorRole:{
            switch(this->promptMsgList.at(row).type){
            case MsgCommond:
                return QColor(255,0,255);
            case MsgCommondReply:
                return QColor(255,255,0);
            case MsgPrompt_T:
                return QColor(255,255,255);
            case MsgWorning:
                return QColor(0,255,255);
            case MsgError:
                return QColor(255,0,0);
            default:
                return QVariant();
            }
        }
        default:{
            return QVariant();
        }
        }

    }
    return QVariant();

}

bool PromptWidgetModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

void PromptWidgetModel::addNewPromptMessage(int type, QString msgBody, QDateTime time)
{
    this->beginResetModel();
    PromptMessage msg;
    msg.type = type;
    msg.msgBody = msgBody;
    msg.insertTime = time;
    this->promptMsgList.insert(0,msg);
    if(this->promptMsgList.count() > 10){
        this->promptMsgList.removeLast();
    }

    this->endResetModel();
}

void PromptWidgetModel::updatePromptMsg(int timeout)
{

}

int PromptWidgetModel::getPromptMsgMode() const
{
    return promptMsgMode;
}

void PromptWidgetModel::setPromptMsgMode(int newPromptMsgMode)
{
    promptMsgMode = newPromptMsgMode;
}



PromptWidgetItemDegelate::PromptWidgetItemDegelate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void PromptWidgetItemDegelate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }

    QString text = index.data(PromptWidgetModel::PromptMessageRoles::PromptMessageBody).toString();
    QColor textColor = index.data(Qt::TextColorRole).value<QColor>();
    QRect dst = option.rect;
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(22,25,41,160));

    painter->setPen(Qt::transparent);
    painter->drawRoundedRect(dst, 23, 23);


    QFont font;//字体属性类对象，可以设置字体的属性
     //设置字体属性
    font.setFamily(QStringLiteral("Microsoft YaHei UI"));
    font.setPixelSize(22);              //设置字体大小
    font.setUnderline(false);            //设置下划线
    font.setOverline(false);            //设置上划线
    font.setItalic(false);               //设置斜体
    font.setBold(false);                //设置加粗
    font.setLetterSpacing(QFont::AbsoluteSpacing,2);//设置字符间距
    painter->setFont(font);//使用字体属性
    painter->setPen(textColor);//设置画笔颜色
    painter->drawText(dst, Qt::AlignCenter,text);



    QRect leftButtonRect = option.rect;

    leftButtonRect.setWidth(dst.width() * 0.1);
    leftButtonRect.setHeight(dst.height() * 0.7);
    leftButtonRect.setLeft(dst.left());
    leftButtonRect.moveCenter(dst.center());
    leftButtonRect.moveLeft(dst.left() + 10);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(255,0,0,160));
    painter->setPen(Qt::transparent);
//    painter->drawRoundedRect(leftButtonRect, 30, 30);
    painter->drawPixmap(leftButtonRect,QPixmap(":/img/png/plane.png"));

    QRect rightButtonRect = leftButtonRect;
    rightButtonRect.setWidth(dst.width() * 0.1);
    rightButtonRect.setHeight(dst.height() * 0.7);
    rightButtonRect.moveCenter(dst.center());
    rightButtonRect.moveRight(dst.right() - 10);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(255,255,0,160));
    painter->setPen(Qt::transparent);
//    painter->drawRoundedRect(rightButtonRect, 30, 30);
    painter->drawPixmap(rightButtonRect,QPixmap(":/img/png/msg.png"));



}

QSize PromptWidgetItemDegelate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);

    size.setHeight(46);

    return size;
}

bool PromptWidgetItemDegelate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(event->type() == QEvent::MouseButtonPress){
        QRect leftButtonRect = option.rect;
        leftButtonRect.setWidth(option.rect.width() * 0.18);
        leftButtonRect.setLeft(option.rect.left());
        leftButtonRect.moveLeft(option.rect.left() + 15);
        leftButtonRect.setBottom(option.rect.bottom());

        QRect rightButtonRect = leftButtonRect;
        rightButtonRect.moveRight(option.rect.right() - 15);
        rightButtonRect.setBottom(option.rect.bottom());

        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QPointF p = mouseEvent->pos(); // 获取鼠标位置

        qDebug()<<p.x()<<p.y()<<leftButtonRect.x()<<leftButtonRect.y()<<leftButtonRect.width()<<leftButtonRect.height();
        if(p.x() >= leftButtonRect.x() && p.x() <= (leftButtonRect.x() + leftButtonRect.width()) &&\
           p.y() >= leftButtonRect.y() && p.y() <= (leftButtonRect.y() + leftButtonRect.height())){
            emit leftButtonPressedSignal();
        }

        if(p.x() >= rightButtonRect.x() && p.x() <= (rightButtonRect.x() + rightButtonRect.width()) &&\
           p.y() >= rightButtonRect.y() && p.y() <= (rightButtonRect.y() + rightButtonRect.height())){
            emit rightButtonPressedSignal();
        }

    }

    return false;
}

