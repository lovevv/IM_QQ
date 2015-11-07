#include "user_register.h"
#include "ui_user_register.h"

#include <QMessageBox>
#include <QDir>

user_register::user_register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_register)
{
    ui->setupUi(this);
    QPalette pal;
    QPixmap mypix(QDir::toNativeSeparators("./resorces/login.jpg"));
    pal.setBrush(QPalette::Window, QBrush(mypix));
    setPalette(pal);
}

user_register::~user_register()
{
    delete ui;
}

void user_register::on_u_register_clicked()
{
    ui->u_register->setDisabled(true);
    QString username=ui->line_user->text();
    QString passwd=ui->line_pwd->text();
    QString comfirn_msg=ui->line_pwdcfm->text();
    if(username.size()==0||passwd.size()==0)
   {
        QMessageBox::information(this,"NO uername","please input username or passwd");
        return;
    }
    else if(passwd!=comfirn_msg)
    {
         QMessageBox::information(this,"Noooo","confirm is not right");
         return;
    }
    else
    {
     //   emit new_register(username,passwd);原来是用信号来进行和登录界面进行交互的再注册的时候，其实这个也是单独可以进行的哈
            qDebug()<<"new register is doing------66";
            this->rsg_socke=new client_socket();
            rsg_socke->connectToHost("127.0.0.1",1234);

            QByteArray buffer;
            QDataStream out(&buffer,QIODevice::WriteOnly);////再链接以后进行信息的注册
            qDebug()<<"------69";
            out<<(quint16)2;    ////注册信息类型
            out<<username<<passwd;
            qDebug()<<"------72";
            rsg_socke->write(buffer);
            connect(rsg_socke,SIGNAL(showrgs_result(int)),this,SLOT(showrgs_result(int)));
    }
}

void user_register::showrgs_result(int isok)
{
    if(isok==1)
        QMessageBox::information(this,"ok","user rgs is success");
    else
        QMessageBox::information(this,"no","user has been exists!please shose another");
}

void user_register::on_r_cancel_clicked()
{
    delete rsg_socke;
    this->close();
}
