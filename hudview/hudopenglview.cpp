#include "hudopenglview.h"
#include "DMMM.h"
HUDOpenGLView::HUDOpenGLView(QWidget *parent) : QOpenGLWidget(parent)
{
//    this->setWindowFlags (this->windowFlags()| Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);
    this->setFixedSize(339,253);
    this->setContentsMargins(0,0,0,0);
}

float HUDOpenGLView::getAltitude() const
{
    return altitude;
}

void HUDOpenGLView::setAltitude(float newAltitude)
{
    if(this->altitude != newAltitude){
        altitude = newAltitude;
    }
}

float HUDOpenGLView::getTargetAltitude() const
{
    return targetAltitude;
}

void HUDOpenGLView::setTargetAltitude(float newTargetAltitude)
{
    if(this->targetAltitude != newTargetAltitude){
        targetAltitude = newTargetAltitude;
    }
}

float HUDOpenGLView::getRoll() const
{
    return roll;
}

void HUDOpenGLView::setRoll(float newRoll)
{
    if(this->roll != newRoll){
        roll = newRoll;
    }
}

float HUDOpenGLView::getTargetRoll() const
{
    return targetRoll;
}

void HUDOpenGLView::setTargetRoll(float newTargetRoll)
{
    if(this->targetRoll != newTargetRoll){
        targetRoll = newTargetRoll;
    }
}

float HUDOpenGLView::getHeading() const
{
    return heading;
}

void HUDOpenGLView::setHeading(float newHeading)
{
    if(this->heading != newHeading){
        heading = newHeading;
    }
}

float HUDOpenGLView::getTargetHeading() const
{
    return targetHeading;
}

void HUDOpenGLView::setTargetHeading(float newTargetHeading)
{
    if(this->targetHeading != newTargetHeading){
        targetHeading = newTargetHeading;
    }
}

float HUDOpenGLView::getPitch() const
{
    return pitch;
}

void HUDOpenGLView::setPitch(float newPitch)
{
    if(this->pitch != newPitch){
        pitch = newPitch;
    }
}

float HUDOpenGLView::getTargetPitch() const
{
    return targetPitch;
}

void HUDOpenGLView::setTargetPitch(float newTargetPitch)
{
    if(this->targetPitch != newTargetPitch){
        targetPitch = newTargetPitch;
    }
}

float HUDOpenGLView::getSpeed() const
{
    return speed;
}

void HUDOpenGLView::setSpeed(float newSpeed)
{
    if(this->speed != newSpeed){
        speed = newSpeed;
    }
}

float HUDOpenGLView::getTargetSpeed() const
{
    return targetSpeed;
}

void HUDOpenGLView::setTargetSpeed(float newTargetSpeed)
{
    if(this->targetSpeed != newTargetSpeed){
        targetSpeed = newTargetSpeed;
    }
}


