#ifndef GAME_OF_LIFE_HANDLER
#define GAME_OF_LIFE_HANDLER

#include "ModeConstants.h"
#include "IModeHandler.h"
#include "GameOfLife.h"
#include "Color.h"

class GameOfLife;

class GameOfLifeHandler : public IModeHandler {
public:
    GameOfLifeHandler();

    void onInit();
    void onFinish();
    void execute();
    void updateParameters(ModeParameters parameters);
    MODE getModeName();

private:
    std::unique_ptr<GameOfLife> mGameOfLife;
};

#endif // GAME_OF_LIFE_HANDLER
