#include "BluetoothDevice.h"

void BluetoothDevice::connect() {
    if (m_fd < 0) {
        printf("Connecting...");
        m_fd = open(m_serial_port_name.c_str(), O_RDWR);
        m_thread = std::make_unique<std::thread>(BluetoothDevice::ReadThread(), this);
        printf("m_fd = %i", m_fd);
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

void BluetoothDevice::ReadThread::operator()(BluetoothDevice* bt) {
    MessageHandler handler;
    while (true)
    {
        if (bt->m_fd < 0) {
            printf("Error %i from open: %s\n", errno, "strerror(errno)");
        } else {
            char read_buf [1024] = {};

            int num_bytes = read(bt->m_fd, &read_buf, sizeof(read_buf));

            if (num_bytes > 0) {
                printf("Received message(%i): %s\n", num_bytes, read_buf);
            }

            std::string msg(read_buf);
            // TODO: handle in a separate thread
            handler.handleMessage(msg);
        }
    }
}