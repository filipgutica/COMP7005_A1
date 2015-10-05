#ifndef DOWNLOADER_H
#define DOWNLOADER_H

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

private:
    Ui::Downloader *ui;
    QTcpServer *_tcpServ;
    QTcpSocket *_sock;
};

#endif // DOWNLOADER_H
