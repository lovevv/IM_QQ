#include "myScreen.h"

myScreen::myScreen(QSize size)
{
    maxWidth = size.width();
    maxHeight = size.height();

    //???
    startPos = QPoint(-1,-1);
    endPos = startPos;
    leftUpPos = startPos;
    rightDownPos = startPos;
    status = SELECT;
}

int myScreen::width()
{
    return maxWidth;
}

int myScreen::height()
{
    return maxHeight;
}

STATUS myScreen::getStatus()
{
    return status;
}

void myScreen::setStatus(STATUS st)
{
    status=st;
}

void myScreen::setEnd(QPoint pos)
{
    endPos = pos;
   //????cmpPoint?????????????
    leftUpPos = startPos;
    rightDownPos = endPos;
    cmpPoint(leftUpPos,rightDownPos);
}

void myScreen::setStart(QPoint pos)
{
    startPos=pos;
}

QPoint myScreen::getEnd()
{
    return endPos;
}

QPoint myScreen::getStart()
{
    return startPos;
}

QPoint myScreen::getLeftUp()
{
    return leftUpPos;
}

QPoint myScreen::getRightDown()
{
    return rightDownPos;
}

/****************************************
*
*??????true ?? false
*
****************************************/
bool myScreen::isInArea(QPoint pos)
{
    if( pos.x() > leftUpPos.x() && pos.x() < rightDownPos.x() &&\
        pos.y() > leftUpPos.y() && pos.y() < rightDownPos.y() )
        return true;
    return false;
}

/****************************************
*
*? p??????
*
****************************************/
void myScreen::move(QPoint p)
{
    int lx = leftUpPos.x() + p.x();
    int ly = leftUpPos.y() + p.y();
    int rx = rightDownPos.x() + p.x();
    int ry = rightDownPos.y() + p.y();

    if( lx<0 ) { lx = 0; rx -= p.x(); }  // ?????????????
    if( ly<0 ) { ly = 0; ry -= p.y(); }  // zuishang
    if( rx>maxWidth )  { rx = maxWidth; lx -= p.x(); }  //zuiyou
    if( ry>maxHeight ) { ry = maxHeight; ly -= p.y(); } //zuixia

    leftUpPos = QPoint(lx,ly);
    rightDownPos = QPoint(rx,ry);
    startPos = leftUpPos; // ???????
    endPos = rightDownPos;
}

/****************************************
*
*??????????????????leftTop
*?????rightDown
*
****************************************/
void myScreen::cmpPoint(QPoint& leftTop,QPoint& rightDown)
{
    QPoint l = leftTop;
    QPoint r = rightDown;

    if( l.x()<=r.x()  )  //???????
    {
        if( l.y()<=r.y() ) //??
        {
            ;
        }
        else          //??
        {
            leftTop.setY(r.y());
            rightDown.setY(l.y());
        }
    }
    else                //???
    {
        if( l.y()<r.y() ) //??
        {
            leftTop.setX(r.x());
            rightDown.setX(l.x());
        }
        else             //??
        {
            QPoint tmp;
            tmp = leftTop;
            leftTop = rightDown;
            rightDown = tmp;
        }
    }
}
