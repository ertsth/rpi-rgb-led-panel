// #include "src/ModeManager.h"
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
        sleep(5);
    }
    bt->disconnect();

    return 0;
}