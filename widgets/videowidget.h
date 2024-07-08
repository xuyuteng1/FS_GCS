#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QGridLayout>
class VideoWidget : public QWidget
{
public:
    VideoWidget();
    void addWidget(QWidget *);

private:
    void initWidget();

private:
    QGridLayout *widgetLayout = nullptr;

};

#endif // VIDEOWIDGET_H
