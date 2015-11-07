#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QWidget>
#include "client_socket.h"
#include <QLabel>
#include <QTreeView>
#include <QStandardItemModel>
#include <QHash>
#include <QSystemTrayIcon>          //创建系统托盘
#include <QMenu>
#include <QCloseEvent>
#include <QTime>

#include <phonon/VideoPlayer>
#include <phonon/MediaObject>
#include <phonon/AudioOutput>

#include "receive_file.h"
#include "chat.h"
#include "shotwindow.h"

//在新的主框架中应该有个关于原先套接字链接的传递，控制用户登录后与server进行的交互；

namespace Ui {
    class Mainframe;
}

class Mainframe : public QWidget
{
    Q_OBJECT

public:
    explicit Mainframe(QWidget *parent = 0,client_socket *socket=0);
    bool Is_inloginlist(QString loginname);
    int setport();
    inline int getport(){return port;}

    ~Mainframe();
    QLabel *name_lable;
protected:
    void closeEvent(QCloseEvent *event);

signals:
    void send_touser(QString username);///发这个信号要求sclient_socket帮我转发数据
    void show_msginchat(QString sendname,QString myname,QString msg);
    void info_mylogin();
    void info_myofflne();

    void get_sendipandport(QString myname,QString sendname,int portt);//////获取ip和port

public slots:
    void set_friendslist(QStringList friendlist);
    void show_chat();/////获取点击到的那一行的数据；
    void message_comming(QString sendname,QString myname,QString msg);////接收到消息以后可以又一些处理，比如说闪烁，还没做呢！！！！！通知chat进行显示
    void delete_communication(QString person,int positive);
    void on_systemTrayiconclicked(QSystemTrayIcon::ActivationReason reason);
    void quit();
    void show_normal();

    void update_fridenglist_login(QString loginname);
    void update_fridenglist_offline(QString offname);

    void get_sendip_port(QString myname,QString sendname,int portt);

    void show_receivefile(QString msg_from,QString myname,int port);



private slots:
    void on_add_friends_clicked();

    void on_pushButton_3_clicked();

private:
  //  QHash <QString, QString>commitlist;///////发送者,kuangzi

    QHash <QString ,chat *>sendlist;////////在主窗口管理一个发送端的窗口，再QString里是接收者的名字；
    QHash <QString, chat *>receivelist;//////。。。。。。。。。接收端窗口，。。。。。。发送者的名字；

    QStringList *my_friendlist;
    QStringList * loginlist;

    Ui::Mainframe *ui;
    client_socket *from_client1;//这个套接字是用来接收登录窗口过来的套接字；
    QStandardItemModel *model;
    chat *newchat;

    //////创建托盘////
   QSystemTrayIcon *imq_icon;
   QMenu *imq_menu;
   static int should_close;

   // QTreeView *a;

   QTcpServer *server;///////////用来进行文件传输；
   int port;
   QTcpSocket *socket;

   //jittushixian
   shotwindow *shot;
};

#endif // MAINFRAME_H
