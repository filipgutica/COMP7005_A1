#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


QString Dialog::getIP()
{
    return ui->txtIP->text();
}

QString Dialog::getPort()
{
    return ui->txtPort->text();
}
