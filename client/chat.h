#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <QDateTime>
#include <QColor>
#include <QColorDialog>
#include <QProgressBar>
#include <QFileDialog>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QHBoxLayout>
#include <QVBoxLayout>


#include "history_record.h"

namespace Ui {
    class chat;
}

class chat : public QDialog
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = 0,QString myname=0,QString name_tosend=0,int ispositive=0);
    inline QString get_myname(){return myname;}
    inline QString get_sendname(){return name_tosend;}

    int setport();
    inline int getport(){return port;}

    Ui::chat *ui;
    QColor mycolor;
    ~chat();

public slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void show_newmsg(QString name,QString sendname,QString msg);
    void loadface(QString clickedname);

    void close_filetrans(QString msg_from,QString myname);

    void accept_connect();

    void update_serverprocess(qint64 numbytes);
    void display_error(QAbstractSocket::SocketError);
    void trans_file();

signals:
   void send_msg(QString name,QString sendname,QString msg);
   void respond_msg(QString name,QString sendname,QString msg);//////回应消息时的信号
   void close_chat(QString,int positive);///////关闭和一个人的聊天窗口的时候触发；

   void load_historyrecord(QString myname,QString sendname);////打开历史记录

   void get_sendip_port(QString myname,QString sendname,int portt);////向接收方提供自己server的端口，供客户进行链接

private slots:
   void on_close_chat_clicked();
   void on_QQface_clicked();
   void on_front_color_clicked();
   void on_fontComboBox_currentFontChanged(const QFont &f);
   void on_front_size_currentIndexChanged(const QString &arg1);
   void on_toolButton_4_clicked();
   void on_filetrans_clicked();
   void file_open_tosend();
   void sendfile();//发送文件

private:

    QString myname;
    QString name_tosend;
    int ispositive;


    QTcpServer *server;///////////用来进行文件传输；
    int port;
    QTcpSocket *socket;

    QVBoxLayout *vboxlayout;
    QHBoxLayout *horizontal;
    QProgressBar *process;
    QHBoxLayout *push_set;
    QPushButton *button1;
    QPushButton *button2;


    QFile *localFile;  //要发送的文件
    qint64 totalBytes;  //数据总大小
    qint64 bytesWritten;  //已经发送数据大小
    qint64 bytesToWrite;   //剩余数据大小
    qint64 loadSize;   //每次发送数据的大小
    QString fileName;  //保存文件路
    QByteArray outBlock;  //数据缓冲区，即存放每次要发送的数据

};

#endif // CHAT_H
