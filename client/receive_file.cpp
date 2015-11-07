#include "receive_file.h"
#include "ui_receive_file.h"
#include <QDir>
receive_file::receive_file(QWidget *parent,QString msg,QString my,int portt) :
    QWidget(parent),
    ui(new Ui::receive_file)
{
    ui->setupUi(this);
    msg_from=msg;
    myname=my;
    port=portt;
    ///////////////////
    QPalette pal;
    QPixmap mypix(QDir::toNativeSeparators("./resorces/login.jpg"));
    pal.setBrush(QPalette::Window, QBrush(mypix));
    setPalette(pal);
    ////////////////////////



    trans=new QTcpSocket();///建立一个与文件传输server的链接；
    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;

    connect(trans,SIGNAL(connected()),this,SLOT(start_tranfor()));
  //  connect(trans,SIGNAL(bytesWritten(qint64)),this,SLOT(update_clientprocess()));
    connect(trans,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(display_error(QAbstractSocket::SocketError)));
    connect(trans,SIGNAL(readyRead()),this,SLOT(update_clientprocess()));
}

receive_file::~receive_file()
{
    delete ui;
}

void receive_file::start_tranfor()
{
    qDebug()<<"tell us the connect is success!!!";
}

void receive_file::update_clientprocess()
{
    qDebug()<<"wenjian de fasong zai zhege shihou yijingkaishile --------4111111111111111";
    QDataStream in(trans);
    if(bytesReceived<=sizeof(qint64)*2)
    {
        if((trans->bytesAvailable()>=sizeof(qint64)*2)&&fileNameSize==0)
        {
            in>>totalBytes>>fileNameSize;
            bytesReceived+=sizeof(qint64)*2;
        }
        if((trans->bytesAvailable()>=fileNameSize)&&(fileNameSize!=0))/////接收文件名并建立文件
        {
            in>>fileName;
            bytesReceived+=fileNameSize;
            localFile=new QFile(fileName);/////建立文件，并要求再其中写合数据
            if(!localFile->open(QIODevice::WriteOnly))
            {
                qDebug()<<"file set is fail ,cant get set this file";
                return;
            }

        }
        else
            return;
    }
    if(bytesReceived < totalBytes)
    {  //如果接收的数据小于总数据，那么写入文件
        bytesReceived += trans->bytesAvailable();
        inBlock = trans->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesReceived);
    if(bytesReceived == totalBytes)
    {
        trans->close();
        localFile->close();
        emit receive_success(msg_from,myname);///// 文件传输结束后向原来的用户发送完毕的消息
        this->close();
    }
}

void receive_file::display_error(QAbstractSocket::SocketError)
{

}

void receive_file::on_pushButton_2_clicked()///表示拒绝接收文件
{
    qDebug()<<"refuse been push "<<"msgfrom "<<get_msgfrom()<<"myname"<<get_myname()<<"port is "<<get_port();
    QString msgfrom=get_msgfrom();
    QString my=get_myname();
    emit refuse_file(msgfrom,my);/////fasong jujue de xinhao
    this->close();
}

void receive_file::on_pushButton_clicked()
{
    int tran_port=get_port();
    trans->connectToHost("127.0.0.1",tran_port);


}
