#include "SnakeHandler.h"

SnakeHandler::SnakeHandler() {
    mSnake = std::make_unique<Snake>(64, 64);
}

MODE SnakeHandler::getModeName() {
    return MODE::SNAKE;
}

void SnakeHandler::onInit() {
    mSnake.get()->init();
}

void SnakeHandler::onFinish() {
    LedMatrix::getInstance()->clear();
}

void SnakeHandler::execute() {
    mSnake.get()->step();
}

void SnakeHandler::updateParameters(ModeParameters parameters) {
    std::string key = parameters.first;
    std::string val = parameters.second;

    if (key == ModeConstants::KEY_SNAKE_DIRECTION) {
        if (val == "up") mSnake.get()->setDirection(UP);
        else if (val == "left") mSnake.get()->setDirection(LEFT);
        else if (val == "right") mSnake.get()->setDirection(RIGHT);
        else if (val == "down") mSnake.get()->setDirection(DOWN);
    } else if (key == ModeConstants::KEY_SNAKE_COLOR_FIELD) {
        mSnake.get()->setColorField(Color::fromHex(val));
    } else if (key == ModeConstants::KEY_SNAKE_COLOR_SNAKE) {
        mSnake.get()->setColorSnake(Color::fromHex(val));
    } else if (key == ModeConstants::KEY_SNAKE_COLOR_FOOD) {
        mSnake.get()->setColorFood(Color::fromHex(val));
    } else if (key == ModeConstants::KEY_SNAKE_TIMEOUT) {
        mSnake.get()->setTimeout(val);
    }
}