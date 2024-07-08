#ifndef CFG_COMMUNICATIONINTERFACE_H__
#define CFG_COMMUNICATIONINTERFACE_H__

#include <QWidget>
#include <QListView>
#include <QStackedWidget>
#include "widgetitle.h"
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QComboBox>
#include <QListWidget>
#include "uComboBox.h"

class SerialConfigWidget: public QListWidget{
public:
    class SerialConfigWidgetItem : public QWidget{
    public:
        SerialConfigWidgetItem(QString str,uint32_t baud = 115200,int8_t protocol = -1);
        void setCurrentBaud(uint32_t baud);
        void setCurrentProtocol(int8_t protocol);
        uint32_t getCurrentBaud();
        int8_t getCurrentProtocol();
    private:
        QLabel *nameLabel = nullptr;
        QLabel *serialName = nullptr;

        QLabel *baudNameLabel = nullptr;
        UComboBox *baudComboBox = nullptr;
        QLabel *protocalNameLabel = nullptr;
        UComboBox *protocalComboBox = nullptr;

        QHBoxLayout *widgetLayout = nullptr;

    private:
        void widgetInit();

    private:
        QString serialNameStr = "Serial X";
        uint32_t _baud;
        uint8_t  _protocol;
    };


public:
    SerialConfigWidget();
    void clearSerialConfigWidget();
    void addItemWidget(QString name,uint32_t baud,int8_t protocol);
    bool getItemWidgetInfo(QString name,uint32_t& baud,int8_t& protocol);
    int getItemWidgeCount();

private:
    void connectSignalAndSlot();

private:
    QMap<QString,SerialConfigWidgetItem *> serialConfigItemMap;

};

class G_CFG_SerialManager:public QWidget
{
    Q_OBJECT
public:
    G_CFG_SerialManager(QWidget *parent = nullptr);
private:
    QLabel          *titleLabel         = nullptr;
    QGridLayout*    widgetLayout        = nullptr;
private:
    SerialConfigWidget *serialConfigWidget = nullptr;

    QPushButton *upDateButton = nullptr;                        //更新
    QPushButton *selectButton = nullptr;

private:
    void initWidget();
    void connectSignalAndSlot();

protected:

private slots:
    void upDateButtonPressedSlot();
    void selectButtonPressedSlot();
    void handle_DMMM_event(int ev,int linkid = 0);
};


#endif // CFG_COMMUNICATIONINTERFACE_H
