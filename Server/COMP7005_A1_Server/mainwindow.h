#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define DEFAULT_PORT 7005

#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void loadFiles();
    void updateFileList();

    void HandleClient(int);
    ~MainWindow();

private slots:
    void on_actionStart_Server_triggered();
    void acceptConnection();
    void handleDisconnect();

private:
    Ui::MainWindow *ui;
    QTcpServer *_tcpServ;
    QTcpSocket *_socket;
    QStringList _fileList;

};

#endif // MAINWINDOW_H
