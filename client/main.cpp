#include <QtGui/QApplication>
#include "client.h"
#include "client_socket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w;
    w.show();
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());/////解决中文乱码问题
    return a.exec();
}
