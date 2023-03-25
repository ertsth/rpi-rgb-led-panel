#include "src/ModeManager.h"

#include <thread>
#include <chrono>

using namespace std::chrono_literals;

int main(int argc, char **argv) {

    ModeManager* mm = new ModeManager();
    mm->startMode(ModeManager::MODE::HELLO);

    return 0;
}