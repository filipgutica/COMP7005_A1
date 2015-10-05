#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionConnect_triggered();
    void ReadControlLine();

private:
    Ui::MainWindow *ui;
    QTcpSocket *_socket;
    QTcpServer *_tcpServ;
    QByteArray _fileList;
    int _totalFileSize;
    int _received;

    QString _ip;
    QString _port;
    QString _fileName;
    bool _fileListReceived;
    bool _fileTransferInitiated;

    void ConnectTCP(QString, QString);
};

#endif // MAINWINDOW_H
