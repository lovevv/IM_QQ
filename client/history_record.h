#ifndef HISTORY_RECORD_H
#define HISTORY_RECORD_H

#include <QWidget>
#include <QDir>
#include<QFile>
#include<QDebug>
#include<QPalette>
#include<QPixmap>

namespace Ui {
    class history_record;
}

class history_record : public QWidget
{
    Q_OBJECT
public slots:
    void load_historyrecord(QString myname,QString sendname);///xianshi xiaoxi dejilu
public:
    explicit history_record(QWidget *parent = 0);
    ~history_record();

private slots:
    void on_pushButton_clicked();

private:
    Ui::history_record *ui;
};

#endif // HISTORY_RECORD_H
