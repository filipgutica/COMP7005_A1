#include "downloader.h"
#include "ui_downloader.h"

Downloader::Downloader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Downloader)
{
    ui->setupUi(this);
    _tcpServ = new QTcpServer(this);
    _sock = NULL;
    _bytesReceived = 0;
    _bytesExpected = 0;

}

Downloader::~Downloader()
{
    delete ui;
}

bool Downloader::SetFileName(QString s)
{
    _fName = s;

    _file = new QFile(_fName);

    qDebug() << "Creating file: " << _file->fileName();

    if (!_file->open(QFile::WriteOnly))
    {
        qDebug() << "File open fail " << _file->errorString();
        return false;
    }

    return true;
}

bool Downloader::SetBytesExpected(int n)
{
    if (n > 0)
    {
        _bytesExpected = n;
        return true;
    }
    else
        return false;
}

void Downloader::StartDownloader()
{
    ui->btnOK->setEnabled(false);
    ui->btnCancel->setEnabled(true);

    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(_bytesExpected);

    _tcpServ->listen(QHostAddress::Any, DOWNLOAD_PORT);
    connect(_tcpServ, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    qDebug() << "Downloader listening";

    while (!_tcpServ->isListening() && !_tcpServ->listen())
    {
        qDebug() << "I'm not listening";
        return;
    }
}

void Downloader::acceptConnection()
{
    _sock = _tcpServ->nextPendingConnection();
    qDebug() << "Downloader Accepted connection: " << _sock->socketDescriptor();
    connect(_sock, SIGNAL(readyRead()), this, SLOT(readSocket()));
    _tcpServ->close();
}

bool Downloader::SetSocket(int socketDescriptor)
{
    _sock->setSocketDescriptor(socketDescriptor);

    return true;
}

void Downloader::readSocket()
{
    int bytes = (int)_sock->bytesAvailable();
    _bytesReceived = bytes;
    _file->write(_sock->readAll(), bytes);
    ui->progressBar->setValue(_bytesReceived);

    if (_bytesReceived == _bytesExpected)
    {
        _bytesReceived = 0;
        _file->close();
        _sock->close();
        ui->btnOK->setEnabled(true);
        ui->btnCancel->setEnabled(false);
    }
}

void Downloader::on_btnOK_clicked()
{
      this->accept();
}

void Downloader::on_btnCancel_clicked()
{
    _bytesReceived = 0;

    if (_file)
    {
        _file->deleteLater();
        _file->close();
    }

    if (_sock)
    {
        _sock->close();
    }

    if (_tcpServ)
    {
        _tcpServ->close();
    }

    this->close();
}

void Downloader::SetProgress(int prog)
{
    ui->progressBar->setValue(prog);
}