void HUDOpenGLView::drawBackGround()
{
    QVector<QVector3D> position;
    position.append(QVector3D( 1.0f,  1.0f, 1.0f));
    position.append(QVector3D(-1.0f,  1.0f, 1.0f));
    position.append(QVector3D(-1.0f, -1.0f, 1.0f));
    position.append(QVector3D( 1.0f, -1.0f, 1.0f));

    QVector<QVector4D> color;
    color.append(rbgaToVector4D(this->background_sky));
    color.append(rbgaToVector4D(this->background_sky));
    color.append(rbgaToVector4D(this->background_sky));
    color.append(rbgaToVector4D(this->background_sky));

    drawGraphics(position,color);

    position.clear();
    color.clear();
    /*计算第三点、第四点*/

    int roll = static_cast<int>(this->roll);
    int pitch = 0 - this->pitch;

    if(roll / 90 % 2 == 0){           //起点在1，3象限
        if(static_cast<float>(qTan((roll % 180) * M_PI / 180)) * (1.0f - pitch * this->pitchScale) > 1.0f - pitch * this->pitchScale){           /*45°~90°段 或者 225°到270°段*/
            if(this->roll < 180){           //第一象限
                position.append(QVector3D(static_cast<float>(qTan((90 - roll % 90) * M_PI / 180)) * (1.0f + pitch * this->pitchScale), - 1.0f, 1.0f));
                position.append(QVector3D(-static_cast<float>(qTan((90 - roll % 90) * M_PI / 180)) * (1.0f - pitch * this->pitchScale),  1.0f, 1.0f));
                position.append(QVector3D(-1.0f,  1.0f, 1.0f));
                position.append(QVector3D(-1.0f, -1.0f, 1.0f));
            }else{                          //第三象限
                position.append(QVector3D(- static_cast<float>(qTan((90 - roll % 90) * M_PI / 180)) * (1.0f - pitch * this->pitchScale),  1.0f, 1.0f));
                position.append(QVector3D( static_cast<float>(qTan((90 - roll % 90) * M_PI / 180)) * (1.0f + pitch * this->pitchScale), -1.0f, 1.0f));
                position.append(QVector3D(1.0f, -1.0f, 1.0f));
                position.append(QVector3D(1.0f,  1.0f, 1.0f));
            }
        }else{                              /*0°~45°段 或者 180°到225°段*/
            if(roll < 180){
                position.append(QVector3D(1.0f, (pitch * this->pitchScale - static_cast<float>(qTan((roll % 90)* M_PI / 180)) * 1.0f), 1.0f));
                position.append(QVector3D(-1.0f, (pitch * this->pitchScale + static_cast<float>(qTan((roll % 90)* M_PI / 180)) * 1.0f), 1.0f));
                position.append(QVector3D(-1.0f, -1.0f, 1.0f));
                position.append(QVector3D(1.0f, -1.0f, 1.0f));
            }else{
                position.append(QVector3D(-1.0f,(pitch * this->pitchScale + static_cast<float>(qTan((roll % 90)* M_PI / 180)) * 1.0f), 1.0f));
                position.append(QVector3D(1.0f,(pitch * this->pitchScale - static_cast<float>(qTan((roll % 90)* M_PI / 180)) * 1.0f), 1.0f));
                position.append(QVector3D(1.0f,1.0f, 1.0f));
                position.append(QVector3D(-1.0f,1.0f, 1.0f));
            }
        }
    }else{                                  //起点在 2，4象限
        if(pitch * this->pitchScale + static_cast<float>(qTan((roll % 180) * M_PI / 180)) * (1.0f + pitch * this->pitchScale) < -1.0f - pitch * this->pitchScale){
            if(this->roll < 180){           //第二象限
                position.append(QVector3D(-static_cast<float>(qTan((roll % 90) * M_PI / 180)) * (1.0f + pitch * this->pitchScale), -1.0f, 1.0f));
                position.append(QVector3D(static_cast<float>(qTan((roll % 90) * M_PI / 180)) * (1.0f - pitch * this->pitchScale), 1.0f, 1.0f));
                position.append(QVector3D(-1.0f, 1.0f, 1.0f));
                position.append(QVector3D(-1.0f, -1.0f, 1.0f));
            }else{                          //第四象限
                position.append(QVector3D( static_cast<float>(qTan((roll % 90) * M_PI / 180)) * (1.0f - pitch * this->pitchScale), 1.0f, 1.0f));
                position.append(QVector3D(- static_cast<float>(qTan((roll % 90) * M_PI / 180)) * (1.0f + pitch * this->pitchScale), -1.0f, 1.0f));
                position.append(QVector3D(1.0f, -1.0f, 1.0f));
                position.append(QVector3D(1.0f, 1.0f, 1.0f));
            }
        }else{
            if(this->roll < 180){
                position.append(QVector3D(-1.0f, (pitch * this->pitchScale - static_cast<float>(qTan((90 - roll % 90)* M_PI / 180)) * 1.0f), 1.0f));
                position.append(QVector3D(1.0f, (pitch * this->pitchScale + static_cast<float>(qTan((90 - roll % 90)* M_PI / 180)) * 1.0f), 1.0f));
                position.append(QVector3D(1.0f, 1.0f, 1.0f));
                position.append(QVector3D(-1.0f, 1.0f, 1.0f));

            }else{
                position.append(QVector3D(1.0f, (pitch * this->pitchScale + static_cast<float>(qTan((90 - roll % 90)* M_PI / 180)) * 1.0f), 1.0f));
                position.append(QVector3D(- 1.0f, (pitch * this->pitchScale - static_cast<float>(qTan((90 - roll % 90)* M_PI / 180)) * 1.0f), 1.0f));
                position.append(QVector3D(-1.0f, -1.0f, 1.0f));
                position.append(QVector3D( 1.0f, -1.0f, 1.0f));
            }
        }
    }



    color.append(rbgaToVector4D(this->background_land));
    color.append(rbgaToVector4D(this->background_land));
    color.append(rbgaToVector4D(this->background_land));
    color.append(rbgaToVector4D(this->background_land));

    drawGraphics(position,color);
}

void HUDOpenGLView::drawScale_pitch()
{
    glEnable(GL_LINE_SMOOTH);           //启用线宽调整
    QVector<QVector3D> position;
    position.append(QVector3D( 0.0f,  0.6f, 1.0f));             /*中心垂直线*/
    position.append(QVector3D( 0.0f,  -0.6f, 1.0f));

    QVector<QVector4D> color;
    color.append(rbgaToVector4D(this->color_scale));
    color.append(rbgaToVector4D(this->color_scale));

    drawLines(position,color);

    QVector<QVector3D> lineositionNum;
    QVector<QVector4D> lineColorNum;
    QVector<QVector2D> texture;
    /*绘制俯仰*/

    int pitch = 0 - this->pitch;
    for(int i = -9; i < 9; i++){
        if((i * 10 + pitch) * this->pitchScale > 0.6f || (i * 10 + pitch) * this->pitchScale < -0.6f){
            //此处添加越界检查
            continue;
        }
        /*绘制俯仰刻度值*/
//        if(i % 2 == 0){
        lineositionNum.append(QVector3D(0.25f - 0.06f,i * 10.0f * pitchScale + static_cast<float>(pitch) * pitchScale + 0.06f,1.0f));
        lineositionNum.append(QVector3D(0.25f - 0.06f,i * 10.0f * pitchScale + static_cast<float>(pitch) * pitchScale - 0.06f,1.0f));
        lineositionNum.append(QVector3D(0.25f + 0.06f,i * 10.0f * pitchScale + static_cast<float>(pitch) * pitchScale + 0.06f,1.0f));
        lineositionNum.append(QVector3D(0.25f + 0.06f,i * 10.0f * pitchScale + static_cast<float>(pitch) * pitchScale - 0.06f,1.0f));

        lineColorNum.append(QVector4D(0.0f,0.0f,0.0f,0.0f));
        lineColorNum.append(QVector4D(0.0f,0.0f,0.0f,0.0f));
        lineColorNum.append(QVector4D(0.0f,0.0f,0.0f,0.0f));
        lineColorNum.append(QVector4D(0.0f,0.0f,0.0f,0.0f));

        texture.append(QVector2D(0.0f ,0.0f));
        texture.append(QVector2D(0.0f ,1.0f));
        texture.append(QVector2D(1.0f ,0.0f));
        texture.append(QVector2D(1.0f ,1.0f));

        /*绘制俯仰刻度值*/
        drawPicture(lineositionNum,lineColorNum,texture,this->strToImage(QString::number(i * 10),QColor(0,0,0,0),32,QColor(abs(i) > 4 ? 255: 0,abs(i) <=  4 ? 255 : 0 ,0,255),3));
        lineositionNum.clear();
        lineColorNum.clear();
        texture.clear();
//        }

        /*绘制俯仰刻度线段*/
        position.clear();
        position.append(QVector3D( (i % 2 == 0) ? -0.2f : -0.1f,  i * 10.0f * pitchScale + static_cast<float>(pitch) * pitchScale, 1.0f));
        position.append(QVector3D( (i % 2 == 0) ?  0.2f :  0.1f,  i * 10.0f * pitchScale + static_cast<float>(pitch) * pitchScale, 1.0f));
        glLineWidth(2);
        drawLines(position,color);
        glLineWidth(1);

    }

    glDisable(GL_LINE_SMOOTH);           //禁用线宽调整
}

