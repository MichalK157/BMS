
#include "q_communication.h"
#include "SerialPort.h"
#include <iostream>


void SerialReaderThread::run() 
{
    SerialPort serial("/dev/ttyUSB0", B115200);
    uint8_t buffer[255];

    if (!serial.open()) {
        std::cerr << "Failed to open serial port!" << std::endl;
        is_run = false;
    }
    else
    {
        is_run = true;
    }

    while (is_run) {

        int bytesRead = serial.readData(buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the string
        emit newData(buffer);
    }
    }
    serial.close();
}