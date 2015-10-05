#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    Dialog *dlg = new Dialog();

    if (dlg->exec() == QDialog::Accepted)
    {
        _ip = dlg->getIP();
        _port = dlg->getPort();
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
}