void HUDOpenGLView::drawScale_heading()
{
    glEnable(GL_LINE_SMOOTH);           //启用线宽调整
    QVector<QVector3D> lineosition;
    QVector<QVector4D> lineColor;

    QVector<QVector3D> lineositionNum;
    QVector<QVector4D> lineColorNum;
    QVector<QVector2D> texture;

    int heading = static_cast<int>(this->heading);

    for(int i = 0; i < 360; i++){
        /*绘制弧形表盘*/
        if(((i + heading) % 360 < 300) && ((i + heading) % 360 > 60)){
            continue;
        }else{
            if(!((i + 1 + heading) % 360 <= 300 && (i + 1 + heading) % 360 >= 60 )){
                lineosition.clear();
                lineColor.clear();
                lineosition.append(QVector3D(qSin((i + heading) % 360 * M_PI / 180) * 0.8f * 0.9f , qCos((i + heading ) % 360* M_PI / 180) * 0.9f * 0.9f , 1.0f));
                lineosition.append(QVector3D(qSin(((i + 1) + heading ) % 360 * M_PI / 180) * 0.8f * 0.9f , qCos((i + 1  + heading ) % 360* M_PI / 180) * 0.9f * 0.9f , 1.0f));
                lineColor.append(rbgaToVector4D(this->color_scaleHeading));
                lineColor.append(rbgaToVector4D(this->color_scaleHeading));
                glLineWidth(2);
                drawLines(lineosition,lineColor);
                glLineWidth(1);
            }
        }

        /*绘制弧形刻度线段*/
        if(i % 10 == 0){
            lineosition.append(QVector3D(qSin((i + heading) % 360 * M_PI / 180) * 0.8f * 0.9f , qCos((i  + heading) % 360* M_PI / 180) * 0.9f * 0.9f , 1.0f));
            lineosition.append(QVector3D(qSin((i + heading) % 360 * M_PI / 180) * ((i / 10 % 2 == 0) ? 0.8f * 0.95f : 0.8f * 0.94f) , qCos((i  + heading) % 360 * M_PI / 180) * ((i / 10 % 2 == 0) ? 0.9f * 0.98f :0.9f * 0.94f) , 1.0f));

            lineColor.append(rbgaToVector4D(this->color_scaleHeading));
            lineColor.append(rbgaToVector4D(this->color_scaleHeading));

            glLineWidth(1);
            drawLines(lineosition,lineColor);
            glLineWidth(1);
            lineosition.clear();
            lineColor.clear();
        }

        /*绘制表盘数据*/
        if(i % 20 == 0){
            lineositionNum.clear();
            lineColorNum.clear();
            texture.clear();
            lineositionNum.append(QVector3D(qSin((i  + heading) % 360 * M_PI / 180) * 0.8f * 0.9f - 0.05f,  qCos((i  + heading) % 360* M_PI / 180) * 1.0f -  0.00f, 1.0f));
            lineositionNum.append(QVector3D(qSin((i  + heading) % 360 * M_PI / 180) * 0.8f * 0.9f - 0.05f,  qCos((i  + heading) % 360* M_PI / 180) * 1.0f -  0.1f, 1.0f));
            lineositionNum.append(QVector3D(qSin((i  + heading) % 360 * M_PI / 180) * 0.8f * 0.9f + 0.05f,  qCos((i  + heading) % 360* M_PI / 180) * 1.0f - 0.00f, 1.0f));
            lineositionNum.append(QVector3D(qSin((i  + heading) % 360 * M_PI / 180) * 0.8f * 0.9f + 0.05f,  qCos((i  + heading) % 360* M_PI / 180) * 1.0f - 0.1f, 1.0f));

            lineColorNum.append(QVector4D(0.0f,0.0f,0.0f,0.0f));
            lineColorNum.append(QVector4D(0.0f,0.0f,0.0f,0.0f));
            lineColorNum.append(QVector4D(0.0f,0.0f,0.0f,0.0f));
            lineColorNum.append(QVector4D(0.0f,0.0f,0.0f,0.0f));

            texture.append(QVector2D(0.0f ,0.0f));
            texture.append(QVector2D(0.0f ,1.0f));
            texture.append(QVector2D(1.0f ,0.0f));
            texture.append(QVector2D(1.0f ,1.0f));
            drawPicture(lineositionNum,lineColorNum,texture,this->strToImage(QString::number((360 - i) % 360),QColor(50,50,50,0),32,Qt::white,3));
            lineositionNum.clear();
            lineColorNum.clear();
            texture.clear();
        }
    }


    QVector<QVector3D> position;
    position.append(QVector3D( 0.0f,   0.82f, 0.0f));
    position.append(QVector3D( -0.025f, 0.74f, 0.0f));
    position.append(QVector3D( 0.025f,  0.74f, 0.0f));


    QVector<QVector4D> color;
    color.append(rbgaToVector4D(this->color_scaleHeading));
    color.append(rbgaToVector4D(this->color_scaleHeading));
    color.append(rbgaToVector4D(this->color_scaleHeading));

    drawGraphics(position,color);

    lineositionNum.clear();
    lineColorNum.clear();
    texture.clear();

    lineositionNum.append(QVector3D(0.0f - 0.06f,   0.72f, 1.0f));
    lineositionNum.append(QVector3D(0.0f - 0.06f,   0.62f, 1.0f));
    lineositionNum.append(QVector3D(0.0f + 0.06f,   0.72f, 1.0f));
    lineositionNum.append(QVector3D(0.0f + 0.06f,   0.62f, 1.0f));

    lineColorNum.append(QVector4D(0.0f,0.0f,0.0f,0.0f));
    lineColorNum.append(QVector4D(0.0f,0.0f,0.0f,0.0f));
    lineColorNum.append(QVector4D(0.0f,0.0f,0.0f,0.0f));
    lineColorNum.append(QVector4D(0.0f,0.0f,0.0f,0.0f));

    texture.append(QVector2D(0.0f ,0.0f));
    texture.append(QVector2D(0.0f ,1.0f));
    texture.append(QVector2D(1.0f ,0.0f));
    texture.append(QVector2D(1.0f ,1.0f));

    /*绘制当前航向值*/
    drawPicture(lineositionNum,lineColorNum,texture,this->strToImage(QString::number(heading),QColor(50,100,100,200),48,Qt::yellow,4));
    lineositionNum.clear();
    lineColorNum.clear();
    texture.clear();
    glDisable(GL_LINE_SMOOTH);           //禁用线宽调整

}

