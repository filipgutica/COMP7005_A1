#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#define DOWNLOAD_PORT 7575


#include <QDialog>
#include <QtNetwork>

namespace Ui {
class Downloader;
}

class Downloader : public QDialog
{
    Q_OBJECT

public:
    explicit Downloader(QWidget *parent = 0);
    ~Downloader();
    bool SetFileName(QString);
    bool SetBytesExpected(int);
    void StartDownloader();
    bool SetSocket(int);
    void SetProgress(int);

private slots:

    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void acceptConnection();

    void readSocket();

private:
    Ui::Downloader *ui;
    QTcpServer *_tcpServ;
    QTcpSocket *_sock;
    int _bytesReceived;
    int _bytesExpected;
    QFile *_file;
    QString _fName;

};

#endif // DOWNLOADER_H
