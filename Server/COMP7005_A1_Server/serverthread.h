#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#define DOWNLOAD_PORT 7575

#include <QThread>
#include <QtNetwork>

class ServerThread : public QThread
{
    Q_OBJECT
public:
    ServerThread(int, QStringList, QObject *);
     void run();

signals:
     void BytesReady(QByteArray);

private slots:
     void readSocket();
     void ProcessSocketError(QAbstractSocket::SocketError);

private:
     int _socketDescriptor;
     QStringList _fileList;
     QTcpSocket *_tcpSocket;
};

#endif // SERVERTHREAD_H
