#ifndef RECEIVE_FILE_H
#define RECEIVE_FILE_H

#include <QWidget>
#include <QDebug>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
    class receive_file;
}

class receive_file : public QWidget
{
    Q_OBJECT

public:
    explicit receive_file(QWidget *parent = 0,QString msg=0,QString my=0,int portt=0);
    inline QString get_msgfrom(){return msg_from;}
    inline QString get_myname(){return myname;}
    inline int get_port(){return port;}

    ~receive_file();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

public slots:
    void start_tranfor();
    void update_clientprocess();////genxin kehuduande wenjian jieshoude jindu
    void display_error(QAbstractSocket::SocketError);

signals:
    void refuse_file(QString msg_from,QString myname);
    void receive_success(QString msgfrom,QString my);

private:
    Ui::receive_file *ui;

    QTcpSocket *trans;
    QString msg_from;
    QString myname;
    int port;

   //////////////////////////////////////以下为进行文件传输的时候要求的东西////////////////////////////////////////

    qint64 totalBytes;  //存放总大小信息
    qint64 bytesReceived;  //已收到数据的大小
    qint64 fileNameSize;  //文件名的大小信息
    QString fileName;   //存放文件名
    QFile *localFile;   //本地文件
    QByteArray inBlock;   //数据缓冲区
};

#endif // RECEIVE_FILE_H
