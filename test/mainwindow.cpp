#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QNetworkAccessManager *man = new QNetworkAccessManager(this);
    connect(man, &QNetworkAccessManager::finished, this, &MainWindow::downloadFinished);
    const QUrl url = QUrl(myUrl);
    QNetworkRequest request(url);
    man->get(request);

}

void MainWindow::downloadFinished(QNetworkReply *reply)
{
    QPixmap pix;
    pix.loadFromData(reply->readAll());
    ui->label->setPixmap(pix);

}
