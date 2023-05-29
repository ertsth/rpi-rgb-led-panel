#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <string>
#include <random>
#include "Color.h"
#include "LedMatrix.h"
#include <thread>
#include <mutex>
#include <chrono>

#include <iostream>

enum CellType {
    EMPTY,
    BODY,
    HEAD,
    FOOD
};

enum Direction {
    UP,
    LEFT,
    RIGHT,
    DOWN
};

struct FieldCell {
    CellType type = EMPTY;
    // Direction nextCell;
    int age;
};

struct Position {
    int x = -1;
    int y = -1;
};

class Snake {
    public:
    Snake(int w, int h);
    void init();
    void step();
    bool isGameEnd();
    void redraw();

    void setTimeout(std::string );
    void setDirection(Direction direction);
    void setColorFood(Color color);
    void setColorSnake(Color color);
    void setColorField(Color color);

    private:
    bool isOutOfBounds(Position pos);
    bool isOnFood(Position pos);
    void generateFood();
    void createSnake();
    Position getNextCell(Position curr, Direction direction);

    std::vector<std::vector<FieldCell>> mActiveField;
    std::vector<std::vector<FieldCell>> mBuferField;
    int mWidth = 0;
    int mHeight = 0;

    Direction mDirection = RIGHT;
    bool mIsGameEnd = false;
    int mLength;

    Color mColorSnake = Color(0, 255, 0);
    Color mColorFood = Color(255, 0, 0);
    Color mColorField = Color(0, 0, 0);

    uint const DEFAULT_TIMEOUT = 1000;
    uint mTimeout = DEFAULT_TIMEOUT;
};



#endif // SNAKE_H