#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <QUdpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void readSocket();

private slots:


    void on_send_clicked();

    void on_connect_clicked();

    void on_sendText_editingFinished();

    void on_disconnect_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *socket ;
    QHostAddress dstIP ;
    quint16 dstPort ;
    QHostAddress localIP ;
    quint16 localPort ;
    bool inConnection;
};

#endif // MAINWINDOW_H
