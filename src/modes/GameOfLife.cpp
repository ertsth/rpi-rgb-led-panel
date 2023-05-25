#include "GameOfLife.h"

GameOfLife::GameOfLife(int rows, int cols)
        : GameOfLife(rows, cols, std::vector<std::vector<Cell>>(rows, std::vector<Cell>(cols))) {
    initRandomGrid();
}

GameOfLife::GameOfLife(int rows, int cols, std::vector<std::vector<Cell>> initState) {
    mRows = rows;
    mColumns = cols;
    mCellGridActive = initState;
    mCellGridBuffer = std::vector<std::vector<Cell>>(mRows, std::vector<Cell>(mColumns));

    mThread = std::make_unique<std::thread>(&GameOfLife::loop, this);
}

void GameOfLife::setColorOfAlive(Color color) {
    mColorAlive = color;
}

void GameOfLife::setColorOfDead(Color color) {
    mColorDead = color;
}

void GameOfLife::setRuleOfBirth(std::string rule) {
    mRuleBirth = rule;
}

void GameOfLife::setRuleOfSurvive(std::string rule) {
    mRuleSurvive = rule;
}

void GameOfLife::start() {
    mMutex.lock();
    mState = GameState::ACTIVE;
    mMutex.unlock();
}

void GameOfLife::loop() {

    while(true) {
        mMutex.lock();
        if (mState == GameState::ACTIVE) {
            mMutex.unlock();
            step();
        }
        mMutex.unlock();
        sleep(mTimeout_s);
    }
}

void GameOfLife::step() {
    runIteration();
    redraw();
}

void GameOfLife::stop() {
    mMutex.lock();
    mState = GameState::STOPPED;
    mMutex.unlock();
}

void GameOfLife::redraw() {
    // for (int i = 0; i < mRows; ++i) {
    //     for (int j = 0; j < mColumns; ++j) {
    //         if (mCellGridActive[i][j].state == CellState::ALIVE) mMatrix.setPixel(i, j, mColorAlive);
    //         else if (mCellGridActive[i][j].state == CellState::DEAD) mMatrix.setPixel(i, j, mColorDead);
    //     }
    // }
}

void GameOfLife::runIteration() {
    calculateBufferGrid();
    mCellGridActive = mCellGridBuffer;
}

void GameOfLife::calculateBufferGrid() {
    for (int i = 0; i < mRows; ++i) {
        for (int j = 0; j < mColumns; ++j) {
            int nNeighbors = countAliveNeighbors(i, j);
            if ((mRuleBirth.find(std::to_string(nNeighbors).c_str()) != mRuleBirth.npos)
                    && mCellGridActive[i][j].state == CellState::DEAD) mCellGridBuffer[i][j].state = CellState::ALIVE;
            else if ((mRuleSurvive.find(std::to_string(nNeighbors).c_str()) != mRuleSurvive.npos)
                    && mCellGridActive[i][j].state == CellState::ALIVE) mCellGridBuffer[i][j].state = CellState::ALIVE;
            else mCellGridBuffer[i][j].state = CellState::DEAD;
        }
    }
}

int GameOfLife::countAliveNeighbors(int x, int y) {
    int res = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if ((i == x) && (j == y)) continue;
            if ((i < 0) || (i >= mRows) || (j < 0) || (j >= mColumns)) continue;
            if (mCellGridActive[i][j].state == CellState::ALIVE) res++;
        }
    }
    return res;
}

void GameOfLife::printGrid(std::vector<std::vector<Cell>> &grid) {
    for (int i = 0; i < mRows; ++i) {
        for (int j = 0; j < mColumns; ++j) {
            std::cout << grid[i][j].state << " ";
        }
        std::cout << std::endl;
    }
}

void GameOfLife::initRandomGrid() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 2);

    for (int i = 0; i < mRows; ++i) {
        for (int j = 0; j < mColumns; ++j) {
            mCellGridActive[i][j] = {dis(gen) % 2 ? ALIVE : DEAD};
        }
    }
}