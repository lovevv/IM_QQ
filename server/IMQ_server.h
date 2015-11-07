#ifndef IMQ_SERVER_H
#define IMQ_SERVER_H
#include <QtNetwork/QTcpServer>
#include <QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QHash>
#include <QDir>

#include "Tcpsocket_client.h"
#include "message.h"

#define server_port 1234

class IMQ_server : public QTcpServer
{
    Q_OBJECT
public :
    explicit IMQ_server(QObject *parent=0,int port=0);

protected:
    void incomingConnection(int socketDescriptor);

private:
    QHash <QString,Tcpsocket_client *>connectionlist;//用来建立用户的链接的数据结构；
    QSqlDatabase db;
    struct _user user_msg[30];//定义用户的信息，username and passwd;
    int usernum;

private slots:
    void Addnewuser(QString name,QHostAddress addr,Tcpsocket_client *socket);
    void removeuser();
    void sendmessage(QString name,QString sendname,QString msg);
    void newu_register(QString name,QString passwd);/////信息注册者
    void  info_friendoffline(QString offlinename);
    void info_friendlogin(QString loginname);
    void send_outlinefile(QString newname);//发送离线文件

    void return_socket(QString myname,QString sendname,int portt);

    void refuse_file(QString msg_from,QString sendname);
    void successfile(QString msg_from,QString sendname);

signals:
    void relogin();
    void register_info(int isok);
    void info_offline(QString name);
    void outline_file(QString sendname,QString send_toname,QString msg);
     void is_haveoutline_msg(QString name);////判断是否是又离线文件这个时候



};

#endif // IMQ_SERVER_H
