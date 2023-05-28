#include "DummyHandler.h"

MODE DummyHandler::getModeName() {
    return MODE::NONE;
}

void DummyHandler::onInit() {
    std::cout << "Dummy onInit" << std::endl;
}

void DummyHandler::onFinish() {
    std::cout << "Dummy onFinish" << std::endl;
}

void DummyHandler::execute() {
    // std::cout << "Dummy execute" << std::endl;
}

void DummyHandler::updateParameters(ModeParameters parameters) {
    std::string key = parameters.first;
    std::string val = parameters.second;

    std::cout << "Dummy Keyval: " << key << " | " << val << std::endl;
}