#include <QMessageBox>
#include "imqserver.h"
#include "ui_imqserver.h"

#include "IMQ_server.h"

//QWidget 是所有用户界面对象的基类
IMQServer::IMQServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IMQServer)
{
    ui->setupUi(this);
}

IMQServer::~IMQServer()
{
    delete ui;
}

void IMQServer::on_server_link_clicked()
{
    if(ui->link_port->text().size()==0)
        QMessageBox::information(this,"NO port","please input port of sever");
    else
    {
         server=new IMQ_server(0,1234);
    }
}
