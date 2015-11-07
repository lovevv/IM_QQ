#ifndef SHOTWINDOW_H
#define SHOTWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QKeyEvent>
#include"areashot.h"

namespace Ui {
    class shotwindow;
}

class shotwindow : public QWidget
{
    Q_OBJECT

public:
    explicit shotwindow(QWidget *parent = 0);
    ~shotwindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();
    void shotScreenshot();
    void deskshow(QPixmap *deskmap);
    void on_pushButton_2_clicked();
signals:
    void forclose();

private:
    Ui::shotwindow *ui;
    QTimer *timer;
    QPixmap pixmap;
    areashot *shot;
    QPixmap *saveforshow;//备份下来用于显示，不影响分辨率
};

#endif // SHOTWINDOW_H
