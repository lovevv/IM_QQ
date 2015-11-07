#ifndef MYQLABLE_H
#define MYQLABLE_H
#include <QLabel>
#include <QWidget>
#include <QDebug>

class myQLabel:public QLabel
{
    Q_OBJECT
public:
    myQLabel(QWidget *parent=0);
  //  ~myQLabel();
signals:
    void clicked();
public slots:
    void showclicked();
protected:
    void mousePressEvent(QMouseEvent *ev);////// 重写这个函数实现Qlable单击事件；
};

#endif // MYQLABLE_H
