#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Chatty");
    socket = new QUdpSocket(this);
    inConnection=false;
    ui->display->setEnabled(false);

}

void MainWindow::readSocket()
{
      if(inConnection==false) return;
      while(socket->hasPendingDatagrams())
      {
          QByteArray data;
          data.resize(socket->pendingDatagramSize());
          QHostAddress sender;
          quint16 senderPort;

          socket->readDatagram(data.data(), data.size(),&sender, &senderPort);
          QString rcvData = data.data();

          ui->display->append("<font color=red> Him:"+ rcvData.toUtf8() +"</font> " );


      }
}



MainWindow::~MainWindow()
{
    delete ui;
    socket->close();
}


void MainWindow::on_send_clicked()
{
   if(inConnection==false)
   {
       QMessageBox msg;
       msg.setText("You must start a conversation first");
       msg.exec();
       return;
   }
    QString str = ui->sendText->text();
    if(str == "") return;
    ui->display->append("<font color=green>Me: " + str.toUtf8() + "</font>");

    ui->sendText->setText("");
    socket->writeDatagram(str.toUtf8().data(),QHostAddress(dstIP),dstPort);


}

void MainWindow::on_connect_clicked()
{
    if(inConnection==true) return;
    inConnection=true;
    localIP = QHostAddress(ui->localIP->text());
    localPort = ui->localPort->text().toShort() ;


    dstIP = QHostAddress(ui->remoteIP->text());
    dstPort = ui->remotePort->text().toShort() ;
    socket->bind(QHostAddress(localIP) , localPort);
    connect(socket, SIGNAL(readyRead()),this, SLOT(readSocket()));


}

void MainWindow::on_sendText_editingFinished()
{
    on_send_clicked();
}

void MainWindow::on_disconnect_clicked()
{
    ui->display->clear();
    inConnection=false;
    QMessageBox msg;
    msg.setText("Connection Closed, GoodBye");
    msg.exec();
}
