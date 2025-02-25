﻿#pragma execution_character_set("utf-8")

#include "battery.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

Battery::Battery(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    alarmValue = 30;
    step = 0.5;

    borderWidth = 2;
    borderRadius = 3;
    bgRadius = 3;
    headRadius = 3;

    borderColorStart = QColor(200, 200, 200);
    borderColorEnd = QColor(150, 150, 150);
    alarmColorStart = QColor(250, 87, 103);
    alarmColorEnd = QColor(230, 87, 103);
    normalColorStart = QColor(14, 185, 112);
    normalColorEnd = QColor(14, 255, 112);

    isForward = false;
    currentValue = 0;

    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
}

Battery::~Battery()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void Battery::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制边框
    drawBorder(&painter);
    //绘制背景
    drawBg(&painter);
    //绘制头部
    drawHead(&painter);
}

void Battery::drawBorder(QPainter *painter)
{
    painter->save();

    double headWidth = width() / 15;
    double batteryWidth = width() - headWidth;

    //绘制电池边框
    QPointF topLeft(borderWidth, borderWidth);
    QPointF bottomRight(batteryWidth, height() - borderWidth);
    batteryRect = QRectF(topLeft, bottomRight);

    painter->setPen(QPen(borderColorStart, borderWidth));
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundedRect(batteryRect, borderRadius, borderRadius);

    painter->restore();
}

void Battery::drawBg(QPainter *painter)
{
    if (value == minValue) {
        return;
    }

    painter->save();

    QLinearGradient batteryGradient(QPointF(0, 0), QPointF(0, height()));
    if (currentValue <= alarmValue) {
        batteryGradient.setColorAt(0.0, alarmColorStart);
        batteryGradient.setColorAt(1.0, alarmColorEnd);
    } else {
        batteryGradient.setColorAt(0.0, normalColorStart);
        batteryGradient.setColorAt(1.0, normalColorEnd);
    }

    int margin = qMin(width(), height()) / 20;
    double unit = (batteryRect.width() - (margin * 2)) / 100;
    double width = currentValue * unit;
    QPointF topLeft(batteryRect.topLeft().x() + margin, batteryRect.topLeft().y() + margin);
    QPointF bottomRight(width + margin + borderWidth, batteryRect.bottomRight().y() - margin);
    QRectF rect(topLeft, bottomRight);

    painter->setPen(Qt::NoPen);
    painter->setBrush(batteryGradient);
    painter->drawRoundedRect(rect, bgRadius, bgRadius);

    painter->restore();
}

void Battery::drawHead(QPainter *painter)
{
    painter->save();

    QPointF headRectTopLeft(batteryRect.topRight().x(), height() / 3);
    QPointF headRectBottomRight(width(), height() - height() / 3);
    QRectF headRect(headRectTopLeft, headRectBottomRight);

    QLinearGradient headRectGradient(headRect.topLeft(), headRect.bottomLeft());
    headRectGradient.setColorAt(0.0, borderColorStart);
    headRectGradient.setColorAt(1.0, borderColorEnd);

    painter->setPen(Qt::NoPen);
    painter->setBrush(headRectGradient);
    painter->drawRoundedRect(headRect, headRadius, headRadius);

    painter->restore();
}

void Battery::updateValue()
{
    if (isForward) {
        currentValue -= step;
        if (currentValue <= value) {
            currentValue = value;
            timer->stop();
        }
    } else {
        currentValue += step;
        if (currentValue >= value) {
            currentValue = value;
            timer->stop();
        }
    }

    this->update();
}

double Battery::getMinValue() const
{
    return this->minValue;
}

double Battery::getMaxValue() const
{
    return this->maxValue;
}

double Battery::getValue() const
{
    return this->value;
}

double Battery::getAlarmValue() const
{
    return this->alarmValue;
}

double Battery::getStep() const
{
    return this->step;
}

int Battery::getBorderWidth() const
{
    return this->borderWidth;
}

