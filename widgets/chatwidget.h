#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QDateTime>
#include <QListView>
#include <QAbstractItemModel>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QPicture>
#include <QFontMetrics>
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
class ChatWidgetItemDelegate : public QStyledItemDelegate{
public:
    ChatWidgetItemDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
};

class ChatWidgetModel : public QAbstractItemModel{
public:
    struct ChatMessage{
        QString     text;
        QDateTime   time;
        int         src;
    };


    enum ChatMessageRoles{
        ChatMessageBody = Qt::UserRole + 1,
        ChatMessageTime,
        ChatMessageSrc,
    };

public:
    ChatWidgetModel();

    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QModelIndex parent(const QModelIndex &index) const override;

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void addNewPromptMessage(QString text,int src = -1,QDateTime = QDateTime::currentDateTime());

private:
    QList<ChatMessage>   chatMsgList = {};

};


class ChatWidget : public QListView
{
public:
    ChatWidget(QWidget *parent = nullptr);

private:
    ChatWidgetModel *model = nullptr;
    ChatWidgetItemDelegate *degelate = nullptr;
private:
    void ChatWidgetInit();
    QTimer* timer = nullptr;
    void RestartTimer();
private slots:
    void HandleTimeOut_Slot();
public slots:
    void addNewPromptMessageSlot(QString text,bool parent_isMinimized = false,int src = -1,QDateTime = QDateTime::currentDateTime());
protected:
    bool event(QEvent *e);

};

#endif // CHATWIDGET_H
