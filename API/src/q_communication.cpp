
#include "q_communication.h"
#include "protocol.h"
#include <iostream>

SerialReaderThread::SerialReaderThread(QObject* parent) : QThread(parent)
{
    serial = new SerialPort("/dev/USART", B115200);
}

void SerialReaderThread::run()
{
    uint8_t buffer[256];

    if(!serial->open())
    {
        std::cerr << "Failed to open serial port!" << std::endl;
        is_run = false;
    }
    else
    {
        std::cout << "Start Read Task" << std::endl;
        is_run = true;
    }

    while(is_run)
    {

        int bytesRead = serial->readData(buffer, sizeof(MSG_TO_PC));
        if(bytesRead > 0)
        {
            /*
            for (int i = 0; i < sizeof(MSG_TO_PC); i++) {
              std::cout << std::hex << (int)buffer[i];
            }
            std::cout << std::endl;
            */
            emit newData(buffer);
        }
        else
        {
            this->msleep(50);
        }
    }
    serial->close();
}

void SerialReaderThread::send(const uint8_t* data)
{
    if(!serial->writeData(data, sizeof(MSG_TO_BMS)))
    {
        std::cerr << "Failed to write data!" << std::endl;
    }
}

void SerialReaderThread::stop()
{
    this->is_run = false;
}

SerialReaderThread::~SerialReaderThread()
{
    is_run = false;
    serial->close();
    delete serial;
}