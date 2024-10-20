#include "q_main_window.h"
#include "protocol.h"
#include "serialization.h"
#include <iostream>

Q_main_window::Q_main_window(QWidget* parent) : QMainWindow(parent)
{
    serialReaderThread = new SerialReaderThread();
    logger = new Logger("log.csv");
    logger->init_logger();
    ui->setupUi(this);
    charge_press = false;
    connect(serialReaderThread, &SerialReaderThread::newData, this, &Q_main_window::getdate);
    connect(ui->Connect, &QPushButton::released, this, &Q_main_window::connect_bms);
    connect(ui->Disconnect, &QPushButton::released, this, &Q_main_window::disconnect_bms);
    connect(ui->charge, &QPushButton::released, this, &Q_main_window::charge);
    serialReaderThread->start();
}
Q_main_window::~Q_main_window()
{
    serialReaderThread->stop();
    serialReaderThread->quit();
    serialReaderThread->wait();
    delete serialReaderThread;
    delete logger;
}

void Q_main_window::disconnect_bms()
{
    MSG_TO_BMS msg;
    memset(&msg, 0, sizeof(MSG_TO_BMS));
    msg.id = MSG_ID_COMMUNICATION;
    msg.communication = Communication_Stop;
    uint8_t* buffer = bms_msg_serialization_to_buffer(&msg);
    if(buffer != NULL)
    {
        serialReaderThread->send(buffer);
    }
    free(buffer);
}

void Q_main_window::charge()
{
    MSG_TO_BMS msg;
    msg.id = MSG_ID_SET;
    if(charge_press)
    {
        charge_press = false;
        ui->charge->setText(QString("unload"));
        msg.set_msg.name = Set_Msg_Name_ctrl2;
        msg.set_msg.reg_value = 0x02;
    }
    else
    {
        charge_press = true;
        ui->charge->setText(QString("charging"));
        msg.set_msg.name = Set_Msg_Name_ctrl2;
        msg.set_msg.reg_value = 0x01;
    }
}

void Q_main_window::connect_bms()
{
    MSG_TO_BMS msg;
    memset(&msg, 0, sizeof(MSG_TO_BMS));
    msg.id = MSG_ID_COMMUNICATION;
    msg.communication = Communication_Init;
    uint8_t* buffer = bms_msg_serialization_to_buffer(&msg);
    if(buffer != NULL)
    {
        serialReaderThread->send(buffer);
    }
    free(buffer);
}

void Q_main_window::getdate(const uint8_t* data)
{

    MSG_TO_PC* msg = buffer_serialization_to_pc_msg(data);
    if(msg != NULL)
    {
        switch(msg->id)
        {
            case MSG_ID_BATTERY:
            {
                update_battery(ui, &msg->battery, logger);
                break;
            }
            default:
            {
                break;
            }
        }
        delete msg;
    }
}
