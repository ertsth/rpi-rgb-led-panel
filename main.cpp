#include "src/BluetoothDevice.h"

#include <thread>
#include <chrono>
#include <iostream>

#include <unistd.h>               // for linux

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