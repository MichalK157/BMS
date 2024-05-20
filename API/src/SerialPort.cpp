#include "SerialPort.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>

SerialPort::SerialPort(const std::string& portName, int baudRate)
    : portName(portName), baudRate(baudRate), fileDescriptor(-1), openFlag(false) {
    memset(&tty, 0, sizeof tty);
}

SerialPort::~SerialPort() {
    close();
}

bool SerialPort::open() {
    fileDescriptor = ::open(portName.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fileDescriptor < 0) {
        std::cerr << "Error opening " << portName << ": " << strerror(errno) << std::endl;
        return false;
    }

    if (tcgetattr(fileDescriptor, &tty) != 0) {
        std::cerr << "Error getting attributes: " << strerror(errno) << std::endl;
        ::close(fileDescriptor);
        return false;
    }

    cfsetospeed(&tty, baudRate);
    cfsetispeed(&tty, baudRate);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN]  = 1;
    tty.c_cc[VTIME] = 5;

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag |= 0;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fileDescriptor, TCSANOW, &tty) != 0) {
        std::cerr << "Error setting attributes: " << strerror(errno) << std::endl;
        ::close(fileDescriptor);
        return false;
    }

    openFlag = true;
    return true;
}

void SerialPort::close() {
    if (openFlag) {
        ::close(fileDescriptor);
        openFlag = false;
    }
}

int SerialPort::readData(uint8_t* buffer, unsigned int size) {
    if (!openFlag) return -1;
    return ::read(fileDescriptor, buffer, size);
}

bool SerialPort::writeData(const char* buffer, unsigned int size) {
    if (!openFlag) return false;
    return ::write(fileDescriptor, buffer, size) == size;
}

bool SerialPort::isOpen() const {
    return openFlag;
}
