#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
#include <iostream>
#include "../lib/json/json.hpp"
#include "LedMatrix.h"
#include "LuaWrapper.h"
#include <fstream>

#include<unistd.h>               // for linux

class MessageHandler {
public:
    void handleMessage(std::string msg);
    void processMessage();

    // Modes
    const static char* MODE_PAINT;
    const static char* MODE_SPOTIFY;
    const static char* MODE_GAME_OF_LIFE;
    const static char* MODE_IMAGE;
    const static char* MODE_SNAKE;
    const static char* MODE_CUSTOM;

    // General commands
    const static char* KEY_GENERAL_MODE_NAME;
    const static char* KEY_GENERAL_SET_PIXEL;
    const static char* KEY_GENERAL_FILL_MATRIX;
    // Spotify mode
    const static char* KEY_SPOTIFY_TOKEN;
    // Game of life mode
    const static char* KEY_GAME_OF_LIFE_MODE_ACTION;
    const static char* KEY_GAME_OF_LIFE_MODE_COLOR_ALIVE;
    const static char* KEY_GAME_OF_LIFE_MODE_COLOR_DEAD;
    const static char* KEY_GAME_OF_LIFE_MODE_RULE_BIRTH;
    const static char* KEY_GAME_OF_LIFE_MODE_RULE_SURVIVE;
    const static char* KEY_GAME_OF_LIFE_MODE_SPEED;
    // Custom mode
    const static char* KEY_CUSTOM_SCRIPT;
    // Snake mode
    const static char* KEY_SNAKE_COLOR_BACKGROUND;
    const static char* KEY_SNAKE_COLOR_SNAKE;
    const static char* KEY_SNAKE_COLOR_FOOD;
    const static char* KEY_SNAKE_DIRECTION;
private:
    LedMatrix mMatrix;
};

#endif // MESSAGE_HANDLER_H