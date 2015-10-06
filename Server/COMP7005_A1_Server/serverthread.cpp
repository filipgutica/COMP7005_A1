#include "serverthread.h"

ServerThread::ServerThread(int socketDescriptor, QStringList fileList, QObject *parent)
    : QThread(parent), _socketDescriptor(socketDescriptor), _fileList(fileList)
{

}

void ServerThread::run()
{
     _tcpSocket = new QTcpSocket();

    if (!_tcpSocket->setSocketDescriptor(_socketDescriptor))
    {
        return;
    }

    connect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(readSocket()), Qt::DirectConnection);


     qDebug() << "Socket Descriptor: " << _socketDescriptor;

     QString s = "Files: ";
     QByteArray tcpbytes;
     for (int i = 0; i < (_fileList.length()); i++)
     {
         qDebug() << _fileList.at(i);

        s.append(_fileList.at(i));

        tcpbytes.append(s);

     }
     qDebug() << "tcp bytes: " << tcpbytes;
     _tcpSocket->write(tcpbytes);

  /*   QString s = QString("Last: %1").arg(_fileList.back());
     QByteArray tcpbytes;
     tcpbytes.append(s);
     qDebug() << "tcp bytes: " << tcpbytes;
     if( _tcpSocket->waitForConnected() )
        _tcpSocket->write(tcpbytes);*/

     exec();

}

void ServerThread::readSocket()
{
    QByteArray data = _tcpSocket->readAll();
    QRegExp rxIndex("Index: ");
    QRegExp rxFileName("FileName: ");
    QRegExp rxFileSize("Size: ");

    qDebug() << "Server received: " << data;
    if (rxIndex.indexIn(data.data()) != -1)
    {
        char *tok = strtok(data.data(), ":");
        tok = strtok(NULL, ":");

        int index = atoi(tok);
        QFile file(_fileList.at(index));

        if (!file.open(QFile::ReadWrite))
        {
            this->exit();
            return;
        }

        QString s = QString("Size: %1").arg(file.size());
        QByteArray tcpbytes;

        tcpbytes.append(s);
        _tcpSocket->write(tcpbytes);
        _downloadSocket = new QTcpSocket();

        connect(_downloadSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ProcessSocketError(QAbstractSocket::SocketError)), Qt::DirectConnection);

       _downloadSocket->connectToHost("localhost", DOWNLOAD_PORT);

        while(!file.atEnd())
        {
            _downloadSocket->write(file.readAll());
        }

        _downloadSocket->close();
        _downloadSocket->deleteLater();
    }

}

void ServerThread::ProcessSocketError(QAbstractSocket::SocketError err)
{
    qDebug() << err;
}

