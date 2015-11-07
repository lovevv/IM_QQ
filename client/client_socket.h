#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H
#include<QtNetwork>
#include<QtNetwork/QTcpSocket>
#include <QHostAddress>
#include "message.h"

class client_socket:public QTcpSocket
{
    Q_OBJECT
public:
    client_socket(QObject *parent=0);
  //  ~client_socket();
    inline void set_name(QString name){username=name;}
    inline void set_pwd(QString pwd){passwd=pwd;}
    inline QString getname(){return username;}
    inline QString getpwd(){return passwd;}
    bool is_registering;////////用来表示是不是重复注册；

public  slots:
    void sendmsg_login();
    void read_msg();

    void send_msg(QString name,QString sendname,QString msg);
    void respond_msg(QString name,QString sendname,QString msg);

    void get_friendslist(QString name);

    void info_myfriend_login();
    void info_myfriend_offline();

    void get_sendip(QString myname,QString sendname,int portt);////new is doing

    void refuse_file(QString msg_from,QString name);
    void receive_success(QString msg_from,QString myname);

signals:
    void add_newuser_inmylist(QString name,QHostAddress address);
    void showmessage(QString msg_from,QString myname,QString msg);//////用来通知再主界面是进行显示聊天界面显示数据；

    void login_mainframe(QString displayname);//////进入主窗口；
    void set_friendslist(QStringList friendlist);///这个信号用来进行通知主窗口的函数来接收好友列表并进行显示；
    void showrgs_result(int isok);

    void update_fridenglist_login(QString new_loginname);
    void update_fridenglist_offline(QString offnmae);

    void should_connect(QString msg_from,QString myname,int port);

    void close_filetrans(QString msg_from,QString myname);
private:
    QString username;
    QString passwd;


};

#endif // CLIENT_SOCKET_H
