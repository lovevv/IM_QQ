#include "IMQ_server.h"
#include "Tcpsocket_client.h"
#include <stdlib.h>
#include <QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<stdio.h>
#include <QDateTime>
#include "message.h"

IMQ_server::IMQ_server(QObject *parent,int port):QTcpServer(parent)
{
    qDebug("jianli ziji erver oject");
    usernum=0;//用户数目的初始化
    if(!listen(QHostAddress::Any,server_port))
        qDebug()<<this->errorString();
    else
    {
      db=QSqlDatabase::addDatabase("QMYSQL");
      db.setHostName("localhost");
      db.setDatabaseName("IMQ");
      db.setUserName("root");
      db.setPassword("");
      bool ok=db.open();
      if(!ok)
      {
          qDebug("open database fail");
          exit(0);
      }
      else
      {
        QSqlQuery query;
          query.exec("select * from _user");
          while(query.next())//将用户的信息保存在
          {
              strcpy(user_msg[usernum].username,query.value(0).toString().toLatin1().data());
              strcpy(user_msg[usernum].passwd,query.value(1).toString().toLatin1().data());
              user_msg[usernum].status=query.value(2).toInt();
               usernum++;
          }
//          for(int i=0;i<usernum;i++)
//             qDebug(user_msg[usernum].username.toLatin1().data());
      }
    }
}


void IMQ_server::incomingConnection(int socketDescriptor)// 当有用户的链接请求到来的时候会触发这个函数，创建套接字和用户进行交互
{
    qDebug("incoming hanshu kaishi jinxing tiaoyong");
    Tcpsocket_client *connection=new Tcpsocket_client(this);


    if( connection->setSocketDescriptor(socketDescriptor))
        qDebug("connect success");

    connect(connection,SIGNAL(newonline(QString,QHostAddress,Tcpsocket_client *)),this,SLOT(Addnewuser(QString,QHostAddress,Tcpsocket_client*)));
    connect(connection,SIGNAL(disconnected()),this,SLOT(removeuser()));
  //  connect(connection,SIGNAL(newmessage(quint16,quint16,char*)),this,SLOT(sendmessage(quint16,quint16,char*)));
    connect(connection,SIGNAL(newmessage(QString,QString,QString)),this,SLOT(sendmessage(QString,QString,QString)));
    connect(this,SIGNAL(outline_file(QString,QString,QString)),this,SLOT(sendmessage(QString,QString,QString)));

    connect(this,SIGNAL(relogin()),connection,SLOT(is_relogin()));
    connect(connection,SIGNAL(new_register(QString,QString)),this,SLOT(newu_register(QString,QString)));
    connect(this,SIGNAL(register_info(int)),connection,SLOT(is_registerok(int)));
    connect(connection,SIGNAL(new_infologin(QString)),this,SLOT(info_friendlogin(QString)));////////用户登录后会向其所有还有发送本人现在登录的信息；
    connect(connection,SIGNAL(info_offline(QString)),this,SLOT(info_friendoffline(QString)));
    connect(this,SIGNAL(is_haveoutline_msg(QString)),this,SLOT(send_outlinefile(QString)));

 //   connect(connection,SIGNAL(get_socket(QString,QString)),this,SLOT(return_socket(QString,QString)));
    connect(connection,SIGNAL(get_socket(QString,QString,int)),this,SLOT(return_socket(QString,QString,int)));
    connect(connection,SIGNAL(refuse_file(QString,QString)),this,SLOT(refuse_file(QString,QString)));
    connect(connection,SIGNAL(successfile(QString,QString)),this,SLOT(successfile(QString,QString)));
  //  connect(connection,SIGNAL(is_haveoutline_msg(QString)),this,SLOT(send_outlinefile(QString)));
//        struct _user temp;
//        if(connection->write((char *)&temp,sizeof(temp)));
//            qDebug("write data is success");
}

void IMQ_server::successfile(QString msg_from, QString sendname)
{
    qDebug()<<"sendname is "<<sendname<<"in the 10 types ";
    QHash<QString, Tcpsocket_client *>::const_iterator i;
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out<<quint16(10)<<msg_from<<sendname;//// 发送者，接受者，msg

    for(i=connectionlist.constBegin();i!=connectionlist.constEnd();i++)
    {
        if(sendname==i.key())
        {
             i.value()->write(buffer);
         }
    }
}

void IMQ_server::refuse_file(QString msg_from, QString sendname)///发送拒绝信息给请求方
{
    QHash<QString, Tcpsocket_client *>::const_iterator i;
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out<<quint16(9)<<msg_from<<sendname;//// 发送者，接受者，msg

    for(i=connectionlist.constBegin();i!=connectionlist.constEnd();i++)
    {
        if(sendname==i.key())
        {
             i.value()->write(buffer);
         }
    }
}

