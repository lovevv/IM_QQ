#include "chat.h"
#include "ui_chat.h"
#include <QPalette>
#include <QDir>
#include "chat_face.h"


chat::chat(QWidget *parent,QString myname,QString name_tosend,int ispositive) :
    QDialog(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    this->myname=myname;
    this->name_tosend=name_tosend;
    this->ispositive=ispositive;
  ////  qDebug()<<"my ispocitive is "<<ispositive<<"--------15";

    ui->front_size->insertItem(0,tr("8"));
    ui->front_size->insertItem(1,tr("9"));
    ui->front_size->insertItem(2,tr("10"));
    ui->front_size->insertItem(3,tr("11"));
    ui->front_size->insertItem(4,tr("12"));
    ui->front_size->insertItem(5,tr("13"));
    ui->front_size->insertItem(6,tr("14"));
    ui->front_size->insertItem(7,tr("15"));
    ui->front_size->insertItem(8,tr("16"));
    ui->front_size->insertItem(9,tr("17"));
    ui->front_size->insertItem(10,tr("18"));
    ui->front_size->insertItem(11,tr("19"));
    ui->front_size->insertItem(12,tr("20"));

  //  ui->textEdit->append("<img src='./resorces/1.bmp'>");/////可以用来获取图片资源么有问题

////////////////////////////////用来进行背景图片的设置；
    QPalette pal;
   // QPixmap mypix(QDir::toNativeSeparators("./resorces/login.jpg"));///zheyang yeshi keyide
    QPixmap mypix("./resorces/login.jpg");
    pal.setBrush(QPalette::Window, QBrush(mypix));
    setPalette(pal);
    //////////////////////////////////////
   // ui->textEdit->setText(s);
   // edit->setText(s);



    connect(ui->send_chat,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
    connect(ui->close_chat,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()));//////再筐子定义的时候链接到信号；

 //   connect(ui->QQface,SIGNAL(clicked()),this,SLOT(on_QQface_clicked()));
}

chat::~chat()
{
    delete ui;
}

void chat::on_pushButton_2_clicked()
{
    this->close();
}

void chat::on_pushButton_clicked()
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
 //   QString msg=ui->textEdit->toPlainText();//获取要发送的信息，只能获取文本
    QString msg=ui->textEdit->toHtml();//////这样获取的是整个html页面的格式，是不是邮电浪费？？？？？！！！！！格式太多！！！！

    qDebug()<<"i get the msg to send is the picture "<<msg;

    QString name=get_myname();
    QString sendname=get_sendname();

    ui->textBrowser->setTextColor(Qt::green);
    ui->textBrowser->setCurrentFont(QFont("Times New Roman",11));/////设置发送的字体
    ui->textBrowser->append("[ " +myname+" ] "+ time);
    ui->textBrowser->append(msg);
    ////ui->textEdit->append("<img src='./resorces/1.bmp'>");

    ui->textEdit->clear();
    ui->textEdit->setFocus();////发送完数据清空缓存，等待下次发送；
    if(ispositive)
        emit(send_msg(name,sendname,msg));//数据设置好了以后发送信号给主窗口的套接字；
    else
        emit(respond_msg(sendname,name,msg));

}

void chat::show_newmsg(QString name, QString sendname, QString msg)/////发送者的姓名，我的姓名，msg
{
    qDebug()<<"show_newmsg------------------70";
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->textBrowser->setTextColor(Qt::red);//
    ui->textBrowser->setCurrentFont(QFont("Times New Roman",11));/////设置发送的字体
    ui->textBrowser->append("[ " +name+" ] "+ time);//////
    ui->textBrowser->append(msg);
    ui->textEdit->setFocus();
}

void chat::on_close_chat_clicked()
{

    if(ispositive==1)
   {
        qDebug()<<"send close_chat(name_tosend,1)";
        emit close_chat(name_tosend,1);/////主动发起的窗口对应是sendlist的处理，被动接收的窗口是receivelist的处理
    }
    else
      {
        qDebug()<<"send close_chat(name_tosend,0)";
        emit close_chat(name_tosend,0);/////
    }
    qDebug()<<"you press the close of the chat,the communication with "+name_tosend+"will be end ";
    ///////////////////////////////////////////////////////////////////////////////////
    //保存再textbrower中的信息到本地的记录
    QString file_record=ui->textBrowser->toHtml();///////保存到本地的文件
    QString record_intext=ui->textBrowser->toPlainText();
    if(record_intext.size()==0)
    {
        qDebug()<<"file length is  0 ,you need not to save it!!";
        return;
    }
    QString my_name=get_myname();
    QString send_name=get_sendname();

    QDir *mulu=new QDir();
    QString str_mulu="./"+myname+"_"+send_name;
    bool exist=mulu->exists(str_mulu);
    if(exist)
    {
        qDebug()<<"dir has been exist ,you can not creat it again";
        QString filename=str_mulu+"/a.txt";
        QFile file(filename);
        if(!file.open(QIODevice::Append|QIODevice::Text))/////如果文件不存在并且指定IO_WriteOnly或IO_ReadWrite时，文件被创建。
            qDebug()<<"this has a fail in the file write";
        else
        {
            QTextStream in(&file);
            in<<file_record;
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
            QString filename=str_mulu+"/a.txt";
            QFile file(filename);
            if(!file.open(QIODevice::Append|QIODevice::Text))/////如果文件不存在并且指定IO_WriteOnly或IO_ReadWrite时，文件被创建。
                qDebug()<<"this has a fail in the file write";
            else
            {
                QTextStream in(&file);
                in<<file_record;
            }
            file.flush();
            file.close();
            qDebug()<<"file has been save it!!!!!!!!!!!";
        }
        else
            qDebug()<<"creat fail";
    }
}

