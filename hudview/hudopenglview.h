#ifndef HUDOPENGLVIEW_H
#define HUDOPENGLVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QtMath>
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <QOpenGLVertexArrayObject>
#include <QtOpenGL\qgl.h>
#include <gl\GL.h>
#include <gl\GLU.h>

class HUDOpenGLView : public QOpenGLWidget,public QOpenGLFunctions
{
public:
    HUDOpenGLView(QWidget *parent = 0);

    float getAltitude() const;
    void setAltitude(float newAltitude);

    float getTargetAltitude() const;
    void setTargetAltitude(float newTargetAltitude);

    float getRoll() const;
    void setRoll(float newRoll);

    float getTargetRoll() const;
    void setTargetRoll(float newTargetRoll);

    float getHeading() const;
    void setHeading(float newHeading);

    float getTargetHeading() const;
    void setTargetHeading(float newTargetHeading);

    float getPitch() const;
    void setPitch(float newPitch);

    float getTargetPitch() const;
    void setTargetPitch(float newTargetPitch);

    float getSpeed() const;
    void setSpeed(float newSpeed);

    float getTargetSpeed() const;
    void setTargetSpeed(float newTargetSpeed);

private:

    float       pitchScale = 0.02f;                 //俯仰角度对应图形高度比例 1 ：50

    float       altitude = 100;                     //高度
    float       targetAltitude = 0;                 //高度

    float       roll = 0;                           //横滚
    float       targetRoll = 0;                     //目标横滚

    float       heading = 0;                        //航向
    float       targetHeading = 0;                  //目标航向

    float       pitch = 10.0;                       //俯仰
    float       targetPitch = 0;                    //目标俯仰

    float       speed = 0.0f;
    float       targetSpeed = 0.0f;


    QColor background_sky   = QColor(0  ,150 ,200 ,255);            //颜色-天空
    QColor background_land  = QColor(230,150 ,50  ,255);            //颜色-土地
    QColor background_scale = QColor(20 ,20  ,20  ,255);            //颜色-刻度背景色
    QColor background_heading = QColor(115 ,150 ,60 ,255);          //颜色-刻度背景色
    QColor background_roll = QColor(60 ,115 ,150 ,255);             //颜色-刻度背景色

    QColor backGround_label =  QColor(200 ,200 ,20  ,0);             //颜色-刻度背景色
    QColor color_airPlane =  QColor(255 ,20  ,20  ,255);
    QColor color_scale      = QColor(255,255 ,255 ,255);            //颜色-刻度
    QColor color_scaleHeading = QColor(0,0 ,0 ,255);

    QOpenGLShader *vshader_draw  = nullptr;                      //顶点着色器-绘制图形时使用
    QOpenGLShader *fshader_draw  = nullptr;                      //片元着色器-绘制图形时使用
    QOpenGLShaderProgram *shaderProgram_draw = nullptr;          //着色器程序-绘制图形使用
    QOpenGLTexture *texture = nullptr;

    QOpenGLBuffer EBO;
    QOpenGLBuffer VBO;
    QOpenGLVertexArrayObject  VAO;

private:
    QTimer *timer = nullptr;

private:
    void drawBackGround();                  //绘制HUD面板
    void drawScale_pitch();                 //绘制俯仰刻度盘
    void drawScale_heading();               //绘制航向刻度盘
    void drawAirInfo();                     //绘制飞行器图标
    void drawAirLabelInfo();                //绘制hud界面标签

//    void drawAlititudeScale();
//    void drawSpeedScale();


private:
    void drawGraphics(QVector<QVector3D> position,QVector<QVector4D> color);
    void drawLines(QVector<QVector3D> position,QVector<QVector4D> color);
    void drawPicture(QVector<QVector3D> position,QVector<QVector4D> color,QVector<QVector2D> texture, QImage image);

    QImage strToImage(QString text,QColor backgroundColor,int fontSize,QColor fontColor,int minLen,Qt::AlignmentFlag flag = Qt::AlignCenter);
    QVector4D rbgaToVector4D(QColor);
protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);


public slots:
    void updateHUDData(float altitude,float targetAltitude,float roll,float targetRoll,float heading,float targetHeading,float pitch,float targetPitch,float speed,float targetSpeed);
//    void updateHUDData();
};

#endif // HUDOPENGLVIEW_H
