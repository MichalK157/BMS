#ifndef Q_TOOLS_HEADER
#define Q_TOOLS_HEADER

#include "../build/ui_bms_api.h"
#include "protocol.h"
#include <QtWidgets/QLabel>
#include <fstream>
#include <iostream>
#include <string>

class Logger {
private:
  std::string filename;
  std::ofstream logFile;
  std::string getTimeStamp();

public:
  Logger(const std::string &fileName) : filename(fileName){};
  ~Logger();
  void init_logger();
  void log(const Battery *msg, Ui_BMS *ui);
};

void update_battery(Ui_BMS *ui, const Battery *msg, Logger *logger);

#endif