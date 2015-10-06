#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "downloader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _fileList = new QStringList();
}

MainWindow::~MainWindow()
{
    delete _fileList;
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    Dialog *dlg = new Dialog();

    if (dlg->exec() == QDialog::Accepted)
    {
        _ip = dlg->getIP();
        _port = dlg->getPort();

        ConnectTCP(_ip, _port);
    }

}

//Private
void MainWindow::ConnectTCP(QString ip, QString port)
{
    _socket = new QTcpSocket(this);
    connect ( _socket, SIGNAL(readyRead()), SLOT(ReadControlLine()));

    _socket->connectToHost(ip, port.toInt());
}


void MainWindow::ReadControlLine()
{
    QByteArray data = _socket->readAll();

    qDebug() << data;

    QRegExp rxAvailableFiles("Files: ");
    QRegExp rxLastFile("Last: ");
    QRegExp rxRequestedFileSize("Size: ");

    if (rxAvailableFiles.indexIn(data.data()) != -1)
    {
        char *tok = strtok(data.data(), ":");
        tok = strtok(NULL, ":");
        _fileList->push_back(QString::fromUtf8(tok));
    }

    if (rxLastFile.indexIn(data.data()) != -1)
    {
        char *tok = strtok(data.data(), ":");
        tok = strtok(NULL, ":");
        _fileList->push_back(QString::fromUtf8(tok));

        UpdateFilelist();
    }

    if (rxRequestedFileSize.indexIn(data.data()) != -1)
    {
        char *tok = strtok(data.data(), ":");
        tok = strtok(NULL, ":");
        int fileSize = atoi(tok);

        Downloader dl;

        if (dl.SetFileName(_fileName) &&
            dl.SetBytesExpected(fileSize))
        {
            dl.StartDownloader();
            dl.exec();
        }
    }


}

void MainWindow::WriteTCP(QByteArray data)
{
    if( _socket->waitForConnected() ) {
        _socket->write( data );
    }
}

void MainWindow::UpdateFilelist()
{
    ui->listView->setModel(new QStringListModel(*_fileList));
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    _fileName = index.data().toString();
    _fileName = _fileName.split("/").back();
    QString s = QString("%1").arg(index.row());
    QByteArray tcpBytes;
    tcpBytes.append(s);
    WriteTCP(tcpBytes);

}
