
#include "q_communication.h"
#include <iostream>


SerialReaderThread::SerialReaderThread(QObject *parent)
    : QThread(parent) 
{
    serial = new SerialPort("/dev/USART", B115200);
}

void SerialReaderThread::run() 
{
    char buffer[10];

    if (!serial->open()) {
        std::cerr << "Failed to open serial port!" << std::endl;
        is_run = false;
    }
    else
    {
        std::cout << "Start Read Task" << std::endl; 
        is_run = true;
    }

    while (is_run) {

        int bytesRead = serial->readData(buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) 
        {
        buffer[bytesRead] = '\0'; // Null-terminate the string
        std::cout << buffer << std::endl;
        emit newData(buffer);
        }
        else
        {
            this->msleep(50);
        }
        
    }
    serial->close();
}

void SerialReaderThread::send(const char *data)
{
    if (!serial->writeData(data, strlen(data))) {
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