#pragma execution_character_set("utf-8")

#include "gaugeprogressbar.h"
#include "qpainter.h"
#include "qevent.h"
#include "qmath.h"
#include "qpropertyanimation.h"
#include "qdatetime.h"
#include "qdebug.h"

GaugeProgressBar::GaugeProgressBar(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    precision = 0;

    startAngle = 0;
    endAngle = 0;

    bgColor = QColor(180, 180, 180,100);
    progressColor = QColor(255, 255, 255,200);
    progressBgColor = QColor(255, 255, 255,20);
    circleColorStart = QColor(50, 50, 50,20);
    circleColorEnd = QColor(50, 50, 50,20);
    textColor = QColor(200, 200, 200,0);

    showPointer = true;
    showValue = false;
    pointerStyle = PointerStyle_Circle;

    hover = false;
    radiusCoverCircle = 85;
    radiusCircle = 82;

    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    animation = new QPropertyAnimation(this, "");
    animation->setStartValue(0);
    animation->setEndValue(10);
    animation->setDuration(300);
    connect(animation, SIGNAL(valueChanged(QVariant)), this, SLOT(updateRadius(QVariant)));

    setFont(QFont("Arial", 9));
}

GaugeProgressBar::~GaugeProgressBar()
{

}

void GaugeProgressBar::paintEvent(QPaintEvent *)
{
    // qDebug()<<"GaugeProgressBar paintEvent";
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制背景
    drawBg(&painter);
    //绘制饼圆
    drawColorPie(&painter);
    //绘制覆盖圆 用以遮住饼圆多余部分
    drawCoverCircle(&painter);
    //绘制中心圆
    drawCircle(&painter);

    //根据指示器形状绘制指示器
    if (pointerStyle == PointerStyle_Circle) {
        drawPointerCircleBase(&painter);
        drawPointerCircle(&painter);
    } else if (pointerStyle == PointerStyle_Indicator) {
        drawPointerIndicator(&painter);
    } else if (pointerStyle == PointerStyle_IndicatorR) {
        drawPointerIndicatorR(&painter);
    } else if (pointerStyle == PointerStyle_Triangle) {
        drawPointerTriangle(&painter);
    }

    if(lastX != this->xValue || lastY != this->yValue){
        drawPointerCircle(&painter);
        update();
    }

    //绘制当前值
    drawText(&painter);
}

void GaugeProgressBar::drawBg(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
    QPen pen(QColor(255,255,255));
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
}

void GaugeProgressBar::drawColorPie(QPainter *painter)
{
    int radius = 95;
    painter->save();
    painter->setPen(Qt::NoPen);
    QRectF rect(-radius, -radius, radius * 2, radius * 2);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0 - startAngle - endAngle;
    double angleCurrent = angleAll * ((value - minValue) / (maxValue - minValue));
    double angleOther = angleAll - angleCurrent;

    painter->restore();

}

void GaugeProgressBar::drawCoverCircle(QPainter *painter)
{
    int radius = radiusCoverCircle;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();

    QPen pen(QColor(180,180,180));
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

}

void GaugeProgressBar::drawCircle(QPainter *painter)
{
    int radius = radiusCircle;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(0, -radius, 0, radius);
    bgGradient.setColorAt(0.0, circleColorStart);
    bgGradient.setColorAt(1.0, circleColorEnd);
    painter->setBrush(bgGradient);

    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();


}

void GaugeProgressBar::drawPointerCircle(QPainter *painter)
{
    if (!showPointer) {
        return;
    }
    int radius = 10;
    int motionRadius = 70;
    double stepX = (maxXValue - minXValue) / static_cast<double>(motionRadius * 2);
    double xValue_T = (this->xValue) / stepX;

    double stepY = (maxYValue - minYValue) / static_cast<double>(motionRadius * 2);
    double yValue_T = (this->yValue) / stepY;

    double degRotate = atan(static_cast<double>(xValue_T)/static_cast<double>(yValue_T));

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(progressColor);

    if(xValue_T == 0 && yValue_T == 0){
        painter->drawEllipse(0 - radius,0 - radius, radius * 2, radius * 2);
    }else{
        if(xValue_T > 0){
            if(yValue_T < 0){
                painter->drawEllipse(0 - radius - (sin(degRotate) * xValue_T),0 - radius - (cos(degRotate) * yValue_T), radius * 2, radius * 2);
            }else{
                painter->drawEllipse(0 - radius + (sin(degRotate) * xValue_T),0 - radius - (cos(degRotate) * yValue_T), radius * 2, radius * 2);
            }
        }else{
            if(yValue_T < 0){
                painter->drawEllipse(0 - radius + (sin(degRotate) * xValue_T),0 - radius - (cos(degRotate) * yValue_T), radius * 2, radius * 2);
            }else{
                painter->drawEllipse(0 - radius - (sin(degRotate) * xValue_T),0 - radius - (cos(degRotate) * yValue_T), radius * 2, radius * 2);
            }
        }
    }
    painter->restore();
}


