#include "ModeManager.h"

ModeManager::ModeManager() {

}

ModeManager::~ModeManager() {

}

void ModeManager::startMode(ModeManager::MODE mode) {
    if (mode == MODE::HELLO) {
        LuaWrapper::getInstance().doFile("modes/hello.lua");
    }
}