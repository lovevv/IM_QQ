#ifndef CONNECT_IMQ_H
#define CONNECT_IMQ_H
#include <QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>

//用来链接数据库，在验证登录时候的用户密码和用户名


static bool createconnect()
{
         QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("IMQ");
        db.setUserName("root");
        db.setPassword("");
        bool ok=db.open();
       // if(!ok)
       //  QSqlDatabase::lastError();
        return ok;
}
#endif // CONNECT_IMQ_H
