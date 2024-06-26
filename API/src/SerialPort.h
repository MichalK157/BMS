#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <string>
#include <termios.h>

class SerialPort {
public:
  SerialPort(const std::string &portName, int baudRate);
  ~SerialPort();

  bool open();
  void close();
  int readData(uint8_t *buffer, size_t size);
  bool writeData(const uint8_t *buffer, size_t size);
  bool isOpen() const;

private:
  uint8_t tx_buffer[255];
  std::string portName;
  int baudRate;
  int fileDescriptor;
  bool openFlag;
  struct termios tty;
};

#endif // SERIALPORT_H