void HUDOpenGLView::drawAirInfo()
{
    glEnable(GL_LINE_SMOOTH);           //启用线宽调整
    glLineWidth(3);
    QVector<QVector3D> airPoosition;
    airPoosition.append(QVector3D( -0.5f, 0.0f, 1.0f));             /*中心垂直线*/
    airPoosition.append(QVector3D( -0.25f, 0.0f, 1.0f));

    QVector<QVector4D> airColor;
    airColor.append(rbgaToVector4D(this->color_airPlane));
    airColor.append(rbgaToVector4D(this->color_airPlane));

    drawLines(airPoosition,airColor);

    airPoosition.clear();
    airPoosition.append(QVector3D(0.5f,  0.0f,  1.0f));             /*中心垂直线*/
    airPoosition.append(QVector3D(0.25f,  0.0f,  1.0f));

    drawLines(airPoosition,airColor);

    airPoosition.clear();
    airPoosition.append(QVector3D(-0.15f,  -0.05f,  1.0f));           /*中心垂直线*/
    airPoosition.append(QVector3D( 0.0f,  0.05f,  1.0f));             /*中心垂直线*/
    drawLines(airPoosition,airColor);

    airPoosition.clear();
    airPoosition.append(QVector3D(0.15f,-0.05f,  1.0f));              /*中心垂直线*/
    airPoosition.append(QVector3D( 0.0f,  0.05f,  1.0f));             /*中心垂直线*/
    drawLines(airPoosition,airColor);
    glLineWidth(1);
    glDisable(GL_LINE_SMOOTH);           //禁用线宽调整


    QVector<QVector3D> position;
    QVector<QVector4D> color;
    QVector<QVector2D> texture;

    position.clear();
    texture.clear();
    color.clear();


    texture.append(QVector2D(1.0f,0.0f));
    texture.append(QVector2D(0.0f,0.0f));
    texture.append(QVector2D(1.0f,1.0f));
    texture.append(QVector2D(0.0f,1.0f));


    position.append(QVector3D(-0.35f,  -0.38f, 1.0f));
    position.append(QVector3D(-0.80f,  -0.38f, 1.0f));
    position.append(QVector3D(-0.35f,  -0.5f, 1.0f));
    position.append(QVector3D(-0.80f,  -0.5f, 1.0f));

    color.append(QVector4D(0.0f,0.0f,0.0f,0.0f));
    color.append(QVector4D(0.0f,0.0f,0.0f,0.0f));
    color.append(QVector4D(0.0f,0.0f,0.0f,0.0f));
    color.append(QVector4D(0.0f,0.0f,0.0f,0.0f));


    drawPicture(position,color,texture,this->strToImage("CR:" + QString::number(this->roll,'f',1),this->backGround_label,64,Qt::black,9,Qt::AlignLeft));

    position.clear();
    position.append(QVector3D(-0.35f,  -0.5f, 1.0f));
    position.append(QVector3D(-0.80f,  -0.5f, 1.0f));
    position.append(QVector3D(-0.35f,  -0.62f, 1.0f));
    position.append(QVector3D(-0.80f,  -0.62f, 1.0f));

    drawPicture(position,color,texture,this->strToImage("TR:" + QString::number(this->targetRoll,'f',1),this->backGround_label,64,Qt::yellow,9,Qt::AlignLeft));

    position.clear();
    position.append(QVector3D(-0.35f,  -0.68f, 1.0f));
    position.append(QVector3D(-0.80f,  -0.68f, 1.0f));
    position.append(QVector3D(-0.35f,  -0.8f, 1.0f));
    position.append(QVector3D(-0.80f,  -0.8f, 1.0f));
    drawPicture(position,color,texture,this->strToImage("CP:" + QString::number(this->pitch,'f',1),this->backGround_label,64,Qt::black,9,Qt::AlignLeft));

    position.clear();
    position.append(QVector3D(-0.35f,  -0.8f, 1.0f));
    position.append(QVector3D(-0.80f,  -0.8f, 1.0f));
    position.append(QVector3D(-0.35f,  -0.92f, 1.0f));
    position.append(QVector3D(-0.80f,  -0.92f, 1.0f));

    drawPicture(position,color,texture,this->strToImage("TP:" + QString::number(this->targetPitch,'f',1),this->backGround_label,64,Qt::yellow,9,Qt::AlignLeft));

    position.clear();
    texture.clear();
    position.append(QVector3D(0.80f,  -0.38f, 1.0f));
    position.append(QVector3D(0.35f,  -0.38f, 1.0f));
    position.append(QVector3D(0.80f,  -0.5f, 1.0f));
    position.append(QVector3D(0.35f,  -0.5f, 1.0f));


    texture.append(QVector2D(1.0f,0.0f));
    texture.append(QVector2D(0.0f,0.0f));
    texture.append(QVector2D(1.0f,1.0f));
    texture.append(QVector2D(0.0f,1.0f));

    drawPicture(position,color,texture,this->strToImage( QString::number(this->heading,'f',1) + ":CH",this->backGround_label,64,Qt::black,9,Qt::AlignRight));


    position.clear();
    position.append(QVector3D(0.80f,  -0.5f, 1.0f));
    position.append(QVector3D(0.35f,  -0.5f, 1.0f));
    position.append(QVector3D(0.80f,  -0.62f, 1.0f));
    position.append(QVector3D(0.35f,  -0.62f, 1.0f));


    drawPicture(position,color,texture,this->strToImage( QString::number(this->targetHeading,'f',1)+ ":TH",this->backGround_label,64,Qt::yellow,9,Qt::AlignRight));

    position.clear();
    position.append(QVector3D(0.80f,  -0.68f, 1.0f));
    position.append(QVector3D(0.35f,  -0.68f, 1.0f));
    position.append(QVector3D(0.80f,  -0.8f, 1.0f));
    position.append(QVector3D(0.35f,  -0.8f, 1.0f));

    drawPicture(position,color,texture,this->strToImage( QString::number(this->altitude,'f',1)+ ":CA",this->backGround_label,64,Qt::black,9,Qt::AlignRight));


    position.clear();
    position.append(QVector3D(0.80f,  -0.8f, 1.0f));
    position.append(QVector3D(0.35f,  -0.8f, 1.0f));
    position.append(QVector3D(0.80f,  -0.92f, 1.0f));
    position.append(QVector3D(0.35f,  -0.92f, 1.0f));


    drawPicture(position,color,texture,this->strToImage(QString::number(this->targetAltitude,'f',1) + ":TA",this->backGround_label,64,Qt::yellow,9,Qt::AlignRight));


}