void IMQ_server::return_socket(QString myname, QString sendname,int portt)
{
    QHash<QString, Tcpsocket_client *>::const_iterator i;
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
   // Tcpsocket_client *need_socket;
    out<<quint16(7)<<myname<<sendname<<portt;

    qDebug()<<"in the return_socket-------85"<<"myname is "<<myname<<"sendname is"<<sendname;
    for(i=connectionlist.constBegin();i!=connectionlist.constEnd();i++)
    {
        if(sendname==i.key())
        {
            i.value()->write(buffer);
         }
    }
}

void IMQ_server::send_outlinefile(QString newname)
{
    qDebug()<<"Now!!!!!!!!! we are going to judge is there have a lixian file!!!!!!!!!!!!!!  and what  name is";
    QString name=newname;

    QString filepath="./"+name;
    QDir mulu(filepath);

    QStringList file_ls=mulu.entryList(QDir::Files);
    QStringList split_filename;

    int num_list=file_ls.size();
    QString filename;

    QString sendname;
    QString myname=name;
    QString msg;
    QString file_readpath;

    for(int i=0;i<num_list;i++)
    {
        filename=static_cast<QString>(file_ls.at(i));
        qDebug()<<filename;////////可以判断到文件了，这个时候就可以发送消息给用户了；
        split_filename=filename.split(".");
        sendname=split_filename.at(0);////发送方的id标示
    //    qDebug()<<"in the lixian wenjian zheli de fasong fang de mingzi shi--------199"<<sendname;
        file_readpath=filepath+"/"+sendname+".txt";
        QFile file_read(file_readpath);
        if(!file_read.open(QIODevice::ReadOnly))
            qDebug()<<"file open is fail ,you can not open it,please check it";
        else
        {
            QTextStream in(&file_read);
            msg=in.readAll();
            qDebug()<<"msg is in the lixian -------210"<<msg;
        }
        emit outline_file(sendname,myname,msg);
       // file_read.deleteLater();
        //mulu.rmdir(file_readpath);
     //   mulu.remove(file_readpath);
        QFile::remove(file_readpath);
    }
}

void IMQ_server::info_friendlogin(QString loginname)
{
    QSqlQuery squery;
    QString name;
    QHash<QString, Tcpsocket_client *>::const_iterator i;

    qDebug()<<"in the infomation to tell myfriend i am coming";
    char sqlchar[50]="select * from";
    strcat(sqlchar," f_");
    strcat(sqlchar,loginname.toLatin1().data());
    qDebug()<<sqlchar;
    squery.exec(sqlchar);

    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out<<quint16(5)<<loginname;/////我是谁？我登录


    while(squery.next())
    {
        // fridendlist->append(squery.value(0).toString());/////获取好友又列表
        name=squery.value(0).toString();
        qDebug()<<"name is the infomation----in 82 -----------------------"<<name;
        for(i=connectionlist.begin();i!=connectionlist.end();i++)
        {
            if(i.key()==name&&i.key()!=loginname)
            {
                qDebug()<<"fridend name is"<<name<<"myname is "<<loginname;
                i.value()->write(buffer);
            }
        }
    }
   emit is_haveoutline_msg(loginname);
}

void IMQ_server::info_friendoffline(QString offlinename)/////下线的消息这里貌似是没哟进行通知到其好友埃。。。。。。！！！！
{
    QSqlQuery squery;
    QString name;
    QHash<QString, Tcpsocket_client *>::const_iterator i;

    qDebug()<<"in the infomation to tell myfriend i am left";
    char sqlchar[50]="select * from";
    strcat(sqlchar," f_");
    strcat(sqlchar,offlinename.toLatin1().data());
    qDebug()<<sqlchar;
    squery.exec(sqlchar);

    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);



    while(squery.next())
    {
        // fridendlist->append(squery.value(0).toString());/////获取好友又列表
        name=squery.value(0).toString();
        qDebug()<<"name is the infomation----in offline 82 -----------------------"<<name;
        for(i=connectionlist.begin();i!=connectionlist.end();i++)
        {
            if(i.key()==name&&name!=offlinename)
            {
                qDebug()<<"fridend name is"<<name<<"ooflinename is "<<offlinename;
                out<<quint16(6)<<offlinename;
                i.value()->write(buffer);////服务器没有帮我转发？？！！！！不！！！转发的貌似有问题，接受端的类别怎么总是8？？？？！！！
            }
        }
    }

}

void IMQ_server::newu_register(QString name, QString passwd)
{
    qDebug()<<"in the server register doing----68";
    QSqlQuery squery;
    QString sqlchar="insert into _user values('"+name+"','"+passwd+"',"+"0)";
    if(squery.exec(sqlchar))
     {
        emit register_info(1);
        qDebug("register success");
    }
    else
    {
        emit register_info(0);
        qDebug("register fail");
    }
}

