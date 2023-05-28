#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
#include <iostream>
#include "../lib/json/json.hpp"
#include "LedMatrix.h"
#include "LuaWrapper.h"
#include "GameOfLife.h"
#include <fstream>
#include "ModeConstants.h"
#include "ModeManager.h"
#include<unistd.h>               // for linux

class MessageHandler {
public:
    void handleMessage(std::string msg);
private:
    ModeManager mModeManager;
};

#endif // MESSAGE_HANDLER_H