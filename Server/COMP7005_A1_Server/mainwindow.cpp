#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverthread.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _tcpServ = new QTcpServer(this);

    loadFiles();
    updateFileList();

    connect(_tcpServ, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFileList()
{
    //Add to the list view
    ui->listView->setModel(new QStringListModel(_fileList));
}

void MainWindow::acceptConnection()
{
    QTcpSocket *clientConnection = _tcpServ->nextPendingConnection();

    HandleClient(clientConnection->socketDescriptor());

}

void MainWindow::HandleClient(int socketDescriptor)
{
    ServerThread *thrd = new ServerThread(socketDescriptor, _fileList, this);

    connect(thrd, SIGNAL(finished()), thrd, SLOT(deleteLater()));

    thrd->start();
}


void MainWindow::handleDisconnect()
{

}

void MainWindow::loadFiles()
{
    QDirIterator dirIter("../Files", QDirIterator::Subdirectories);
    QString curFile;

    while (dirIter.hasNext())
    {
        dirIter.next();
        if (QFileInfo(dirIter.filePath()).isFile())
        {

            curFile = dirIter.filePath();
          //  qDebug() << curFile;
            _fileList.push_back(curFile);

        }
    }
}

void MainWindow::on_actionStart_Server_triggered()
{
    if(!_tcpServ->listen(QHostAddress::Any, DEFAULT_PORT))
    {
        QMessageBox::critical(this, tr("Server"),
                                     tr("Unable to start the server: %1.")
                                     .arg(_tcpServ->errorString()));
    }

}
