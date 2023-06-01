#include "GameOfLifeHandler.h"

GameOfLifeHandler::GameOfLifeHandler() {
    mGameOfLife = std::make_unique<GameOfLife>(64, 64);
}

MODE GameOfLifeHandler::getModeName() {
    return MODE::GAME_OF_LIFE;
}

void GameOfLifeHandler::onInit() {

}

void GameOfLifeHandler::onFinish() {
    LedMatrix::getInstance()->clear();
}

void GameOfLifeHandler::execute() {
    mGameOfLife.get()->run();
}

void GameOfLifeHandler::updateParameters(ModeParameters parameters) {
    std::string key = parameters.first;
    std::string val = parameters.second;

    std::cout << "Keyval: " << key << " | " << val << std::endl;

    if (key == ModeConstants::KEY_GAME_OF_LIFE_MODE_ACTION) {
        if (val == "start") mGameOfLife.get()->start();
        else if (val == "stop") mGameOfLife.get()->stop();
        else if (val == "step") mGameOfLife.get()->step();
    } else if (key == ModeConstants::KEY_GAME_OF_LIFE_MODE_COLOR_ALIVE) {
        mGameOfLife.get()->setColorOfAlive(Color::fromHex(val));
    } else if (key == ModeConstants::KEY_GAME_OF_LIFE_MODE_COLOR_DEAD) {
        mGameOfLife.get()->setColorOfDead(Color::fromHex(val));
    } else if (key == ModeConstants::KEY_GAME_OF_LIFE_MODE_RULE_BIRTH) {
        mGameOfLife.get()->setRuleOfBirth(val);
    } else if (key == ModeConstants::KEY_GAME_OF_LIFE_MODE_RULE_SURVIVE) {
        mGameOfLife.get()->setRuleOfSurvive(val);
    } else if (key == ModeConstants::KEY_GAME_OF_LIFE_MODE_TIMEOUT) {
        mGameOfLife.get()->setTimeout(val);
    }
}