int Battery::getBorderRadius() const
{
    return this->borderRadius;
}

int Battery::getBgRadius() const
{
    return this->bgRadius;
}

int Battery::getHeadRadius() const
{
    return this->headRadius;
}

QColor Battery::getBorderColorStart() const
{
    return this->borderColorStart;
}

QColor Battery::getBorderColorEnd() const
{
    return this->borderColorEnd;
}

QColor Battery::getAlarmColorStart() const
{
    return this->alarmColorStart;
}

QColor Battery::getAlarmColorEnd() const
{
    return this->alarmColorEnd;
}

QColor Battery::getNormalColorStart() const
{
    return this->normalColorStart;
}

QColor Battery::getNormalColorEnd() const
{
    return this->normalColorEnd;
}

QSize Battery::sizeHint() const
{
    return QSize(150, 80);
}

QSize Battery::minimumSizeHint() const
{
    return QSize(30, 10);
}

void Battery::setRange(double minValue, double maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    //值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        setValue(minValue);
    } else if (value > maxValue) {
        setValue(maxValue);
    }

    this->update();
}

void Battery::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void Battery::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void Battery::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void Battery::setValue(double value)
{
    //值和当前值一致则无需处理
    if (value == this->value) {
        return;
    }

    //值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        value = minValue;
    } else if (value > maxValue) {
        value = maxValue;
    }

    if (value > currentValue) {
        isForward = false;
    } else if (value < currentValue) {
        isForward = true;
    } else {
        this->value = value;
        this->update();
        return;
    }

    this->value = value;
    this->update();
    emit valueChanged(value);
    timer->stop();
    timer->start();
}

void Battery::setValue(int value)
{
    setValue((double)value);
}

void Battery::setAlarmValue(double alarmValue)
{
    if (this->alarmValue != alarmValue) {
        this->alarmValue = alarmValue;
        this->update();
    }
}

void Battery::setAlarmValue(int alarmValue)
{
    setAlarmValue((double)alarmValue);
}

void Battery::setStep(double step)
{
    if (this->step != step) {
        this->step = step;
        this->update();
    }
}

void Battery::setStep(int step)
{
    setStep((double)step);
}

void Battery::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        this->update();
    }
}

void Battery::setBorderRadius(int borderRadius)
{
    if (this->borderRadius != borderRadius) {
        this->borderRadius = borderRadius;
        this->update();
    }
}

void Battery::setBgRadius(int bgRadius)
{
    if (this->bgRadius != bgRadius) {
        this->bgRadius = bgRadius;
        this->update();
    }
}

void Battery::setHeadRadius(int headRadius)
{
    if (this->headRadius != headRadius) {
        this->headRadius = headRadius;
        this->update();
    }
}

void Battery::setBorderColorStart(const QColor &borderColorStart)
{
    if (this->borderColorStart != borderColorStart) {
        this->borderColorStart = borderColorStart;
        this->update();
    }
}

void Battery::setBorderColorEnd(const QColor &borderColorEnd)
{
    if (this->borderColorEnd != borderColorEnd) {
        this->borderColorEnd = borderColorEnd;
        this->update();
    }
}

void Battery::setAlarmColorStart(const QColor &alarmColorStart)
{
    if (this->alarmColorStart != alarmColorStart) {
        this->alarmColorStart = alarmColorStart;
        this->update();
    }
}

void Battery::setAlarmColorEnd(const QColor &alarmColorEnd)
{
    if (this->alarmColorEnd != alarmColorEnd) {
        this->alarmColorEnd = alarmColorEnd;
        this->update();
    }
}

void Battery::setNormalColorStart(const QColor &normalColorStart)
{
    if (this->normalColorStart != normalColorStart) {
        this->normalColorStart = normalColorStart;
        this->update();
    }
}

void Battery::setNormalColorEnd(const QColor &normalColorEnd)
{
    if (this->normalColorEnd != normalColorEnd) {
        this->normalColorEnd = normalColorEnd;
        this->update();
    }
}