void HUDOpenGLView::drawAirLabelInfo()
{
    QVector<QVector3D> position;
    QVector<QVector4D> color;
    QVector<QVector2D> texture;

    /*左上标签背景*/
    position.clear();
    position.append(QVector3D(-0.83f,  0.14f, 1.0f));
    position.append(QVector3D(-1.0f,   0.14f, 1.0f));
    position.append(QVector3D(-1.0f,   0.0f, 1.0f));
    position.append(QVector3D(-0.83f,  0.0f, 1.0f));
    position.append(QVector3D(-0.80f,  0.07f, 1.0f));

    color.clear();
    color.append(rbgaToVector4D(this->background_roll));
    color.append(rbgaToVector4D(this->background_roll));
    color.append(rbgaToVector4D(this->background_roll));
    color.append(rbgaToVector4D(this->background_roll));
    color.append(rbgaToVector4D(this->background_roll));

    drawGraphics(position,color);

    /*左上标签背景*/
    position.clear();
    position.append(QVector3D(-0.83f,   0.0f, 1.0f));
    position.append(QVector3D(-1.0f,    0.0f, 1.0f));
    position.append(QVector3D(-1.0f,   -0.14f, 1.0f));
    position.append(QVector3D(-0.83f,  -0.14f, 1.0f));
    position.append(QVector3D(-0.80f,  -0.07f, 1.0f));

    color.clear();
    color.append(rbgaToVector4D(this->background_heading));
    color.append(rbgaToVector4D(this->background_heading));
    color.append(rbgaToVector4D(this->background_heading));
    color.append(rbgaToVector4D(this->background_heading));
    color.append(rbgaToVector4D(this->background_heading));

    drawGraphics(position,color);


    /*右上标签背景*/
    position.clear();
    position.append(QVector3D(1.0f,   0.14f, 1.0f));
    position.append(QVector3D(0.83f,  0.14f, 1.0f));
    position.append(QVector3D(0.80f,  0.07f, 1.0f));
    position.append(QVector3D(0.83f,  0.0f, 1.0f));
    position.append(QVector3D(1.0f,   0.0f, 1.0f));

    color.clear();
    color.append(rbgaToVector4D(this->background_roll));
    color.append(rbgaToVector4D(this->background_roll));
    color.append(rbgaToVector4D(this->background_roll));
    color.append(rbgaToVector4D(this->background_roll));
    color.append(rbgaToVector4D(this->background_roll));

    drawGraphics(position,color);


    /*右下标签背景*/
    position.clear();
    position.append(QVector3D(1.0f,   0.0f, 1.0f));
    position.append(QVector3D(0.83f,  0.0f, 1.0f));
    position.append(QVector3D(0.80f, -0.07f, 1.0f));
    position.append(QVector3D(0.83f, -0.14f, 1.0f));
    position.append(QVector3D(1.0f,  -0.14f, 1.0f));

    color.clear();
    color.append(rbgaToVector4D(this->background_heading));
    color.append(rbgaToVector4D(this->background_heading));
    color.append(rbgaToVector4D(this->background_heading));
    color.append(rbgaToVector4D(this->background_heading));
    color.append(rbgaToVector4D(this->background_heading));

    drawGraphics(position,color);

    /*左上标签文字*/
    position.clear();
    position.append(QVector3D(-0.83f,   0.14f, 1.0f));
    position.append(QVector3D(-1.0f,    0.14f, 1.0f));
    position.append(QVector3D(-0.83f,   0.0f, 1.0f));
    position.append(QVector3D(-1.0f,    0.0f, 1.0f));

    color.clear();
    color.append(rbgaToVector4D(this->background_roll));
    color.append(rbgaToVector4D(this->background_roll));
    color.append(rbgaToVector4D(this->background_roll));
    color.append(rbgaToVector4D(this->background_roll));

    texture.clear();
    texture.append(QVector2D(1.0f,0.0f));
    texture.append(QVector2D(0.0f,0.0f));
    texture.append(QVector2D(1.0f,1.0f));
    texture.append(QVector2D(0.0f,1.0f));

    drawPicture(position,color,texture,this->strToImage(QString::number(this->targetAltitude),QColor(0,0,0,0),32,Qt::white,7));


    /*左下标签文字*/
    position.clear();

    position.append(QVector3D(-0.83f,   0.0f, 1.0f));
    position.append(QVector3D(-1.0f,    0.0f, 1.0f));
    position.append(QVector3D(-0.83f,  -0.14f, 1.0f));
    position.append(QVector3D(-1.0f,   -0.14f, 1.0f));

    color.clear();
    color.append(rbgaToVector4D(this->background_heading));
    color.append(rbgaToVector4D(this->background_heading));
    color.append(rbgaToVector4D(this->background_heading));
    color.append(rbgaToVector4D(this->background_heading));

    drawPicture(position,color,texture,this->strToImage(QString::number(this->altitude,'f',1),QColor(0,0,0,0),32,Qt::white,7));

    /*右上标签文字*/
    position.clear();
    position.append(QVector3D(1.0f,    0.14f, 1.0f));
    position.append(QVector3D(0.83f,   0.14f, 1.0f));
    position.append(QVector3D(1.0f,    0.0f, 1.0f));
    position.append(QVector3D(0.83f,   0.0f, 1.0f));


    color.clear();
    color.append(rbgaToVector4D(this->background_roll));
    color.append(rbgaToVector4D(this->background_roll));
    color.append(rbgaToVector4D(this->background_roll));
    color.append(rbgaToVector4D(this->background_roll));

    drawPicture(position,color,texture,this->strToImage(QString::number(this->targetSpeed,'f',1),QColor(0,0,0,0),32,Qt::white,5));

    /*右下标签文字*/
    position.clear();
    position.append(QVector3D(1.0f,    0.0f, 1.0f));
    position.append(QVector3D(0.83f,   0.0f, 1.0f));
    position.append(QVector3D(1.0f,   -0.14f, 1.0f));
    position.append(QVector3D(0.83f,  -0.14f, 1.0f));

    color.clear();
    color.append(rbgaToVector4D(this->background_heading));
    color.append(rbgaToVector4D(this->background_heading));
    color.append(rbgaToVector4D(this->background_heading));
    color.append(rbgaToVector4D(this->background_heading));

    drawPicture(position,color,texture,this->strToImage(QString::number(this->speed,'f',1),QColor(0,0,0,0),32,Qt::white,5));


}

