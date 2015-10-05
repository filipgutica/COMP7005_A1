#ifndef CLIENT
#define CLIENT

#define IP_LEN 16
#define BUFFSIZE 1024

#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <QString>
#include <QDebug>
#include <QRegExp>

void ConnectToServer(int port, char* ip, void *app);
void CloseConnection();
void SendMessage(const char*, int);
void* readThrd(void *param);

#endif // CLIENT

