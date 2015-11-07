#include "Tcpsocket_client.h"
#include <QByteArray>
#include <stdio.h>
#include <QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include <QHostAddress>
#include "message.h"

Tcpsocket_client::Tcpsocket_client(QObject *parent):QTcpSocket(parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(messagecoming()));
}
//Tcpsocket_client::~Tcpsocket_client()
//{
//    QTcpSocket::~QTcpSocket();
//}
void Tcpsocket_client::messagecoming()
{
    qDebug("messge comming!!!,you should receive it!");
    QByteArray buffer;
    QStringList friendslist;
    int n;
    quint16 datatype;//首先检测
    QString sendname;     //信息发送者
    QString receivename;       //信息接受者
    QString msg;        ///信息的具体内容
    QString reg_username;  ///注册信息的用户名
    QString reg_passwd;         //// 注册信息的用户密码
    int port;////发送文件是客户端作为服务器的端口号

    //发到server的信息的类型，1：登录信息，2;注册信息，3要转发的消息, 4或取指定用户的好友列表,5群发好友登录信息
    QDataStream in(this);
    QDataStream out(&buffer,QIODevice::WriteOnly);//设置一个接口用来和客户端进行数据的传送

    in>>datatype;
    qDebug()<<datatype;
    QString newname,newpasswd;
    QHostAddress newaddr;
        switch(datatype)
        {
        case 1:
            in>>newname>>newpasswd>>newaddr;//            qDebug()<<newname; //            qDebug()<<newpasswd;
            if(searchuser(newname,newpasswd))
            {
                emit(newonline(newname,newaddr,this));//// 若是再数据库中又用户的信息就登录验证
                qDebug("user login");
                this->username=newname;
                if(relogin)
                    qDebug()<<"in 48--------relogin";
                if(get_reloginstatus())
                    out<<quint16(1)<<quint16(0)<<newname;//此时显示用户不可以登录
                else
                     out<<quint16(1)<<quint16(1)<<newname;//用户验证通过，可以进行登录；
                this->write(buffer);
            }
            else
            {
                qDebug("login error");
            }
            break;
        case 2:
                in>>reg_username>>reg_passwd;
                qDebug()<<"reg_username="<<reg_username<<"reg_passwd="<<reg_passwd;
                emit new_register(reg_username,reg_passwd);
                if(get_registerstatus())
                    out<<quint16(2)<<quint16(1);
                else
                    out<<quint16(2)<<quint16(0);
                this->write(buffer);
                break;
        case 3:
            in>>sendname>>receivename>>msg;/////信息发送者，信息接受者
            qDebug()<<"in the server and the msg is"<<msg<<"myname="<<sendname<<"receivename="<<receivename;
            emit(newmessage(sendname,receivename,msg));
            break;

        case 4:
                in>>newname;///把要查询的用户名督导这里；
                qDebug()<<newname;//可以显示链接用户的名字了，到这里么有问题了阿；
                search_friendlist(newname,&friendslist);
                n=friendslist.size();
                for(int i=0;i<n;i++)
                    qDebug()<<friendslist.at(i);
                out<<quint16(4)<<friendslist;
                this->write(buffer);

                break;
        case 5:
            in>>sendname;
            qDebug()<<"sendname is ----88"<<sendname;
         //   info_friendlogin(sendname);
            emit(new_infologin(sendname));

            break;
        case 6:
            in>>sendname;
            qDebug()<<"there is hace a client si doing offline"<<sendname;
            emit(info_offline(sendname));
        case 7:
            in>>sendname>>receivename>>port;// 发送者，接受者
            qDebug()<<"sendname "<<sendname<<"receivename"<<receivename<<"port is"<<port;
            emit get_socket(sendname,receivename,port);
        case 9:
            qDebug()<<"in the 9 types ";
            in>>sendname>>receivename;
            qDebug()<<"sendname="<<sendname<<"receivename="<<receivename;
            emit refuse_file(sendname,receivename);
            break;
        case 10:
           qDebug()<<"in the 10 types ";
           in>>sendname>>receivename;
           qDebug()<<"sendname="<<sendname<<"receivename="<<receivename;
           emit successfile(sendname,receivename);
        default:
            break;
        }
}

//void Tcpsocket_client::info_friendlogin(QString loginname)
//{
//    QSqlQuery squery;
//    QString name;
//    qDebug()<<"in the infomation to tell myfriend i am coming";
//    char sqlchar[50]="select * from";
//    strcat(sqlchar," f_");
//    strcat(sqlchar,loginname.toLatin1().data());
//    qDebug()<<sqlchar;
//    squery.exec(sqlchar);
//    while(squery.next())
//    {
//       // fridendlist->append(squery.value(0).toString());/////获取好友又列表
//        name=squery.value(0).toString();
//    //   qDebug()<<"name is the infomation"<<name;

//    }
//}

void Tcpsocket_client::search_friendlist(QString name, QStringList *fridendlist)
{
    QSqlQuery squery;
    qDebug("in search_friendlist----------65");
    char sqlchar[50]="select * from";
    strcat(sqlchar," f_");
    strcat(sqlchar,name.toLatin1().data());
    qDebug()<<sqlchar;
    squery.exec(sqlchar);
    while(squery.next())
    {
        fridendlist->append(squery.value(0).toString());/////获取好友又列表
    }
}

bool Tcpsocket_client::searchuser(QString username, QString passwd)//验证用户在数据库中的函数已经没有问题；
{
    QSqlQuery squery;
    squery.exec("select * from _user");
    int i=0;
    int j=0;
    while(squery.next())//检查用户的信息是否再数据库中，一个一个扫描数据库中的记录；
    {
        //(,query.value(0).toString().toLatin1().data());
         if(strcmp(username.toLatin1().data(),squery.value(0).toString().toLatin1().data())==0)
             if(strcmp(passwd.toLatin1().data(),squery.value(1).toString().toLatin1().data())==0)
                j++;
         i++;
    }
    if(j==1)
        return true;
    else
        return false;
}

void  Tcpsocket_client::is_relogin()
{
    qDebug("in the is_relogin()");
    relogin=true;
}

void Tcpsocket_client::is_registerok(int isok)//////当在注册结束的时候会发出这样的一个信号来告知套接字，用户的创建是否是成功的；
{
    if(isok)
        new_rgsok=true;
    else
        new_rgsok=false;
}
