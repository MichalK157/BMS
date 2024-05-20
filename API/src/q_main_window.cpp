#include "q_main_window.h"
#include <QDebug>

Q_main_window::Q_main_window(QWidget *parent) : QMainWindow(parent), serialReaderThread(new SerialReaderThread) {
    ui.setupUi(this);
    connect(serialReaderThread, &SerialReaderThread::newData, this, &Q_main_window::getdata);
    serialReaderThread->start();
}

Q_main_window::~Q_main_window() {
    serialReaderThread->quit();
    serialReaderThread->wait();
    delete serialReaderThread;
}

void Q_main_window::getdata(const uint8_t* data) {
    // Obsługa nowych danych
    qDebug() << "New data received: " << data;
}
