#ifndef AREASHOT_H
#define AREASHOT_H
#define WIDTH_SHOW 340
#define HEIGHT_SHOW 30


#include <QWidget>
#include<QtGui>
#include<QPixmap>
#include<QPainter>
#include<QPoint>
#include<QLabel>
#include<QPixmap>
#include<QLineEdit>

#include "myScreen.h"   //进行区域截图的自定义类





namespace Ui {
    class areashot;
}

class areashot : public QWidget
{
    Q_OBJECT

public:
    explicit areashot(QWidget *parent = 0);
    ~areashot();

 protected:

/********************************************************
  *
  *在进行截图的确定截图区域时需要捕获的鼠标事件以及键盘按键检测时间的重写------》chsun
  *
  *********************************************************/


       void paintEvent(QPaintEvent *);//在进行调用grabWindow函数的时候会进行重绘
       void mousePressEvent(QMouseEvent *);//鼠标按下的事件
       void mouseMoveEvent(QMouseEvent *);//鼠标移动事件
       void mouseReleaseEvent(QMouseEvent *);//鼠标放开事件
       void keyReleaseEvent(QKeyEvent *);//检测键盘按键事件
       void mouseDoubleClickEvent(QMouseEvent *);//鼠标双击事件
signals:
       void fullshot(QPixmap *p);
private:
    Ui::areashot *ui;
    myScreen *cutScreen;      // RCutScreen对象,记录x y w h 数据
     QPixmap *infoPix;         // 截图信息显示背景
     QPixmap *fullScreen;      // 保存全屏图像
     QPixmap *areaScreen;//保存区域截图
     QPixmap *bgScreen;        // 模糊背景图
     QPoint movPos;

};

#endif // AREASHOT_H