//void HUDOpenGLView::drawAlititudeScale()
//{
//    QVector<QVector3D> position;
//    QVector<QVector4D> color;
//    position.clear();
//    color.clear();
//    color.append(rbgaToVector4D(this->color_scale));
//    color.append(rbgaToVector4D(this->color_scale));
//    for(int i = 0; i < 10 ; i++){
//        position.clear();
//        position.append(QVector3D(((i % 2 == 0) ? -0.9 : -0.85),static_cast<float>(i) * 0.1f,1.0f));
//        position.append(QVector3D(-0.8f,static_cast<float>(i) * 0.1f,1.0f));
//        drawLines(position,color);

//        position.clear();
//        position.append(QVector3D(((i % 2 == 0) ? -0.9 : -0.85),static_cast<float>(i) * -0.1f,1.0f));
//        position.append(QVector3D(-0.8f,static_cast<float>(i) * -0.1f,1.0f));
//        drawLines(position,color);
//    }
//}

//void HUDOpenGLView::drawSpeedScale()
//{
//    QVector<QVector3D> position;
//    QVector<QVector4D> color;
//    position.clear();
//    color.clear();
//    color.append(rbgaToVector4D(this->color_scale));
//    color.append(rbgaToVector4D(this->color_scale));
//    for(int i = 0; i < 10 ; i++){
//        position.clear();
//        position.append(QVector3D(((i % 2 == 0) ? 0.9 : 0.85),static_cast<float>(i) * 0.1f,1.0f));
//        position.append(QVector3D(0.8f,static_cast<float>(i) * 0.1f,1.0f));
//        drawLines(position,color);

