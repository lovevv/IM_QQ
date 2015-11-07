#-------------------------------------------------
#
# Project created by QtCreator 2012-05-15T16:50:29
#
#-------------------------------------------------
#z注意再写一些关于网络的使用的时候你需要添加一个网络的服务
QT       += core gui
QT += network
QT +=sql
TARGET = testserver
TEMPLATE = app


SOURCES += main.cpp\
        imqserver.cpp \
    IMQ_server.cpp \
    Tcpsocket_client.cpp

HEADERS  += imqserver.h \
    IMQ_server.h \
    message.h \
    Tcpsocket_client.h

FORMS    += imqserver.ui



