void chat::on_QQface_clicked()
{
    qDebug()<<"in the on_QQface_clicked";
    chat_face *mychat_face=new chat_face();
    qDebug()<<"on_QQface_clicked() is press";

    mychat_face->show();
    connect(mychat_face,SIGNAL(load_face(QString)),this,SLOT(loadface(QString)));
    qDebug()<<"on_QQface_clicked after";
}

void chat::loadface(QString clickedname)
{
    qDebug()<<"in the loadface------127";
    QString beclick_name=clickedname;
   // beclick_name.split("_")
    int num_name=beclick_name.size();

    QStringList array;
    QString second_name;

    if(num_name==5)
        ui->textEdit->append("<img src='./imqface/1.gif'>");
    else
    {
        array=beclick_name.split("_");////字符串分割，将对应的图片资源加载到聊天窗口
        second_name=array.at(1);
        qDebug()<<"second_name is now -------162"<<second_name;
        ui->textEdit->append("<img src='./imqface/"+second_name+".gif'>");
    }
}

void chat::on_front_color_clicked()
{
    mycolor=QColorDialog::getColor(mycolor,this);
    if(mycolor.isValid())
    {
        ui->textEdit->setTextColor(mycolor);
        ui->textEdit->setFocus();
    }
}

void chat::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->textEdit->setCurrentFont(f);
//    qDebug()<<"you are change the front format";
    ui->textEdit->setFocus();
}

void chat::on_front_size_currentIndexChanged(const QString &arg1)
{
    ui->textEdit->setFontPointSize(arg1.toDouble());
    ui->textEdit->setFocus();
}

void chat::on_toolButton_4_clicked()////关于聊天记录的保存
{
    QString my_name=get_myname();
    QString send_name=get_sendname();
//    QDir *mulu=new QDir();
//    QString str_mulu="./"+myname+"_"+send_name;
//    bool exist=mulu->exists(str_mulu);

//    if(exist)//////目录存在课进行读取，
//    {
//        QString fileName = str_mulu+"/a.txt";
//        QString str_line;
//        QFile file(fileName);
//        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        {
//            //QMessageBox::warning(this,"Warnning","can't open",QMessageBox::Yes);
//        }
//        QTextStream in(&file);
//        while(!in.atEnd())//////不要来判断文件是否是已经结束了，这样会导致在重新显示记录的时候格式又问题
//        {
            //str_line=in.readAll();//读取一行//如果读取多行
           // ui->textBrowser->append(str_line);信号到新的窗口进行显示本地记录；
            history_record *record_dialog=new history_record();
            record_dialog->show();
            connect(this,SIGNAL(load_historyrecord(QString,QString)),record_dialog,SLOT(load_historyrecord(QString,QString)));
            emit load_historyrecord(my_name,send_name);
//        }
//            file.flush();
//        file.close();
//    }
//    else
//        qDebug()<<"has a fail in the dir ,there no it";

}

void chat::on_filetrans_clicked()/////实现文件传输问题
{
    this->resize(600,421);////heshi bili wei 423,421
 //   this->setMaximumSize();
    this->setMinimumSize(600,421);
    this->setMaximumSize(600,421);


    vboxlayout=new QVBoxLayout(ui->widget);
    horizontal=new QHBoxLayout(ui->widget);
    process=new QProgressBar(ui->widget);
    process->setValue(0);
    horizontal->addWidget(process);
    process->show();
    vboxlayout->addLayout(horizontal);

    push_set=new QHBoxLayout(ui->widget);
    button1=new QPushButton(ui->widget);
    button1->resize(100,30);
    //button1->setWindowTitle("打开");
    button1->setText(tr("打开"));
    connect(button1,SIGNAL(clicked()),this,SLOT(file_open_tosend()));
    button1->show();


    button2=new QPushButton(ui->widget);
    button2->setText(tr("发送"));//////解决中文乱码问题，在主函数main添加 QTextCodec::setCodecForTr(QTextCodec::codecForLocale());即可
    button2->resize(100,30);
    push_set->addWidget(button1);
    push_set->addWidget(button2);
    connect(button2,SIGNAL(clicked()),this,SLOT(sendfile()));
    button2->show();
    vboxlayout->addLayout(push_set);
}

