#include "SerialPort.h"
#include <cstring>
#include <iostream>

int main() {
  SerialPort serial("/dev/ttyUSB0", B115200);

  if (!serial.open()) {
    std::cerr << "Failed to open serial port!" << std::endl;
    return 1;
  }

  const uint8_t *dataToSend = (uint8_t *)"Hello, Serial Port!";
  if (!serial.writeData(dataToSend, 100)) {
    std::cerr << "Failed to write data!" << std::endl;
  }

  uint8_t buffer[100];
  int bytesRead = serial.readData(buffer, sizeof(buffer) - 1);
  if (bytesRead > 0) {
    buffer[bytesRead] = '\0'; // Null-terminate the string
    std::cout << "Received: " << buffer << std::endl;
  }

  serial.close();
  return 0;
}