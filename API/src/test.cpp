#include "SerialPort.h"
#include <iostream>
#include <cstring>

int main() {
    SerialPort serial("/dev/ttyUSB0", B115200);

    if (!serial.open()) {
        std::cerr << "Failed to open serial port!" << std::endl;
        return 1;
    }

    const char* dataToSend = "Hello, Serial Port!";
    if (!serial.writeData(dataToSend, strlen(dataToSend))) {
        std::cerr << "Failed to write data!" << std::endl;
    }

    char buffer[100];
    int bytesRead = serial.readData(buffer, sizeof(buffer) - 1);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the string
        std::cout << "Received: " << buffer << std::endl;
    }

    serial.close();
    return 0;
}