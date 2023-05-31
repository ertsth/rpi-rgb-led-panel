#ifndef BLUETOOTH_DEVICE_H
#define BLUETOOTH_DEVICE_H

#include <string>
#include <cstring>
#include <thread>
#include <stdio.h>
#include <iostream>
// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

#include "MessageHandler.h"
#include "MessagePreprocessor.h"

class BluetoothDevice {
public:
    void connect();
    void disconnect();
    void writeMsg(std::string &msg);
    bool isConnected();

    class ReadThread {
        public:
        void operator()(BluetoothDevice* bt);
    };

private:
    std::string m_serial_port_name = "/dev/rfcomm0";
    int m_fd = -1;
    std::unique_ptr<std::thread> m_thread;
    bool m_isConnected = false;
};

#endif // BLUETOOTH_DEVICE_H