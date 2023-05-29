#ifndef SNAKE_HANDLER
#define SNAKE_HANDLER

#include "ModeConstants.h"
#include "IModeHandler.h"
#include "Snake.h"
#include "Color.h"

class Snake;

class SnakeHandler : public IModeHandler {
public:
    SnakeHandler();

    void onInit();
    void onFinish();
    void execute();
    void updateParameters(ModeParameters parameters);
    MODE getModeName();

private:
    std::unique_ptr<Snake> mSnake;
};

#endif // SNAKE_HANDLER
