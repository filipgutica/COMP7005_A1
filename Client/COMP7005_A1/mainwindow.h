#ifndef MAINWINDOW_H
#define MAINWINDOW_H



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
    ~MainWindow();

private slots:
    void on_actionConnect_triggered();
    void ReadControlLine();

    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QTcpSocket *_socket;

    QString _ip;
    QString _port;
    QString _fileName;
    bool _fileListReceived;
    bool _fileTransferInitiated;
    QStringList *_fileList;

    void ConnectTCP(QString, QString);
    void UpdateFilelist();
    void WriteTCP(QByteArray);
};

#endif // MAINWINDOW_H
