#ifndef PROMPTWIDGET_H
#define PROMPTWIDGET_H

#include <QWidget>
#include <QListView>
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>
#include <QStyledItemDelegate>
#include <QPainter>
class PromptWidgetItemDegelate : public QStyledItemDelegate{
    Q_OBJECT
public:
    PromptWidgetItemDegelate(QObject *parent = nullptr);

    void paint(QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const override;

    bool editorEvent(QEvent *event,QAbstractItemModel *model,const QStyleOptionViewItem &option,const QModelIndex &index) override;
private:


private:


protected:

public:
signals:
    void leftButtonPressedSignal();
    void rightButtonPressedSignal();


};


class PromptWidgetModel : public QAbstractItemModel{
public:
    struct PromptMessage{
        int         type;               //消息类型
        QString     msgBody;            //消息体
        QDateTime   insertTime;         //插入时间
        int         src;                //消息源
        int         dst;                //消息目的
    };


    enum PromptMessageRoles{
        PromptMessageType = Qt::UserRole + 1,
        PromptMessageBody,
        PromptMessageTime,
        PromptMessageSrc,
        PromptMessageDst,
    };

    enum PromptMessageMode{
        MsgPrompt = 0,                  //提示模式
        MsgDialogue,                    //对话模式
    };

    enum PromptMessageType{
        MsgCommond = 0,                 //指令
        MsgCommondReply,                //指令应答
        MsgPrompt_T = 0x10,             //提示
        MsgWorning = 0x40,              //警告
        MsgError = 0xA0,                //错误
    };
public:
    PromptWidgetModel();

    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QModelIndex parent(const QModelIndex &index) const override;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void addNewPromptMessage(int type,QString msgBody,QDateTime = QDateTime::currentDateTime());

    void updatePromptMsg(int timeout);

    int getPromptMsgMode() const;
    void setPromptMsgMode(int newPromptMsgMode);

private:
    QList<PromptMessage> promptMsgList;
    int                  promptMsgMode = 0;

};



class PromptWidget : public QListView
{
    Q_OBJECT
public:
    PromptWidget(QWidget *parent = nullptr);

private:
    void initWidget();

private:
    PromptWidgetModel *model = nullptr;
    PromptWidgetItemDegelate *delegate = nullptr;
    int     timeout = 3000;                 //unit: ms

    int     pos_x = 0;
    int     pos_y = 0;
public slots:
    void addPromptMsgSlot(int type,QString msgBody,int scr = -1,int dst = -1);
    void updatePromptMsgSlot();
public:
    int getPos_x() const;
    int getPos_y() const;

signals:
    void promptWidgetLeftButtonPressedSignal();
    void promptWidgetRightButtonPressedSignal();

protected:
//    void mousePressEvent(QMouseEvent *e);
    bool event(QEvent *e);

};

#endif // PROMPTWIDGET_H