//        position.clear();
//        position.append(QVector3D(((i % 2 == 0) ? 0.9 : 0.85),static_cast<float>(i) * -0.1f,1.0f));
//        position.append(QVector3D(0.8f,static_cast<float>(i) * -0.1f,1.0f));
//        drawLines(position,color);
//    }
//}

void HUDOpenGLView::drawGraphics(QVector<QVector3D> position, QVector<QVector4D> color)
{
    this->VBO.create();
    this->VBO.bind();
    this->VBO.allocate(" ",position.count() * sizeof(QVector3D)  + color.count() * sizeof(QVector4D));          //分配VBO内存

    this->VBO.write(0,static_cast<void *>(position.begin()), position.count() * sizeof(QVector3D));
    this->VBO.write(position.count() * sizeof(QVector3D), static_cast<void *>(color.begin()),  color.count() * sizeof(QVector4D));

    GLuint v_position = this->shaderProgram_draw->attributeLocation("vPosition");
    shaderProgram_draw->setAttributeBuffer(v_position, GL_FLOAT, 0, sizeof(QVector3D) / sizeof(GLfloat), 0);
    glEnableVertexAttribArray(v_position);


    GLuint v_Color = this->shaderProgram_draw->attributeLocation("vColor");
    this->shaderProgram_draw->setAttributeBuffer(v_Color, GL_FLOAT, position.count() * sizeof(QVector3D), sizeof(QVector4D) / sizeof(GLfloat), 0);
    glEnableVertexAttribArray(v_Color);

    glDrawArrays(GL_TRIANGLE_FAN, 0, position.count());

    this->VBO.release();
}

void HUDOpenGLView::drawLines(QVector<QVector3D> position, QVector<QVector4D> color)
{
    glEnable(GL_LINE_SMOOTH);
    this->VBO.create();
    this->VBO.bind();
    this->VBO.allocate(" ",position.count() * sizeof(QVector3D)  + color.count() * sizeof(QVector4D));          //分配VBO内存

    this->VBO.write(0,static_cast<void *>(position.begin()), position.count() * sizeof(QVector3D));
    this->VBO.write(position.count() * sizeof(QVector3D), static_cast<void *>(color.begin()),  color.count() * sizeof(QVector4D));

    GLuint v_position = this->shaderProgram_draw->attributeLocation("vPosition");
    shaderProgram_draw->setAttributeBuffer(v_position, GL_FLOAT, 0, sizeof(QVector3D) / sizeof(GLfloat), 0);
    glEnableVertexAttribArray(v_position);


    GLuint v_Color = this->shaderProgram_draw->attributeLocation("vColor");
    this->shaderProgram_draw->setAttributeBuffer(v_Color, GL_FLOAT, position.count() * sizeof(QVector3D), sizeof(QVector4D) / sizeof(GLfloat), 0);
    glEnableVertexAttribArray(v_Color);

    glDrawArrays(GL_LINES, 0, position.count());

    glDisable(GL_LINE_SMOOTH);

    this->VBO.release();
}

