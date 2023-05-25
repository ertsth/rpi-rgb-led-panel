#ifndef GAME_OF_LIFE
#define GAME_OF_LIFE

#include "../Color.h"
#include "../LedMatrix.h"
#include <string>
#include<unistd.h>
#include <vector>
#include <iostream>
#include <random>
#include <thread>
#include <mutex>

enum GameState {
    ACTIVE,
    STOPPED
};

enum CellState {
    DEAD = 0,
    ALIVE = 1
};

struct Cell {
    CellState state = CellState::DEAD;
};

class GameOfLife {
public:
    GameOfLife(int rows, int cols);
    GameOfLife(int rows, int cols, std::vector<std::vector<Cell>> initState);
    void start();
    void stop();
    void step();
    void setColorOfAlive(Color color);
    void setColorOfDead(Color color);
    void setRuleOfBirth(std::string rule);
    void setRuleOfSurvive(std::string rule);

    // TODO
    // void setSpeed();

private:
    void loop();
    void runIteration();
    void redraw();
    void calculateBufferGrid();
    int countAliveNeighbors(int x, int y);

    // debug
    void printGrid(std::vector<std::vector<Cell>> &grid);
    void initRandomGrid();

    GameState mState = GameState::STOPPED;
    Color mColorDead = Color(0, 0, 0);
    Color mColorAlive = Color(255, 255, 255);
    std::string mRuleBirth = "3";
    std::string mRuleSurvive = "23";
    uint mTimeout_s = 1;

    int mRows = 0;
    int mColumns = 0;
    std::vector<std::vector<Cell>> mCellGridActive;
    std::vector<std::vector<Cell>> mCellGridBuffer;

    // LedMatrix mMatrix;

    std::unique_ptr<std::thread> mThread;
    std::mutex mMutex;
};

#endif