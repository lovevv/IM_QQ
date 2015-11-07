#ifndef MESSAGE_H
#define MESSAGE_H

#define MSGSIZE 2048

#include <QString>

struct _message_toser
{
	char username[20];
	char passwd[30];
	int flags;//1 means login,2 means register,3 means to turnto someone
	char sendtoname[20];
	char msg[MSGSIZE];
};


struct _message_touser
{
	char sendfrom[20];
	char msg[MSGSIZE];
	int mysocket;

};

struct _user
{
        char username[20];
        char passwd[20];
        int status;
//	int friendnum;
//	char *friend[50];
//    QString username;
//    QString passwd;
//    int status;
};

struct _identfi
{
	char username[20];
	int flags;//0 means promit,else means forbid
};



struct _name_tosock
{
	int connect;
	char username[20];
};

struct _msg_tolink
{
	char sendtoname[20];
	int connect;
};
#endif	
