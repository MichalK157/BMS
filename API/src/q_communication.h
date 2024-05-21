#pragma once

#include <QThread>
#include <cstdint>
#include <stdbool.h>
#include "SerialPort.h"


class SerialReaderThread : public QThread {
    Q_OBJECT
private:
    SerialPort* serial;
    bool is_run;
public:
    explicit SerialReaderThread(QObject *parent = nullptr);
    ~SerialReaderThread();
    void run() override;
    void send(const char* data);
    void stop();

signals:
    void newData(const char* data);
};