void chat::close_filetrans(QString msg_from, QString myname)

{

  //  if(myname)
   // vboxlayout->removeWidget(ui->widget);
   // horizontal->removeWidget(ui->widget);
    this->setMinimumSize(423,421);
    this->setMaximumSize(423,421);
    process->close();
  //  push_set->removeWidget(ui->widget);
    button1->close();
    button2->close();
    this->resize(423,421);
   // this->setMaximumSize(423,421);
}

void chat::file_open_tosend()//////定义用来打开文件浏览器，随后进行文件传输
{
    fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        qDebug()<<"fille name is the things doing in the flower"<<fileName;
    }
}
void chat::sendfile()
{
    QString myname=get_myname();
    QString sendname=get_sendname();

    server=new QTcpServer();
    port=setport();
    if(!server->listen(QHostAddress::Any,port))
        qDebug()<<server->errorString();
    else
        qDebug()<<"server in the client has been set now!!!!!!!!!!"<<"-----and it port is ---------310"<<port;

    connect(server,SIGNAL(newConnection()),this,SLOT(accept_connect()));
    emit get_sendip_port(myname,sendname,port);
}


void chat::accept_connect()
{

    /*
      当接收发送方建立的链接以后就向其发送文件，检测自己的链接信号即可判断
      */
    socket=server->nextPendingConnection();
    qDebug()<<"jianli wenjian chuanshu de lianjie ----------------------------333";
 //   connect(socket,SIGNAL(readyRead()),this,SLOT(update_serverprocess()));

    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(display_error(QAbstractSocket::SocketError)));
    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(update_serverprocess(qint64)));

    server->close();///////此时不再接收其他的用户的链接请求；

    loadSize = 4*1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;

    localFile=new QFile(fileName);
    if(!localFile->open(QIODevice::ReadOnly))
    {
        qDebug()<<"file open fail ,over it now!!-----352";
        return;
    }
    totalBytes=localFile->size();////huoqu wenjian daxiao
    QDataStream sendout(&outBlock,QIODevice::WriteOnly);

    qDebug()<<"wenjian daxiaos shi totalBytes==="<<totalBytes;
    QString  currentname=fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);
    qDebug()<<"current fileName is the things ---"<<currentname;

    sendout<<qint64(0)<<qint64(0)<<currentname;
    totalBytes+=outBlock.size();
    sendout.device()->seek(0);
    sendout<<totalBytes<<qint64(outBlock.size()-sizeof(qint64)*2);/////表明发送文件的总大小，文件名信息空间，文件名

    bytesToWrite=totalBytes-socket->write(outBlock);
    outBlock.resize(0);

}

void chat::trans_file()
{
    qDebug()<<"in the trans_file ,you can get it-----342";
   // fileName=
    localFile=new QFile(fileName);
    if(!localFile->open(QIODevice::ReadOnly))
    {
        qDebug()<<"file open fail ,over it now!!-----352";
        return;
    }
    totalBytes=localFile->size();////huoqu wenjian daxiao
    qDebug()<<"wenjian daxiaos shi totalBytes==="<<totalBytes;
}

void chat::update_serverprocess(qint64 numbytes)
{
    qDebug()<<"11111111111111111111111111111";
    bytesWritten+=(int)numbytes;
    if(bytesToWrite>0)///表示还是又数据继续进行发送
    {
        outBlock=localFile->read(qMin(bytesToWrite,loadSize));
        bytesToWrite-=(int)socket->write(outBlock);
        outBlock.resize(0);////清空缓冲区
    }
    else
    {
        localFile->close();
        qDebug()<<"wenjian yijing fasong wanbi";
    }
    process->setMaximum(totalBytes);
    process->setValue(bytesWritten);
    if(bytesWritten==totalBytes)
    {
        localFile->close();
        socket->close();
        qDebug()<<"file trans over now";
    }

}

void chat::display_error(QAbstractSocket::SocketError)/////表明这个时候出现了错误；应该进行相关的处理
{
    qDebug()<<socket->errorString();
    socket->close();
}

int  chat::setport()
{
    QTime time=QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    return (qrand()%(32700-1024+1)+1024);
}
////关于文件传输问题：
/*
  主动发送方做server，将
  */
