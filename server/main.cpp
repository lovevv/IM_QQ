#include <QtGui/QApplication>
#include "imqserver.h"
#include "IMQ_server.h"
#include "Thread.h"
#include<stdio.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IMQServer w;
    w.show();


    //可以进行转换，将QString类型转化为char *;
//    QString s="12232324";
//    char ss[20];
//    strcpy(ss,s.toLatin1().data());
//    printf("%s\n",ss);
    //Thread *b=new Thread();
    //b->start();
    return a.exec();
}
