#include "myQlable.h"

myQLabel::myQLabel(QWidget *parent):QLabel(parent)
{
    connect(this,SIGNAL(clicked()),this,SLOT(showclicked()));
}
//myQLabel::~myQLabel()
//{
//}
void myQLabel::mousePressEvent(QMouseEvent *ev)
{
    //emit(clicked());
    emit  clicked();
}
void myQLabel::showclicked()
{
//    qDebug()<<"clicked hahah hahahhah";
//    QPixmap *pm=new QPixmap("this->pixmap()");
}
