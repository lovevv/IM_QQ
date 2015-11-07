#include "client.h"
#include "ui_client.h"
#include "message.h"
#include"client_socket.h"
#include <QPalette>

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    this->setWindowTitle("IMQ_login");




    QPalette pal;
    QPixmap mypix(QDir::toNativeSeparators("./resorces/qq.jpg"));
    pal.setBrush(QPalette::Window, QBrush(mypix));
    //pal.setColor(QPalette::Background, QColor(0x00,0xff,0x00,0x00));
    setPalette(pal);
    ui->line_pwd->setEchoMode(QLineEdit::Password);
   // connect(client1,SIGNAL(login_mainframe()),this,SLOT(display_mainframe()));//将套接字进行中的接收到数据的行为绑定到界面的显示上
    //当在套接字山接收到验证信息且此时是验证通过的，那么就进行主界面的显示；
//    setCursor();
    ui->line_user->setFocus();
}

Client::~Client()
{
    delete ui;
}

void Client::on_pushButton_clicked()
{


    client1=new client_socket(this);
 ////   client1->
    qDebug("zhunbei lianjie server");
    client1->connectToHost("127.0.0.1",1234);
    connect(client1,SIGNAL(login_mainframe(QString)),this,SLOT(display_mainframe(QString)));//将套接字进行中的接收到数据的行为绑定到界面的显示上
    //当在套接字山接收到验证信息且此时是验证通过的，那么就进行主界面的显示；
    //将界面上的用户名和密码读入进行验证；
    connect(this,SIGNAL(sendto_getfriendlist(QString)),client1,SLOT(get_friendslist(QString)));
    //此时设置发送消息的类型为1，2为注册信息，3为带转发消息，4可设置为群组消息

    client1->set_name(ui->line_user->text());
    client1->set_pwd(ui->line_pwd->text());

    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out<<(quint16)1;
    out<<client1->getname()<<client1->getpwd()<<client1->localAddress();
    client1->write(buffer);
}

void Client::display_mainframe(QString name)
{
    qDebug("jieshou dao denglu de xinxi le a ");
    mainframe=new Mainframe(0,client1);//将套接字进行转移到新的窗口；

    mainframe->setWindowTitle(name);/////设置登录窗体的用户名；

    this->close();//关闭原来的登录窗体；
    emit(sendto_getfriendlist(name));/////发送信号给  套接字让它向server请求用户列表；
    mainframe->show();
}

//void Client::new_register(QString username, QString passwd)
//{
//    qDebug()<<"new register is doing------66";
//    client_socket  *rsg_socket=new client_socket();
//    rsg_socket->connectToHost("127.0.0.1",1234);

//    QByteArray buffer;
//    QDataStream out(&buffer,QIODevice::WriteOnly);
//    qDebug()<<"------69";
//    out<<(quint16)2;    ////注册信息类型
//    out<<username<<passwd;
//    qDebug()<<"------72";
//    rsg_socket->write(buffer);
////    delete(rsg_socket);
//    qDebug()<<"--------74";
//}

void Client::on_pushButton_3_clicked()
{
    this->close();
}

void Client::on_pushButton_2_clicked()//////register user;
{
    user_register *newuser=new user_register();
    newuser->show();
  //  this->close();
//    connect(newuser,SIGNAL(new_register(QString,QString)),this,SLOT(new_register(QString,QString)));
}
