#include "q_tools.h"
#include "boost/lexical_cast.hpp"
//#include <bits/stdc++.h>
#include <array>
#include <charconv>
#include <ctime>
#include <iomanip>
#include <string>
#include <string_view>

using namespace std;
using boost::bad_lexical_cast;
using boost::lexical_cast;

void updateLabel(QLabel *label, std::string data) {
  label->setText(QString(data.c_str()));
}

static std::string trim_value(const int16_t value, const double percale,
                              const uint16_t divider, const double offset,
                              const std::string suffix);
static double get_percale(QComboBox *comboBox_Resistance);

void update_cells(Ui_BMS *ui, const MSG_TO_PC *msg, Logger *logger) {

  updateLabel(ui->c1_2,
              trim_value(msg->cells.voltage[0], 0.38, 1000, 0.03, " V"));
  updateLabel(ui->c1_3,
              trim_value(msg->cells.voltage[1], 0.38, 1000, 0.03, " V"));
  updateLabel(ui->c1_4,
              trim_value(msg->cells.voltage[2], 0.38, 1000, 0.03, " V"));
  updateLabel(ui->c1_5,
              trim_value(msg->cells.voltage[3], 0.38, 1000, 0.03, " V"));
  updateLabel(ui->c1_6,
              trim_value(msg->cells.voltage[4], 0.38, 1000, 0.03, " V"));
  logger->log(msg, ui);
}

void update_battery(Ui_BMS *ui, const MSG_TO_PC *msg, Logger *logger) {

  updateLabel(ui->Label_Current,
              trim_value(msg->battery.current,
                         get_percale(ui->comboBox_Resistance), 1000, 0, " A"));
  if (msg->battery.load == LOAD_detect) {
    ui->Label_Current->setStyleSheet(
        "QLabel { background-color : green; color : black; }");
  } else {
    ui->Label_Current->setStyleSheet(
        "QLabel { background-color : red; color : black; }");
  }
  logger->log(msg, ui);
}

void update_status(Ui_BMS *ui, const MSG_TO_PC *msg, Logger *logger) {
  std::string str;
  str.append("Sys status: ");
  str.append(to_string(msg->status.sys_status));
  updateLabel(ui->Status_label, str.data());
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

void Logger::log(const MSG_TO_PC *msg, Ui_BMS *ui) {
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
    logFile << trim_value(msg->battery.voltage, 1.532, 1000, 0, "") << ";";
    logFile << trim_value(msg->battery.current,
                          get_percale(ui->comboBox_Resistance), 1000, 0, "")
            << ";";
    logFile << msg->battery.temperature.temperature[0] << ";";
    logFile << msg->battery.load << ";" << std::endl;
    break;
  }
  case MSG_ID_CELLS: {
    logFile << "MSG_ID_CELLS"
            << ";";
    logFile << msg->cells.noc << ";";
    for (int i = 0; i < MAX_CELLS_NUMBER; i++) {
      logFile << trim_value(msg->cells.voltage[i], 0.38, 1000, 0.03, "") << ";";
    }
    logFile << std::endl;
    break;
  }
  default: {
    break;
  }
  }
}

static std::string trim_value(const int16_t value, const double percale,
                              const uint16_t divider, const double offset,
                              const std::string suffix) {
  std::array<char, 5> str;

  auto [prt, ex] =
      std::to_chars(str.data(), str.data() + str.size(),
                    (double)(((value * percale) / divider) + offset),
                    std::chars_format::fixed, 2);

  std::string sstr(str.data());
  sstr.append(suffix);
  return sstr;
}

static double get_percale(QComboBox *comboBox_Resistance) {
  double a = -168.8;
  double b = 2.535;
  int index = comboBox_Resistance->currentIndex();
  double value = comboBox_Resistance->itemText(index).toDouble();
  std::cout << a * value + b << std::endl;
  return a * value + b;
}