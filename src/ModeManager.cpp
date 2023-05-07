#include "ModeManager.h"

ModeManager::ModeManager() {

}

ModeManager::~ModeManager() {

}

void ModeManager::startMode(ModeManager::MODE mode) {
    switch (mode)
    {
    case HELLO:
        LuaWrapper::getInstance().doFile("modes/hello.lua");
        break;
    case GAME_LIFE:
        LuaWrapper::getInstance().doFile("modes/game_of_life.lua");
        break;

    default:
        break;
    }
}