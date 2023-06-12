#include "src/BluetoothDevice.h"

#include <thread>
#include <chrono>
#include <unistd.h>

int main(int argc, char **argv) {

    BluetoothDevice* bt = new BluetoothDevice();
    while (true)
    {
        bt->connect();
        sleep(1);
    }
    bt->disconnect();

    return 0;
}