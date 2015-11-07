#ifndef TCPSOCKET_CLIENT_H
#define TCPSOCKET_CLIENT_H
#include<QtNetwork/QTcpSocket>
#include <QHostAddress>
#include <QStringList>

class Tcpsocket_client:public QTcpSocket
{
    Q_OBJECT
public:
    Tcpsocket_client(QObject *parent=0);
  //  ~Tcpsocket_client();
    inline QString getname(){return username;}
    inline QHostAddress getaddr(){return addr;}
    inline bool get_reloginstatus(){return relogin;}//获取重复登录的状态；
    inline bool get_registerstatus(){return new_rgsok;}////获取注册信息是否是成功的，new_rgsok been changed  when the register is doing
 //   void info_friendlogin(QString loginname);

signals:
    void newonline(QString onename,QHostAddress oneaddr,Tcpsocket_client *socket);
    void newmessage(QString  myname,QString sendname,QString msg);///这个函数需要修改；
    void new_register(QString onename,QString onepasswd);
    void new_infologin(QString login_name);
    void info_offline(QString offline_name);

    void get_socket(QString myname,QString sendname,int portt);////向接收用户发送作为服务器的客户端的port端口，便于客户进行链接

    void refuse_file(QString msg_from,QString sendname);/////
    void successfile(QString msg_from,QString sendname);


public slots:
    void messagecoming();
    void is_relogin();
    void is_registerok(int isok);

private:
    bool relogin;
    bool new_rgsok;

    QString username;
    QHostAddress addr;
    bool searchuser(QString username,QString passwd);///用来再自己的数据库查找用户
  //  void registeruser(QString username,QString passwd);/////用来进行新的用户的注册；
    void search_friendlist(QString name,QStringList *fridendlist);
};

#endif // TCPSOCKET_CLIENT_H
