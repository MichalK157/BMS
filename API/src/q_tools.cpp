#include "q_tools.h"
#include "boost/lexical_cast.hpp"
// #include <bits/stdc++.h>
#include <array>
#include <charconv>
#include <ctime>
#include <iomanip>
#include <string>
#include <string_view>

using namespace std;
using boost::bad_lexical_cast;
using boost::lexical_cast;

static std::string trim_value(const int16_t value, const double percale, const uint16_t divider, const double offset,
                              const std::string suffix);
static double get_prescaler(QComboBox* comboBox_Resistance);
static void update_cells(Ui_BMS* ui, const Cells* msg, Logger* logger);
static void updateLabel(QLabel* label, std::string data);

void updateLabel(QLabel* label, std::string data)
{
    label->setText(QString(data.c_str()));
}

void update_cells(Ui_BMS* ui, const Cells* msg, Logger* logger)
{

    updateLabel(ui->c1_2, trim_value(msg->voltage[0], 0.38, 1000, 0.03, " V"));
    updateLabel(ui->c1_3, trim_value(msg->voltage[1], 0.38, 1000, 0.03, " V"));
    updateLabel(ui->c1_4, trim_value(msg->voltage[2], 0.38, 1000, 0.03, " V"));
    updateLabel(ui->c1_5, trim_value(msg->voltage[3], 0.38, 1000, 0.03, " V"));
    updateLabel(ui->c1_6, trim_value(msg->voltage[4], 0.38, 1000, 0.03, " V"));
}

void update_battery(Ui_BMS* ui, const Battery* msg, Logger* logger)
{

    update_cells(ui, &msg->cells, logger);

    updateLabel(ui->Label_Current, trim_value(msg->current, get_prescaler(ui->comboBox_Resistance), 1000, 0, " A"));
    if(msg->battery_status == Battery_Status_Charge)
    {
        ui->Label_Current->setStyleSheet("QLabel { background-color : green; color : black; }");
    }
    else if(msg->battery_status == Battery_Status_Discharge)
    {
        ui->Label_Current->setStyleSheet("QLabel { background-color : yellow; color : black; }");
    }
    else if(msg->battery_status == Battery_Status_Error)
    {
        ui->Label_Current->setStyleSheet("QLabel { background-color : red; color : black; }");
    }
    else
    {
        ui->Label_Current->setStyleSheet("QLabel { background-color : white; color : black; }");
    }
    logger->log(msg, ui);
    /*
      std::string str;
    str.append("Sys status: ");
    str.append(to_string(msg->status.sys_status));
    updateLabel(ui->Status_label, str.data());
    */
}

std::string Logger::Logger::getTimeStamp()
{
    std::time_t now = std::time(nullptr);
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %X", std::localtime(&now));
    return buf;
}

Logger::Logger::~Logger()
{
    if(logFile.is_open())
    {
        logFile.close();
    }
}

void Logger::Logger::init_logger()
{
    std::cout << "sizeof(MSG_TO_PC) : " << sizeof(MSG_TO_PC) << std::endl;
    std::cout << "sizeof(MSG_TO_BMS) : " << sizeof(MSG_TO_BMS) << std::endl;
    logFile.open(filename, std::ios_base::in | std::ios_base::app);
    if(!logFile.is_open())
    {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
    logFile << "Time_Stamp;Msg_Type;NOC;C1;C2;C3;C4;C5;VOLTAGE;CURRENT;TEMP;"
               "STATUS;LOAD;"
            << std::endl;
}

void Logger::log(const Battery* msg, Ui_BMS* ui)
{
    logFile << getTimeStamp() << ";";
    logFile << "MSG_ID_BATTERY" << ";";
    logFile << msg->cells.noc << ";";
    for(int i = 0; i < MAX_CELLS_NUMBER; i++)
    {
        logFile << trim_value(msg->cells.voltage[i], 0.38, 1000, 0.03, "") << ";";
    }
    logFile << trim_value(msg->voltage, 1.532, 1000, 0, "") << ";";
    logFile << trim_value(msg->current, get_prescaler(ui->comboBox_Resistance), 1000, 0, "") << ";";
    logFile << msg->temperature.temperature[0] << ";";
    logFile << msg->battery_status << ";";
    logFile << msg->load << std::endl;
}

static std::string trim_value(const int16_t value, const double percale, const uint16_t divider, const double offset,
                              const std::string suffix)
{
    std::array<char, 6> str;

    auto [prt, ex] = std::to_chars(str.data(), str.data() + str.size(),
                                   (double)(((value * percale) / divider) + offset), std::chars_format::fixed, 2);

    *prt = '\0';
    std::string sstr(str.data());
    sstr.append(suffix);
    return sstr;
}

static double get_prescaler(QComboBox* comboBox_Resistance)
{
    int index = comboBox_Resistance->currentIndex();
    double value = comboBox_Resistance->itemText(index).toDouble();
    return 0.01165 / value;
}