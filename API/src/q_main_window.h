#ifndef Q_MAIN_WINDOW_H
#define Q_MAIN_WINDOW_H

#include <QMainWindow>
#include <QThread>
#include "../build/ui_bms_api.h"
#include "q_communication.h"

using namespace Ui;

class Q_main_window : public QMainWindow
{
    Q_OBJECT
private:
    Ui_BMS ui;
    SerialReaderThread *serialReaderThread;
public:
    Q_main_window(QWidget *parent = nullptr);
    ~Q_main_window();
private slots:
    void getdata(const uint8_t* data);
};



#endif