void GaugeProgressBar::drawPointerCircleBase(QPainter *painter)
{

    if (!showPointer) {
        return;
    }

    int radius = 14;

    painter->save();
    painter->setPen(Qt::NoPen);



    painter->setBrush(QColor(60, 60, 60,150));
    painter->drawEllipse(0 - radius,0 - radius, radius * 2, radius * 2);

    painter->restore();


}

void GaugeProgressBar::drawPointerIndicator(QPainter *painter)
{
    if (!showPointer) {
        return;
    }

    int radius = radiusCircle - 15;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(progressColor);

    QPolygon pts;
    pts.setPoints(3, -8, 0, 8, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    //绘制中心圆点
    radius = radius / 4;
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void GaugeProgressBar::drawPointerIndicatorR(QPainter *painter)
{
    if (!showPointer) {
        return;
    }

    int radius = radiusCircle - 15;
    painter->save();
    painter->setPen(progressColor);
    painter->setBrush(progressColor);

    QPolygon pts;
    pts.setPoints(3, -8, 0, 8, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    //增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    //绘制中心圆点
    radius = radius / 4;
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void GaugeProgressBar::drawPointerTriangle(QPainter *painter)
{
    if (!showPointer) {
        return;
    }

    int radius = 20;
    int offset = radiusCircle - 25;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(progressColor);

    QPolygon pts;
    pts.setPoints(3, -radius / 2, offset, radius / 2, offset, 0, radius + offset);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (value - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void GaugeProgressBar::drawText(QPainter *painter)
{
    if (!showValue) {
        return;
    }

    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QFont font = painter->font();

    if (showPointer) {
        font.setPixelSize(radius - 50);
    } else {
        font.setPixelSize(radius - 15);
    }

    font.setBold(true);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg((double)value, 0, 'f', precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);
    painter->restore();
}

double GaugeProgressBar::getYValue() const
{
    return yValue;
}

void GaugeProgressBar::setYValue(double newYValue)
{
    yValue = newYValue;
    if(lastX != this->xValue || lastY != this->yValue){
        emit valueChangedSignal(static_cast<int>(this->xValue),static_cast<int>(this->yValue));
        this->update();
    }
}

double GaugeProgressBar::getXValue() const
{
    return xValue;
}

void GaugeProgressBar::setXValue(double newXValue)
{
    xValue = newXValue;
    if(lastX != this->xValue || lastY != this->yValue){
        emit valueChangedSignal(static_cast<int>(this->xValue),static_cast<int>(this->yValue));
        this->update();
    }
}

double GaugeProgressBar::getMaxYValue() const
{
    return maxYValue;
}

void GaugeProgressBar::setMaxYValue(double newMaxYValue)
{
    maxYValue = newMaxYValue;
}

void GaugeProgressBar::setMinYValue(double newMinYValue)
{
    minYValue = newMinYValue;
}

double GaugeProgressBar::getMinYValue() const
{
    return minYValue;
}

double GaugeProgressBar::getMaxXValue() const
{
    return maxXValue;
}

void GaugeProgressBar::setMaxXValue(double newMaxXValue)
{
    maxXValue = newMaxXValue;
}

double GaugeProgressBar::getMinXValue() const
{
    return minXValue;
}

void GaugeProgressBar::setMinXValue(double newMinXValue)
{
    minXValue = newMinXValue;
}

void GaugeProgressBar::setEasingCurve()
{
    //随机选择一种动画效果
    int index = qrand() % 40;
    animation->setEasingCurve((QEasingCurve::Type)index);
}

void GaugeProgressBar::updateRadius(QVariant radius)
{
    //如果鼠标悬停则逐渐变小,鼠标移开则逐渐变大直到恢复
    int step = radius.toInt();

    if (hover) {
        radiusCoverCircle = 85 - step;
        radiusCircle = 80 - step;
    } else {
        radiusCoverCircle = 75 + step;
        radiusCircle = 70 + step;
    }

    update();
}

void GaugeProgressBar::setPressedValue(QPointF pressedPoint)
{

    double xVal = 0;
    double yVal = 0;

    if(pressedPoint.x() < (this->width() / 2 - this->radiusCoverCircle)){
        xVal = this->minXValue;
    }else{
        if(pressedPoint.x() > this->width() / 2 + this->radiusCoverCircle){
            xVal = this->maxXValue;
        }else{
            if(pressedPoint.x() > this->width() / 2){
                xVal = (pressedPoint.x() - this->width() / 2) / this->radiusCoverCircle * 100;
            }else{
                xVal = -( this->width() / 2 - pressedPoint.x()) / this->radiusCoverCircle * 100;
            }
        }
    }

    if(pressedPoint.y() < (this->height() / 2 - this->radiusCoverCircle)){
        yVal = this->maxYValue;
    }else{
        if(pressedPoint.y() > this->height() / 2 + this->radiusCoverCircle){
            yVal = this->minYValue;
        }else{
            if(pressedPoint.y() > this->height() / 2){
                yVal = (pressedPoint.y() - this->height() / 2) / -this->radiusCoverCircle * 100;
            }else{
                yVal = -( this->height() / 2 - pressedPoint.y()) / -this->radiusCoverCircle * 100;
            }
        }
    }


    this->setXValue(xVal);
    this->setYValue(yVal);


}

double GaugeProgressBar::getMinValue() const
{
    return this->minValue;
}

double GaugeProgressBar::getMaxValue() const
{
    return this->maxValue;
}

double GaugeProgressBar::getValue() const
{
    return this->value;
}

int GaugeProgressBar::getPrecision() const
{
    return this->precision;
}

int GaugeProgressBar::getStartAngle() const
{
    return this->startAngle;
}

int GaugeProgressBar::getEndAngle() const
{
    return this->endAngle;
}

QColor GaugeProgressBar::getBgColor() const
{
    return this->bgColor;
}

QColor GaugeProgressBar::getProgressColor() const
{
    return this->progressColor;
}

QColor GaugeProgressBar::getProgressBgColor() const
{
    return this->progressBgColor;
}

QColor GaugeProgressBar::getCircleColorStart() const
{
    return this->circleColorStart;
}

QColor GaugeProgressBar::getCircleColorEnd() const
{
    return this->circleColorEnd;
}

QColor GaugeProgressBar::getTextColor() const
{
    return this->textColor;
}

bool GaugeProgressBar::getShowPointer() const
{
    return this->showPointer;
}

bool GaugeProgressBar::getShowValue() const
{
    return this->showValue;
}

GaugeProgressBar::PointerStyle GaugeProgressBar::getPointerStyle() const
{
    return this->pointerStyle;
}

QSize GaugeProgressBar::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugeProgressBar::minimumSizeHint() const
{
    return QSize(20, 20);
}

void GaugeProgressBar::setRange(double minValue, double maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    if (value < minValue || value > maxValue) {
        setValue(value);
    }

    update();
}

void GaugeProgressBar::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void GaugeProgressBar::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void GaugeProgressBar::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void GaugeProgressBar::setValue(double value)
{
    //值小于最小值或者值大于最大值或者值和当前值一致则无需处理
    if (value < minValue || value > maxValue || value == this->value) {
        return;
    }

    this->value = value;
    emit valueChanged(value);
    update();
}

void GaugeProgressBar::setValue(int value)
{
    setValue((double)value);
}

void GaugeProgressBar::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        update();
    }
}

void GaugeProgressBar::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        update();
    }
}

void GaugeProgressBar::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        update();
    }
}

