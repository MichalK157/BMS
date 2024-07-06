#include "q_main_window.h"
#include "protocol.h"
#include "serialization.h"
#include <iostream>

Q_main_window::Q_main_window(QWidget *parent) : QMainWindow(parent) {
  serialReaderThread = new SerialReaderThread();
  logger = new Logger("log.csv");
  logger->init_logger();
  ui->setupUi(this);
  connect(serialReaderThread, &SerialReaderThread::newData, this,
          &Q_main_window::getdate);
  connect(ui->Connect, &QPushButton::released, this,
          &Q_main_window::connect_bms);
  connect(ui->Disconnect, &QPushButton::released, this,
          &Q_main_window::disconnect_bms);
  serialReaderThread->start();
}
Q_main_window::~Q_main_window() {
  serialReaderThread->stop();
  serialReaderThread->quit();
  serialReaderThread->wait();
  delete serialReaderThread;
  delete logger;
}

void Q_main_window::disconnect_bms() {
  MSG_TO_BMS msg;
  memset(&msg, 0, sizeof(MSG_TO_BMS));
  msg.id = MSG_ID_COMMUNICATION;
  msg.communication = Communication_Stop;
  uint8_t *buffer = bms_msg_serialization_to_buffer(&msg);
  if (buffer != NULL) {
    serialReaderThread->send(buffer);
  }
}

void Q_main_window::connect_bms() {
  MSG_TO_BMS msg;
  memset(&msg, 0, sizeof(MSG_TO_BMS));
  msg.id = MSG_ID_COMMUNICATION;
  msg.communication = Communication_Init;
  uint8_t *buffer = bms_msg_serialization_to_buffer(&msg);
  if (buffer != NULL) {
    serialReaderThread->send(buffer);
  }
}

void Q_main_window::getdate(const uint8_t *data) {

  MSG_TO_PC *msg = buffer_serialization_to_pc_msg(data);
  if (msg != NULL) {
    switch (msg->id) {
    case MSG_ID_CELLS: {
      update_cells(ui, msg, logger);
      break;
    }
    case MSG_ID_STATE: {
      break;
    }
    case MSG_ID_BATTERY: {
      update_battery(ui, msg, logger);
      break;
    }
    default: {
      break;
    }
    }
    delete msg;
  }
}
