#include "client.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

MainWindow *mainWindow;

int clientSocket;

void ConnectToServer(int port, char *ip, void *app)
{
    QString strInfo;
    struct hostent	*hostPtr;
    struct sockaddr_in serv_addr;
    char **pptr;
    char serverAddress[IP_LEN];
    pthread_t threadRead;

    mainWindow = (MainWindow*) app;


    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        qDebug() << "Cannot create socket";
        return;
    }

    qDebug() << "Connecting to ip: " << ip << " Port: " << port;


    bzero((char *)&serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if ((hostPtr = gethostbyname(ip)) == NULL)
    {
        qDebug() << "Unknown server address";
        return;
    }

    bcopy(hostPtr->h_addr, (char *)&serv_addr.sin_addr, hostPtr->h_length);

    if (connect (clientSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("connect");
        return;
    }


    qDebug() << "Connected: Server Name: " << hostPtr->h_name;

    strInfo = QString("Connected to chatroom server: %1")
            .arg(hostPtr->h_name);
    //mainWindow->appendMessage(strInfo);

    pthread_create (&threadRead, NULL, readThrd, (void*)1);
    qDebug() << "Pthread created";

}

void* readThrd(void *param)
{
    char *bp, buf[BUFFSIZE];
    int bytes_to_read, n;
    char *tok;
    tok = (char*)malloc(BUFFSIZE);

    QRegExp rxFileList("add: *");
    QRegExp rxFileDownload("remove: *");
    QRegExp rxMsg("usr: *");

    QString str;

    while(true)
    {
        bp = buf;
        bytes_to_read = BUFFSIZE;
        n = recv(clientSocket, bp, bytes_to_read, 0);
    }
}

void SendMessage(const char* msg, int size)
{
    send (clientSocket, msg, size, 0);
}

void CloseConnection()
{
    close(clientSocket);
}
