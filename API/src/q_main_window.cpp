#include "q_main_window.h"
#include "protocol.h"
#include <QDebug>

Q_main_window::Q_main_window(QWidget *parent) : QMainWindow(parent)
    {
        serialReaderThread = new SerialReaderThread();
        ui->setupUi(this);
        connect(serialReaderThread, &SerialReaderThread::newData, this, &Q_main_window::getdate);
        connect(ui->Confirm, &QPushButton::released, this, &Q_main_window::send);
        serialReaderThread->start();
    }
Q_main_window::~Q_main_window() {
    serialReaderThread->stop();
    serialReaderThread->quit();
    serialReaderThread->wait();
    delete serialReaderThread;
}

void Q_main_window::send()
{
    serialReaderThread->send("testing\0");
    ui->c1_2->setText("1.0");
}

void Q_main_window::getdate(const char* data) {
    qDebug() << "New data received: " << data;
}
