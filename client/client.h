#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include "client_socket.h"
#include "mainframe.h"
#include "user_register.h"

namespace Ui {
    class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

public slots:
    void on_pushButton_clicked();
    void display_mainframe(QString name);
//    void new_register(QString username,QString passwd);

signals:
    void sendto_getfriendlist(QString name);

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Client *ui;
    client_socket *client1;
    Mainframe *mainframe;



};

#endif // CLIENT_H
