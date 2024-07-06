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
  void log(const MSG_TO_PC *msg);
};

void updateLabel(QLabel *label, std::string data);
void update_cells(Ui_BMS *ui, const MSG_TO_PC *msg, Logger *logger);
void update_battery(Ui_BMS *ui, const MSG_TO_PC *msg, Logger *logger);

#endif