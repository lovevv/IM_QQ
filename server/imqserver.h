#ifndef IMQSERVER_H
#define IMQSERVER_H

#include <QWidget>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QTcpServer>
#include <IMQ_server.h>

namespace Ui {
    class IMQServer;
}

class IMQServer : public QWidget
{
    Q_OBJECT

public:
    explicit IMQServer(QWidget *parent = 0);
    ~IMQServer();

private slots:
    void on_server_link_clicked();

private:
    Ui::IMQServer *ui;
    IMQ_server *server;//   再筐子中定义了一个server；
};

#endif // IMQSERVER_H