void HUDOpenGLView::drawPicture(QVector<QVector3D> position, QVector<QVector4D> color, QVector<QVector2D> texture, QImage image)
{
    this->VBO.create();
    this->VBO.bind();
    this->VBO.allocate(" ",position.count() * sizeof(QVector3D)  + color.count() * sizeof(QVector4D) + texture.count() * sizeof(QVector2D) );          //分配VBO内存

    this->VBO.write(0,static_cast<void *>(position.begin()), position.count() * sizeof(QVector3D));
    this->VBO.write(position.count() * sizeof(QVector3D), static_cast<void *>(color.begin()),  color.count() * sizeof(QVector4D));
    this->VBO.write(position.count() * sizeof(QVector3D) + color.count() * sizeof(QVector4D), static_cast<void *>(texture.begin()),  texture.count() * sizeof(QVector2D));

    GLuint v_position = this->shaderProgram_draw->attributeLocation("vPosition");

    GLuint v_Color = this->shaderProgram_draw->attributeLocation("vColor");

    GLuint v_texture = this->shaderProgram_draw->attributeLocation("vTexCoord");


    this->shaderProgram_draw->enableAttributeArray(v_position);
    this->shaderProgram_draw->enableAttributeArray(v_Color);
    this->shaderProgram_draw->enableAttributeArray(v_texture);


    this->shaderProgram_draw->setAttributeBuffer(v_position, GL_FLOAT, 0, sizeof(QVector3D) / sizeof(GLfloat), 0);
    this->shaderProgram_draw->setAttributeBuffer(v_Color, GL_FLOAT, position.count() * sizeof(QVector3D), sizeof(QVector4D) / sizeof(GLfloat), 0);
    this->shaderProgram_draw->setAttributeBuffer(v_texture, GL_FLOAT, position.count() * sizeof(QVector3D) + color.count() * sizeof(QVector4D), sizeof(QVector2D) / sizeof(GLfloat), 0);

    this->shaderProgram_draw->setUniformValue("ourTexturec", v_position); //将当前上下文中位置的统一变量设置为value
    this->texture->destroy(); //消耗底层的纹理对象
    this->texture->create();
    this->texture->setData(image);
    this->texture->setLevelofDetailBias(-1);//值越小，图像越清晰
    this->texture->bind();  //绑定纹理
    glDrawArrays(GL_TRIANGLE_STRIP, 0, position.count());//绘制纹理
    this->texture->release(); //释放绑定的纹理


}


QVector4D HUDOpenGLView::rbgaToVector4D(QColor color)
{
    return QVector4D(color.redF(),color.greenF(),color.blueF(),color.alphaF());
}



void HUDOpenGLView::initializeGL()
{
    initializeOpenGLFunctions();
    if(this->vshader_draw == nullptr){
        this->vshader_draw = new QOpenGLShader(QOpenGLShader::Vertex,this);
    }

    if(this->fshader_draw == nullptr){
        this->fshader_draw = new QOpenGLShader(QOpenGLShader::Fragment,this);
    }

    if(this->texture == nullptr){
        this->texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
        texture->setMinificationFilter(QOpenGLTexture::Nearest); //滤波
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        texture->setWrapMode(QOpenGLTexture::Repeat);
        texture->allocateStorage();
    }

    this->vshader_draw->compileSourceFile(":/hudview/shader/hudVertex.vert");


    this->fshader_draw->compileSourceFile(":/hudview/shader/hudFragment.frag");


    if(this->shaderProgram_draw == nullptr){
        this->shaderProgram_draw = new QOpenGLShaderProgram();
        this->shaderProgram_draw->addShader(this->vshader_draw);
        this->shaderProgram_draw->addShader(this->fshader_draw);
    }



    if(!this->shaderProgram_draw->link())
    {
        close();
        qDebug()<<"!this->shaderProgram_draw->link()";
    }
    if(!this->shaderProgram_draw->bind()){
        qDebug()<<"!this->shaderProgram_draw->bind()";
        close();
    }


//    glEnable(GL_TEXTURE_2D);

//    this->VBO.create();
//    this->VBO.bind();
}

void HUDOpenGLView::paintGL()
{
    glEnable(GL_ALPHA_BITS);
//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);            //开启2D纹理
    glEnable(GL_BLEND );                //启用颜色混合。例如实现半透明效果
    glEnable(GL_ALPHA_TEST);            //跟据函数glAlphaFunc的条件要求来决定图形透明的层度是否显示。

    glEnable(GL_CULL_FACE); //启动了背面裁剪
    glFrontFace(GL_CCW); //设置逆时针为正面
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); //混合模式选择

    drawBackGround();
    drawScale_pitch();
    drawScale_heading();
    drawAirInfo();
    drawAirLabelInfo();
//    drawAlititudeScale();
//    drawSpeedScale();

}

void HUDOpenGLView::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
}

void HUDOpenGLView::updateHUDData(float altitude, float targetAltitude, float roll, float targetRoll, float heading, float targetHeading, float pitch, float targetPitch, float speed, float targetSpeed)
{
    this->altitude = altitude;
    this->targetAltitude = targetAltitude;
    this->roll = roll;
    this->targetRoll  = targetRoll;
    this->heading = heading;
    this->targetHeading = targetHeading;
    this->pitch = pitch;
    this->targetPitch = targetPitch;
    this->speed = speed;
    this->targetSpeed = targetSpeed;
    this->update();
}


QImage HUDOpenGLView::strToImage(QString text,QColor backgroundColor,int fontSize,QColor fontColor, int minLen ,Qt::AlignmentFlag flag)
{
    glDisable(GL_DEPTH_TEST);
    QImage image(fontSize / 2 * (text.length() > minLen ? text.length() : minLen) ,fontSize,QImage::Format_ARGB32);
    image.fill(backgroundColor);
    QPainter painter;
    painter.begin(&image);
    QPen pen = painter.pen();
    pen.setColor(fontColor);
    QFont font = painter.font();
    font.setFamily("SimHei");
    font.setBold(true);//加粗
    font.setPixelSize(fontSize);//改变字体大小
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(image.rect(),flag,text);
    painter.end();
    return image;
}



