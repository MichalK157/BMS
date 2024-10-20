#pragma once

#ifndef Q_MAIN_WINDOW_H
#define Q_MAIN_WINDOW_H

#include "../build/ui_bms_api.h"
#include "q_communication.h"
#include "q_tools.h"
#include <QMainWindow>
#include <QThread>

using namespace Ui;

class Q_main_window : public QMainWindow
{
    Q_OBJECT

  public:
    explicit Q_main_window(QWidget* parent = nullptr);
    ~Q_main_window();

  private:
    Ui_BMS* ui;
    Logger* logger;
    bool charge_press;
    SerialReaderThread* serialReaderThread;
    void connect_bms();
    void disconnect_bms();
    void charge();

  private slots:
    void getdate(const uint8_t* data);
};

#endif