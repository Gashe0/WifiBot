#include "mainwindow.h"
#include "connexion.h"
#include "ui_mainwindow.h"


Connexion* s = new Connexion(0);

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

void MainWindow::on_pushButton_clicked()
{
     s->setAdresse(ui->textEdit->toPlainText());
     s->setPort(ui->textEdit_2->toPlainText());
     s->doConnect();
}

void MainWindow::on_pushButton_2_clicked()
{
    s->disconnected();
}
