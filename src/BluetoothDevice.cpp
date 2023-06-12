#include "BluetoothDevice.h"

void BluetoothDevice::connect() {
    if (isConnected()) return;
    printf("Connecting...\n");
    m_fd = open(m_serial_port_name.c_str(), O_RDWR);
    printf("m_fd = %i\n", m_fd);
    if (m_fd > 0) {
        m_isConnected = true;
        m_thread = std::make_unique<std::thread>(BluetoothDevice::ReadThread(), this);
    }
}

void BluetoothDevice::disconnect() {
    m_thread.get()->join();
    close(m_fd);
}

void BluetoothDevice::writeMsg(std::string &msg) {
    if (m_fd < 0) return;
    int size = msg.size();
    unsigned char* msg_chars = (unsigned char*) msg.c_str();
    std::cout << "Msg: " << msg.c_str() << ". s=" << size << std::endl;
    ssize_t n = write(m_fd, msg_chars, size);
    std::cout << "Write " << n << " bytes" << std::endl;
}

bool BluetoothDevice::isConnected() {
    return m_isConnected;
}

void BluetoothDevice::ReadThread::operator()(BluetoothDevice* bt) {
    MessagePreprocessor preprocessor;
    while (true)
    {
        if (bt->m_fd < 0) {
            printf("Error %i from open: %s\n", errno, strerror(errno));
            bt->m_isConnected = false;
        } else {
            char read_buf [1024] = {};

            int num_bytes = read(bt->m_fd, &read_buf, sizeof(read_buf));

            if (num_bytes > 0) {
                // printf("Received message(%i): %s\n", num_bytes, read_buf);
            }

            std::string msg(read_buf);
            preprocessor.addData(msg);
        }
    }
}