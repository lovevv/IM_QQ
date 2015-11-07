#include "shotwindow.h"
#include "ui_shotwindow.h"

shotwindow::shotwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shotwindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(forclose()),this,SLOT(on_pushButton_3_clicked()));//进行显示
}

shotwindow::~shotwindow()
{
    delete ui;
}

void shotwindow::on_pushButton_clicked()
{
    if(ui->checkBox->isChecked())
    {
        this->hide();
        this->timer=new QTimer;
        QObject::connect(this->timer,SIGNAL(timeout()),SLOT(shotScreenshot()));
        this->timer->start(ui->spinBox->value()*1000);
    }
    else
    {
       qApp->beep();
    }
}

void shotwindow::on_pushButton_3_clicked()
{
    this->close();
}

void shotwindow::shotScreenshot()
{
//    this->pixmap=QPixmap::grabWindow(QApplication::desktop()->winId());
//        ui->label->setPixmap(this->pixmap.scaled(ui->label->size()));
//        this->show();
        //this->timer->stop();
    shot=new areashot();
    shot->show();
    this-> timer->stop();
    connect(shot,SIGNAL(fullshot(QPixmap*)),this,SLOT(deskshow(QPixmap*)));
}

void shotwindow::deskshow(QPixmap *deskmap)
{
    ui->label->setPixmap(deskmap->scaled(ui->label->size()));
    saveforshow=new QPixmap(*deskmap);
    this->show();
}

void shotwindow::on_pushButton_2_clicked()
{
      QFileDialog::Options options;
      QString selectedFilter;
      QString str = QDateTime().currentDateTime().toString("yyyyMMddHHmmss");
      QString fileName = str;
      fileName = QFileDialog::getSaveFileName(this,
                                              tr("保存图片"),
                                              fileName,
                                              tr("JPEG Files (*.jpg);;JPEG (*.jpg)"),
                                              &selectedFilter,
                                              options);
     saveforshow->save(fileName,"jpg");
     emit(forclose());//paochu xinhao jinxing guanbi dangqian de xianshi chuangkou
}
