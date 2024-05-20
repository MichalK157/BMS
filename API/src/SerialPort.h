#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <string>
#include <termios.h>

class SerialPort 
{
public:
    SerialPort(const std::string& portName, int baudRate);
    ~SerialPort();

    bool open();
    void close();
    int readData(uint8_t* buffer, unsigned int size);
    bool writeData(const char* buffer, unsigned int size);
    bool isOpen() const;

private:
    std::string portName;
    int baudRate;
    int fileDescriptor;
    bool openFlag;
    struct termios tty;
};

#endif // SERIALPORT_H