#include "q_tools.h"
#include "boost/lexical_cast.hpp"
//#include <bits/stdc++.h>
#include <ctime>
#include <string>

using namespace std;
using boost::bad_lexical_cast;
using boost::lexical_cast;

void updateLabel(QLabel *label, std::string data) {
  label->setText(QString(data.c_str()));
}

void update_cells(Ui_BMS *ui, const MSG_TO_PC *msg, Logger *logger) {
  updateLabel(ui->c1_2, lexical_cast<string>(
                            ((msg->cells.voltage[0] * 0.38) + 0.3) / 1000));
  updateLabel(ui->c1_3, lexical_cast<string>(
                            ((msg->cells.voltage[1] * 0.38) + 0.3) / 1000));
  updateLabel(ui->c1_4, lexical_cast<string>(
                            ((msg->cells.voltage[2] * 0.38) + 0.3) / 1000));
  updateLabel(ui->c1_5, lexical_cast<string>(
                            ((msg->cells.voltage[3] * 0.38) + 0.3) / 1000));
  updateLabel(ui->c1_6, lexical_cast<string>(
                            ((msg->cells.voltage[4] * 0.38) + 0.3) / 1000));
  logger->log(msg);
}

void update_battery(Ui_BMS *ui, const MSG_TO_PC *msg, Logger *logger) {
  updateLabel(
      ui->Label_Current,
      lexical_cast<string>(((msg->battery.current * 0.38) + 0.3) / 1000));
  if (msg->battery.load == LOAD_detect) {
    ui->Label_Current->setStyleSheet(
        "QLabel { background-color : green; color : black; }");
  } else {
    ui->Label_Current->setStyleSheet(
        "QLabel { background-color : red; color : black; }");
  }
}

std::string Logger::Logger::getTimeStamp() {
  std::time_t now = std::time(nullptr);
  char buf[80];
  std::strftime(buf, sizeof(buf), "%Y-%m-%d %X", std::localtime(&now));
  return buf;
}

Logger::Logger::~Logger() {
  if (logFile.is_open()) {
    logFile.close();
  }
}

void Logger::Logger::init_logger() {
  logFile.open(filename, std::ios_base::in | std::ios_base::app);
  if (!logFile.is_open()) {
    std::cerr << "Failed to open log file: " << filename << std::endl;
  }
  logFile << "Time_Stamp;Msg_Type;NOC;C1;C2;C3;C4;C5;VOLTAGE;CURRENT;TEMP;LOAD;"
             "SYS_STATUS;PACK_CONFIG;SYS_CTRL_1;SYS_CTRL_2;PROTECT_1;PROTECT_2;"
             "PROTECT_3"
          << std::endl;
}

void Logger::log(const MSG_TO_PC *msg) {
  logFile << getTimeStamp() << ";";
  switch (msg->id) {
  case MSG_ID_STATE: {
    logFile << "MSG_ID_STATE"
            << ";";
    for (int i = 0; i < 10; i++) {
      logFile << ";";
    }
    logFile << msg->status.sys_status << ";";
    logFile << msg->status.cellbal_1 << ";";
    logFile << msg->status.sys_ctrl_1 << ";";
    logFile << msg->status.sys_ctrl_2 << ";";
    logFile << msg->status.protect1 << ";";
    logFile << msg->status.protect2 << ";";
    logFile << msg->status.protect3 << ";" << std::endl;
    break;
  }
  case MSG_ID_BATTERY: {
    logFile << "MSG_ID_BATTERY"
            << ";";
    for (int i = 0; i < 6; i++) {
      logFile << ";";
    }
    logFile << msg->battery.voltage << ";";
    logFile << msg->battery.current << ";";
    logFile << msg->battery.temperature.temperature[0] << ";";
    logFile << msg->battery.load << ";" << std::endl;
    break;
  }
  case MSG_ID_CELLS: {
    logFile << "MSG_ID_CELLS"
            << ";";
    logFile << msg->cells.noc << ";";
    for (int i = 0; i < MAX_CELLS_NUMBER; i++) {
      logFile << msg->cells.voltage[i] << ";";
    }
    logFile << std::endl;
    break;
  }
  default: {
    break;
  }
  }
}
