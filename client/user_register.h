#ifndef USER_REGISTER_H
#define USER_REGISTER_H

#include <QDialog>
#include <QPalette>
#include "client_socket.h"

namespace Ui {
    class user_register;
}

class user_register : public QDialog
{
    Q_OBJECT

public:
    explicit user_register(QWidget *parent = 0);
    ~user_register();
signals:
 //   void new_register(QString usename,QString passwd);

public slots:
    void on_u_register_clicked();
    void showrgs_result(int isok);
    void on_r_cancel_clicked();

private:
    Ui::user_register *ui;
    client_socket  *rsg_socke;
};

#endif // USER_REGISTER_H
