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

    connect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(this, SIGNAL(BytesReady(QByteArray)), this, SLOT(writeToSocket(QByteArray)));

     qDebug() << "Socket Descriptor: " << _socketDescriptor;

     for (int i = 0; i < (_fileList.length() - 1); i++)
     {
         qDebug() << _fileList.at(i);

        QString s = QString("Files: %1").arg(_fileList.at(i));

        QByteArray tcpbytes;
        tcpbytes.append(s);
        qDebug() << "tcp bytes: " << tcpbytes;
        _tcpSocket->write(tcpbytes);
     }


     QString s = QString("Last: %1").arg(_fileList.back());
     QByteArray tcpbytes;
     tcpbytes.append(s);
     qDebug() << "tcp bytes: " << tcpbytes;
     if( _tcpSocket->waitForConnected() )
        _tcpSocket->write(tcpbytes);

     exec();

}

void ServerThread::readSocket()
{
    QByteArray data = _tcpSocket->readAll();
    qDebug() << data;
    int index = atoi(data.data());
    QFile file(_fileList.at(index));

    if (!file.open(QFile::ReadWrite))
    {
        this->exit();
        return;
    }

    QString s = QString("Size: %1").arg(file.size());
    QByteArray tcpbytes;

    tcpbytes.append(s);

    emit(BytesReady(tcpbytes));

}

void ServerThread::writeToSocket(QByteArray bytes)
{
      qDebug() << "Sending: " << bytes;
    _tcpSocket->write(bytes);
}
