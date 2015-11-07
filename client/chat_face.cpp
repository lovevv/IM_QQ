#include "chat_face.h"
#include "ui_chat_face.h"
#include <QHBoxLayout>
#include"myQlable.h"
chat_face::chat_face(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chat_face)
{
    ui->setupUi(this);
   // myQLabel *lable;
//    ui->default_faces->
    /////////////////////////////这样是可以显示动态的图片的哈，现在的问题是布局的问题了阿///////待解决
//    QGridLayout *horizontal=new QGridLayout();
//    myQLabel *lable1=new myQLabel();
//    QMovie *pm=new QMovie("./imqface/2.gif");
//    lable1->setMovie(pm);
//    pm->start();
//    horizontal->addWidget(lable1,0,4);
//    ui->default_faces->setLayout(horizontal);


    /////这个部分是用来显示动态图片的部分///////////////

        QMovie *pm=new QMovie("./imqface/1.gif");
        ui->label->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/2.gif");
        ui->label_2->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/3.gif");
        ui->label_3->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/4.gif");
        ui->label_4->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/5.gif");
        ui->label_5->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/6.gif");
        ui->label_6->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/7.gif");
        ui->label_7->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/8.gif");
        ui->label_8->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/9.gif");
        ui->label_9->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/10.gif");
        ui->label_10->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/11.gif");
        ui->label_11->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/12.gif");
        ui->label_12->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/13.gif");
        ui->label_13->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/14.gif");
        ui->label_14->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/15.gif");
        ui->label_15->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/16.gif");
        ui->label_16->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/17.gif");
        ui->label_17->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/18.gif");
        ui->label_18->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/19.gif");
        ui->label_19->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/20.gif");
        ui->label_20->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/21.gif");
        ui->label_21->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/22.gif");
        ui->label_22->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/23.gif");
        ui->label_23->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/24.gif");
        ui->label_24->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/25.gif");
        ui->label_25->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/26.gif");
        ui->label_26->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/27.gif");
        ui->label_27->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/28.gif");
        ui->label_28->setMovie(pm);
        pm->start();

        pm=new QMovie("./imqface/29.gif");
        ui->label_29->setMovie(pm);
        pm->start();

//..............................................................................................................................................................
        //坑爹阿！！！！！！！！！！！这个么法写，多的shit！！！！！！！！！！！！！！！！！
    //    /。。。。。。。。。。。。。。
       // 。。。。。。。。。。。。。。。。。。。。。。。
        /////////////////////////////////
        connect(ui->label,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));//将单击的信号链接到相应的槽函数中；
        connect(ui->label_2,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_3,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_4,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_5,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_6,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_7,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_8,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_9,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));

        connect(ui->label_10,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_11,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_12,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_13,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_14,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_15,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_16,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_17,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_18,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_19,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));

        connect(ui->label_20,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_21,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_22,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_23,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_24,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_25,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_26,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_27,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_28,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_29,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));

        connect(ui->label_30,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_31,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_32,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_33,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_34,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_35,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_36,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_37,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_38,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_39,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));

        connect(ui->label_40,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_41,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_42,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_43,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_44,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_45,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_46,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_47,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_48,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_49,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));

        connect(ui->label_50,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_51,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_52,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_53,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_54,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_55,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_56,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_57,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_58,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_59,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));

        connect(ui->label_60,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_61,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_62,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_63,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_64,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_65,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_66,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_67,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_68,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_69,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));

        connect(ui->label_70,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_71,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_72,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_73,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_74,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_75,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_76,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_77,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_78,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
        connect(ui->label_79,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));

        connect(ui->label_80,SIGNAL(clicked()),this,SLOT(myqlable_clicked()));
}

void chat_face::myqlable_clicked()
{
    qDebug()<<"myqlable is being clicked!!!";
    myQLabel *sendname=qobject_cast<myQLabel*>(sender());///获取被单击的我的myqlabel的对象的名称；
    QString beclicked_name=sendname->objectName();
    qDebug()<<beclicked_name;
    emit load_face(beclicked_name);/////   发送被单击后的对戏那个的控件的名称；
}

chat_face::~chat_face()
{
    delete ui;
}

//void chat_face::on_label_linkActivated(const QString &link)
//{
//    qDebug()<<"ppppppppppppppppppppppp";
//}