void GaugeProgressBar::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void GaugeProgressBar::setProgressColor(const QColor &progressColor)
{
    if (this->progressColor != progressColor) {
        this->progressColor = progressColor;
        update();
    }
}

void GaugeProgressBar::setProgressBgColor(const QColor &progressBgColor)
{
    if (this->progressBgColor != progressBgColor) {
        this->progressBgColor = progressBgColor;
        update();
    }
}

void GaugeProgressBar::setCircleColorStart(const QColor &circleColorStart)
{
    if (this->circleColorStart != circleColorStart) {
        this->circleColorStart = circleColorStart;
        update();
    }
}

void GaugeProgressBar::setCircleColorEnd(const QColor &circleColorEnd)
{
    if (this->circleColorEnd != circleColorEnd) {
        this->circleColorEnd = circleColorEnd;
        update();
    }
}

void GaugeProgressBar::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void GaugeProgressBar::setShowPointer(bool showPointer)
{
    if (this->showPointer != showPointer) {
        this->showPointer = showPointer;
        update();
    }
}

void GaugeProgressBar::setShowValue(bool showValue)
{
    if (this->showValue != showValue) {
        this->showValue = showValue;
        update();
    }
}

void GaugeProgressBar::setPointerStyle(GaugeProgressBar::PointerStyle pointerStyle)
{
    if (this->pointerStyle != pointerStyle) {
        this->pointerStyle = pointerStyle;
        update();
    }
}
void GaugeProgressBar::enterEvent(QEvent *)
{
    hover = true;
    animation->stop();
    animation->start();
}

void GaugeProgressBar::leaveEvent(QEvent *)
{
    hover = false;
    animation->stop();
    animation->start();
}

void GaugeProgressBar::mousePressEvent(QMouseEvent *e)
{
    pressed = true;
    setPressedValue(e->pos());
}

void GaugeProgressBar::mouseReleaseEvent(QMouseEvent *)
{
    pressed = false;
    setPressedValue(QPointF(this->width() / 2,this->height() / 2));
}

void GaugeProgressBar::mouseMoveEvent(QMouseEvent *e)
{
    if (pressed) {
        setPressedValue(e->pos());
    }
}
