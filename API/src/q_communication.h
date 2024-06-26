#pragma once

#include "SerialPort.h"
#include <QThread>
#include <cstdint>
#include <stdbool.h>

class SerialReaderThread : public QThread {
  Q_OBJECT
private:
  SerialPort *serial;
  bool is_run;

public:
  explicit SerialReaderThread(QObject *parent = nullptr);
  ~SerialReaderThread();
  void run() override;
  void send(const uint8_t *data);
  void stop();

signals:
  void newData(const uint8_t *data);
};
