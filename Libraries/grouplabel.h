#ifndef GROUPLABEL_H
#define GROUPLABEL_H

#include <QGroupBox>
#include <QLabel>
#include <QGridLayout>
#include <QMap>
#include <QStyle>
class  GroupLabel : public QGroupBox
{
public:
    GroupLabel(QString Name,QString unit,QString objectName);
    GroupLabel(QString Name,QString objectName);

    enum GROUPLABELTYPE{
        NameVal = 1,                         /* 名称、值模式 */
        NameValUnit = 2,                     /* 名称、值、单位模式*/
    };

public:

    QString getUnitVal() const;
    void setUnitVal(const QString &value);

    QString getValueVal() const;
    void setValueVal(const QString &value);

private:
    int count = 0;                           /*  QLabel数量 */
    GROUPLABELTYPE type;					 /* groupLabel格式*/
    QString nameVal;
    QString unitVal;
    QString valueVal;

    QLabel *nameLabel = nullptr;						/* 名称框 */
    QLabel *valueLabel = nullptr;						/* 显示值框 */
    QLabel *unitLabel = nullptr;						/* 单位框 */

    QGridLayout *groupLayout = nullptr;                 /* 布局 */
};


class LabelPixmap : public QLabel{
    Q_OBJECT
    Q_PROPERTY(int status READ getStatus WRITE setStatus)
public:
    LabelPixmap();

    int getStatus() const;
    void setStatus(int newStatusVal);
private:
    int     statusVal;

};

class  GroupLabelPixMap : public QGroupBox
{
public:

public:
    /*********************************************************************
    *功  能：该类主要功能为创建一个图形-文字显示控件。此模式主要由qss实现图片显示及切换
    *参  数：Name:文字显示内容
    *       objectName:QGroupBox的objectName,显示图形由objectName对应的qss样式表设计显示，不可为空,默认QGroupBox(this)的objectName传入objectName,
    *                 nameLabel的objectName为传入的objectName + "_Name",pixMapLabel的objectName为objectName + "_Pix"
    *       orientation:图形-文字布局方式，，水平或垂直，水平布局时文字在左，图片在右，垂直布局时文字在下，图片在上
    *       pixmappSize：图片大小，默认32 * 32.
    *说  明：若显示图片有切换需求，应将statusEnable置位true
    *示  例：GroupLabelPixMap(QStringLiteral("示例"),"StatusPiixmapLabel",true);
    *
    *       qss样式:
    *       QLabel#StatusPiixmapLabel_Pix[status="0"]{
    *            border-image:url(:/img/image0.png)
    *       }
    *       QLabel#StatusPiixmapLabel_Pix[status="1"]{
    *            border-image:url(:/img/image1.png)
    *       }
    *
    *       修改样式调用
    *       setStatusVal();
    **********************************************************************/
    GroupLabelPixMap(QString name,QString objectName,Qt::Orientation orientation = Qt::Horizontal,QSize pixmappSize = QSize(32,32));


public:
    void setStatus(int status);

private:
    QLabel  *nameLabel = nullptr;						/* 名称框 */
    LabelPixmap     *pixMapLabel = nullptr;
    QGridLayout *groupLayout = nullptr;

private:
    QString nameVal;

};




#endif // GROUPLABEL_H
