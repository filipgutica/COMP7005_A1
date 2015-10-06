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
    void AppendToLog(QString);
    void HandleClient(int);
    ~MainWindow();

signals:
    void valueChanged(QString);

private slots:
    void on_actionStart_Server_triggered();
    void acceptConnection();

private:
    Ui::MainWindow *ui;
    QTcpServer *_tcpServ;
    QTcpSocket *_socket;
    QStringList _fileList;

};

#endif // MAINWINDOW_H
