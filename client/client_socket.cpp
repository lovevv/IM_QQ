#include "client_socket.h"
#include <QMessageBox>

client_socket::client_socket(QObject *parent):QTcpSocket(parent)
{
    is_registering=false;
   // connect(this,SIGNAL(bytesWritten(qint64)))
    connect(this,SIGNAL(connected()),this,SLOT(sendmsg_login(_message_toser)));
    connect(this,SIGNAL(readyRead()),this,SLOT(read_msg()));
}

void client_socket::sendmsg_login()
{
    qDebug("i am lianjie dao le sever a !!!gan ni dayede");
}

void client_socket::get_friendslist(QString name)
{
    qDebug("get_friendslist is runing --------------------18");
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    quint16 request=4;//表明这个是要求server给我发我的好友列表
    QString myname=name;
    out<<request<<myname;
    this->write(buffer);
}


void client_socket::send_msg(QString name, QString sendname, QString msg)
{
    qDebug("now in the sendmsg!!!-----------------send_msg---30");
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out<<quint16(3);////表示是要求server进行转发的数据；
    out<<name<<sendname<<msg;///////发送者的名字，要发送到的名字，信息
    this->write(buffer);////进行数据的发送；
}

void client_socket::respond_msg(QString name, QString sendname, QString msg)
{
    qDebug("now in the rspond!!!-----------------send_msg---30");
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out<<quint16(3);////表示是要求server进行转发的数据；
    out<<sendname<<name<<msg;///////发送者的名字，要发送到的名字，信息
    this->write(buffer);////进行数据的发送；
}

void client_socket::info_myfriend_login()
{
    qDebug()<<"info myfriend is doing";
    QString sendname=getname();
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out<<quint16(5);///表示此消息是向好友群发的“我”登录的信息；
    out<<sendname;
    this->write(buffer);
 //   qDebug()<<"myname in 55 client_socket.cpp is "<<getname();
    return;
}

void client_socket::info_myfriend_offline()
{
    qDebug()<<"info myfriend  i am doing offline is doing";
    QString sendname=getname();
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out<<quint16(6);///表示此消息是向好友群发的“我”xiaxian的信息；
    out<<sendname;
    this->write(buffer);
 //   qDebug()<<"myname in 55 client_socket.cpp is "<<getname();
    return;
}

void client_socket::read_msg()
{
    quint16 datatype;       //接收数据的类型，1表示登录的具体信息，2表示注册的信息，3表示是转发接收到的信息，4表示获取用户列表信息；
    quint16  is_canlogin;   //判断是否可以进行登录，解决重复登录问题
    quint16 is_canregister; //判断注册是否成功
    QString displsyname;

    QString msg_from;   ///信息发送这
    QString myname; ///接收这本人阿
    int port;/////文件传输时候的服务器的端口号

    QString msg;
    QStringList fridendslist;
    QString new_loginname;///新登录用户
    QString offline_name;/////下线的用户




////////以上定义的为接收到的信息的具体的格式///////////////////////////////////

    QDataStream in(this);
    in>>datatype;
    qDebug()<<"datatype is "<<datatype;

    switch(datatype)
    {
    case 1:
       // qDebug("登录返回的信息：");
        in>>is_canlogin>>displsyname;
        qDebug()<<displsyname;
        if(is_canlogin==quint16(1))
            emit (login_mainframe(displsyname));//发送一个信号前端进行用户的登录；
        else
    //        QMessageBox::information(this,"NO port","please input port of sever");
            qDebug("relogin");
        break;
    case 2:
        in>>is_canregister;
   //     qDebug()<<"is_canregister=="<<is_canregister;
        emit showrgs_result(is_canregister);
        break;
    case 3:
        qDebug("i am jieshou zhege shuju ane a ----------------------------------------");
        in>>msg_from>>myname>>msg;
        emit(showmessage(msg_from,myname,msg));
        qDebug()<<msg;
        break;
    case 4:
        qDebug("i got the 4 in the client ");
        in>>fridendslist;
        for(int i=0;i<fridendslist.size();i++)////客户端可以成功的拿到数据了
            qDebug()<<fridendslist.at(i);
        emit(set_friendslist(fridendslist));/////发送信号源；
        break;
    case 5:
        qDebug("i got the 5 in the client ");
        in>>new_loginname;
        qDebug()<<"new login is the person -----"<<new_loginname;
        emit (update_fridenglist_login(new_loginname));
        break;
    case 6:
       qDebug("i got the 6 in the client ");//////为什么每次这样接收到的都是8，再以前,
       in>>offline_name;
       qDebug()<<"offline name is the ---"<<offline_name<<"in the mesesage in the 117-----test";
       emit update_fridenglist_offline(offline_name);///发送用户下线的信息；
       break;
    case 7:
         qDebug("i got the 7 in the client ");
         in>>msg_from>>myname>>port;
         qDebug()<<"msg from "<<msg_from<<"myname is "<<myname<<"port is "<<port;///客户端新建立链接即将
         emit should_connect(msg_from,myname,port);
         break;
    case 9:
        qDebug("i got the 9 in the client ");
        in>>msg_from>>myname;///信息来源和信息接受这就是本人自己
        emit close_filetrans(msg_from,myname);
        break;
    case 10:
        qDebug("i got the 9 in the client ");
        in>>msg_from>>myname;///信息来源和信息接受这就是本人自己
        emit close_filetrans(msg_from,myname);
        break;
    default:
        break;
    }
}
/*
  关于在进行用户离线通知时候遇到的问题：
        很奇怪！！！！！！！
        用户的离线可以又两种方式来实现：
                1.一种是再客户端关闭用户窗口的时候向server发送离开消息，这里统一将信息俄类别标示为 6
                    而后经客户端socket向server发送消息，表明自己离开，server拿到离开详细，向给用户的好友发送其已经下线的信息
                    好友的客户端接受到由服务器发来的消息后检测类别为6表示是有人离线即可；
                2.服务器本身你的disconnected信号可以用来来触发一个客户端的离线，再remove用户中向好友发送离线的消息应该也是
                    可以的，但是再这里是现上客户端检测到的消息的类别总算是8，肯定是再信息组合上出现问题，待解决，目前为第一种
                    方案解决；
  */

void client_socket::get_sendip(QString myname, QString sendname, int portt)
{
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out<<quint16(7);//获取一个客户端的ip和端口
    out<<myname<<sendname<<portt;
    this->write(buffer);
    qDebug()<<"now i am doing the things that i want to get the kefuduan de ip and port!!!!!!!!!!!!!!!!!!!----159"<<myname<<"---"<<sendname;
    return;
}

void client_socket::refuse_file(QString msg_from, QString name)
{
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out<<quint16(9);////表示是拒绝接收文件的信息
    out<<name<<msg_from;
    this->write(buffer);
   // qDebug()<<"now i am doing the things that i want to get the kefuduan de ip and port!!!!!!!!!!!!!!!!!!!----159"<<myname<<"---"<<sendname;
    return;
}


void client_socket::receive_success(QString msg_from, QString myname)
{
    qDebug()<<"fail has been receive success !!!"<<"--and msg_from is "<<msg_from<<"myname is "<<myname;
    //////sender is 001 and receicer is 002
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out<<quint16(10);////表示接收文件成功的信号
    out<<myname<<msg_from;
    this->write(buffer);
   // qDebug()<<"now i am doing the things that i want to get the kefuduan de ip and port!!!!!!!!!!!!!!!!!!!----159"<<myname<<"---"<<sendname;
    return;

}