void IMQ_server::Addnewuser(QString name, QHostAddress addr, Tcpsocket_client *socket)
{
        QHash<QString, Tcpsocket_client *>::const_iterator i;
        qDebug("add user");
        int j=0;
        for(i=connectionlist.constBegin();i!=connectionlist.constEnd();i++)
        {
            if(i.key()==name)
             {
                j++;
                break;
            }
        }
        if(j==1)
        {
            qDebug("yonghu yingjing cunzai");
            emit(relogin());/////如果再验证的登录的是用户是已经存在了的，发送重复登录的警告；
            return;
        }
        else
        {
            qDebug("xin zhengjia yige yonghu");
            connectionlist.insert(name,socket);
            //////这里要来判断用户有没有离线文件//////////////在用户的文件下下查找


        }
        for(i=connectionlist.constBegin();i!=connectionlist.constEnd();i++)////用来显示此时已经登录到服务器的用户的名字和套接字列表
        {
            qDebug()<<i.key();
            qDebug()<<i.value();
        }
}



void IMQ_server::removeuser()
{
    qDebug("remove is doing");
    Tcpsocket_client *connection=qobject_cast<Tcpsocket_client *>(sender());
    QHash<QString, Tcpsocket_client *>::const_iterator i;
    QString offline_name=connection->getname();
    qDebug()<<"offline is the"<<offline_name<<"doing now!!!!!!";

    connectionlist.remove(connection->getname());//断开与特定一个用户之间的链接；

    quint16 blockSize=(quint16)sizeof(connection->getname());
    QDataStream out;
    for(i=connectionlist.constBegin();i!=connectionlist.constEnd();i++){
        out.setDevice(i.value());
        out<<blockSize<<(quint16)3<<connection->getname();
    }
    connection->deleteLater();
    for(i=connectionlist.constBegin();i!=connectionlist.constEnd();i++)
    {
        qDebug()<<i.key();
        qDebug()<<i.value();
    }

}

//////注意本文件转移到/home/schlinux/1111111111文件夹下//////////

void IMQ_server::sendmessage(QString name, QString sendname, QString msg)/////////newmessage信号------》sendmessage
{
//       QString currentDateTime=QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm:ss");
//       buffer+=(quint16)sizeof(currentDateTime);
       QHash<QString, Tcpsocket_client *>::const_iterator i;
       QByteArray buffer;
       QDataStream out(&buffer,QIODevice::WriteOnly);
       out<<quint16(3)<<name<<sendname<<msg;//// 发送者，接受者，msg
    //   Tcpsocket_client *connection;
       bool islogin_user=false;////判断这个用户所是否是已经登录，没有的华服务器端要求保存客户的消息

       for(i=connectionlist.constBegin();i!=connectionlist.constEnd();i++)
       {
           if(sendname==i.key())
           {
                //connection=i.value();
               islogin_user=true;
                i.value()->write(buffer);
             //   connection->write(buffer);////用来进行写信息到指定的套接字中去；
            }
       }
       if(!islogin_user)///表明这个时候是没有登录的用户,服务器应该建立相应的文件夹来保存用户的离线消息，等到用户登录的时候，向用户发送消息，且要求
           //删除已存在的文件记录即可
           //约定：接收者是文件夹名，发送者是文件名
       {
           QDir *mulu=new QDir();
           QString str_mulu="./"+sendname;
           bool exist=mulu->exists(str_mulu);
           if(exist)
           {
               qDebug()<<"dir has been exist ,you can not creat it again";
               QString filename=str_mulu+"/"+name+".txt";
               QFile file(filename);
               if(!file.open(QIODevice::Append|QIODevice::Text))/////如果文件不存在并且指定IO_WriteOnly或IO_ReadWrite时，文件被创建。
                   qDebug()<<"this has a fail in the file write";
               else
               {
                   QTextStream in(&file);
                   in<<msg;
               }
               file.flush();
               file.close();
               qDebug()<<"file has been save it!!!!!!!!!!!";
           }
           else
           {
               bool create_ok=mulu->mkdir(str_mulu);
               if(create_ok)
                {
                   qDebug()<<"dir creart is success now";
                 //  qDebug()<<"dir has been exist ,you can not creat it again";
                   QString filename=str_mulu+"/"+name+".txt";
                   QFile file(filename);
                   if(!file.open(QIODevice::Append|QIODevice::Text))/////如果文件不存在并且指定IO_WriteOnly或IO_ReadWrite时，文件被创建。
                       qDebug()<<"this has a fail in the file write";
                   else
                   {
                       QTextStream in(&file);
                       in<<msg;
                   }
                   file.flush();
                   file.close();
                   qDebug()<<"file has been save it!!!!!!!!!!!";
               }
               else
                   qDebug()<<"creat fail";
           }
       }
     //  delete [] message;
}



