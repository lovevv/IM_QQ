#-------------------------------------------------
#
# Project created by QtCreator 2012-05-16T10:53:22
#
#-------------------------------------------------

QT       += core gui
QT +=network
QT +=sql
QT += phonon

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        client.cpp \
    client_socket.cpp \
    mainframe.cpp \
    chat.cpp \
    chat_face.cpp \
    myQlable.cpp \
    user_register.cpp \
    history_record.cpp \
    receive_file.cpp \
    shotwindow.cpp \
    areashot.cpp \
    myScreen.cpp

HEADERS  += client.h \
    client_socket.h \
    mainframe.h \
    chat.h \
    message.h \
    chat_face.h \
    myQlable.h \
    user_register.h \
    history_record.h \
    receive_file.h \
    shotwindow.h \
    areashot.h \
    myScreen.h

FORMS    += client.ui \
    mainframe.ui \
    chat.ui \
    chat_face.ui \
    user_register.ui \
    history_record.ui \
    receive_file.ui \
    shotwindow.ui \
    areashot.ui

RESOURCES += \
    image_resouce.qrc


























































