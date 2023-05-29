#include "ModeManager.h"

ModeManager::ModeManager() {
    mActiveMode = std::make_unique<DummyHandler>();
    startActiveModeExecution();
}

ModeManager::~ModeManager() {

}

void ModeManager::startMode(MODE mode) {
    std::cout << "Starting mode: " << mode << std::endl;
    mActiveMode.get()->onFinish();
    // mExecute.get()->join();
    switch (mode)
    {
        case MODE::GAME_OF_LIFE:
            mActiveMode = std::make_unique<GameOfLifeHandler>();
            break;
        case MODE::SNAKE:
            mActiveMode = std::make_unique<SnakeHandler>();
            break;
        default:

            break;
    }

    mActiveMode.get()->onInit();
    // startActiveModeExecution();
}

void ModeManager::updateParameters(ModeParameters parameters) {
    // TODO: add mutex
    mActiveMode.get()->updateParameters(parameters);
}

void ModeManager::startActiveModeExecution() {
    mExecute = std::make_unique<std::thread>(ModeManager::ExecuteThread(), this);
}

MODE ModeManager::getActiveMode() {
    return mActiveMode.get()->getModeName();
}

void ModeManager::ExecuteThread::operator()(ModeManager* mm) {
    while (true)
    {
        mm->mActiveMode.get()->execute();
    }
}