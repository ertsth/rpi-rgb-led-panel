#include "DummyHandler.h"

MODE DummyHandler::getModeName() {
    return MODE::NONE;
}

void DummyHandler::onInit() {
}

void DummyHandler::onFinish() {
    LedMatrix::getInstance()->clear();
}

void DummyHandler::execute() {
}

void DummyHandler::updateParameters(ModeParameters parameters) {
    std::string key = parameters.first;
    std::string val = parameters.second;
}