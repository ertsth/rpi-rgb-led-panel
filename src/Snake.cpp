#include "Snake.h"

Snake::Snake(int w, int h) {
    mWidth = w;
    mHeight = h;
    mActiveField = std::vector<std::vector<FieldCell>>(mWidth, std::vector<FieldCell>(mHeight));
    mBuferField = std::vector<std::vector<FieldCell>>(mWidth, std::vector<FieldCell>(mHeight));
    init();
}

void Snake::setColorField(Color color) {
    mColorField = color;
}

void Snake::setColorSnake(Color color) {
    mColorSnake = color;
}

void Snake::setColorFood(Color color) {
    mColorFood = color;
}

void Snake::setDirection(Direction direction) {
    std::cout << "direction " << direction << std::endl;
    mDirection = direction;
}

void Snake::setTimeout(std::string timeout) {
    mTimeout = DEFAULT_TIMEOUT * std::stof(timeout);
}

void Snake::init() {
    createSnake();
    generateFood();
}

void Snake::step() {
    for (int i = 0; i < mWidth; i++) {
        for (int j = 0; j < mHeight; j++) {
            FieldCell cell = mActiveField[i][j];
            Position nextPosition = getNextCell({i, j}, mDirection);
            switch (cell.type)
            {
            case BODY:
            std::cout << "Body at " << i << " " << j << std::endl;
                // mBuferField[nextPosition.x][nextPosition.y].type = BODY;
                // mBuferField[i][j].type = EMPTY;
                // mBuferField[nextPosition.x][nextPosition.y].nextCell = mActiveField[i][j].nextCell;
                mBuferField[i][j].age--;
                if (mBuferField[i][j].age == 0) {
                    mBuferField[i][j].type = EMPTY;
                }
                break;
            case HEAD:
                if (isOutOfBounds(nextPosition)) {
                    mIsGameEnd = true;
                } else {
                    if (isOnFood(nextPosition)) {
                        mLength++;
                        generateFood();
                    }
                    mBuferField[nextPosition.x][nextPosition.y].type = HEAD;
                    mBuferField[nextPosition.x][nextPosition.y].age = mLength;
                    mBuferField[i][j].type = BODY;
                    mBuferField[i][j].age--;
                    // mBuferField[nextPosition.x][nextPosition.y].nextCell = mDirection;
                }
                break;
            default:

                break;
            }
        }
    }
    mActiveField = mBuferField;
    redraw();
    std::this_thread::sleep_for(std::chrono::milliseconds(mTimeout));
}

void Snake::redraw() {
    for (int i = 0; i < mWidth; i++) {
        for (int j = 0; j < mHeight; j++) {
            FieldCell cell = mActiveField[i][j];
            switch (cell.type)
            {
            case BODY:
                LedMatrix::getInstance()->setPixel(i, j, mColorSnake);
                break;
            case HEAD:
                LedMatrix::getInstance()->setPixel(i, j, Color(0, 0, 255));
                break;
            case EMPTY:
                LedMatrix::getInstance()->setPixel(i, j, mColorField);
                break;
            case FOOD:
                LedMatrix::getInstance()->setPixel(i, j, mColorFood);
                break;
            default:

                break;
            }
        }
    }
}

bool Snake::isOutOfBounds(Position pos) {
    return (pos.x < 0 || pos.x >= mWidth || pos.y < 0 || pos.y >= mHeight);
}

bool Snake::isGameEnd() {
    return mIsGameEnd;
}

bool Snake::isOnFood(Position pos) {
    return (mActiveField[pos.x][pos.y].type == FOOD);
}

void Snake::generateFood() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> posX(0, mWidth - 1);
    std::uniform_int_distribution<int> posY(0, mHeight - 1);
    int x = -1;
    int y = -1;
    do {
        x = posX(gen);
        y = posY(gen);
    } while (mBuferField[x][y].type != EMPTY);
    mBuferField[x][y].type = FOOD;
    std::cout << "Food generated at " << x << " " << y << std::endl;
}

void Snake::createSnake() {
    mLength = 3;

    mActiveField[mWidth / 2][mHeight / 2].type = BODY;
    mActiveField[mWidth / 2][mHeight / 2].age = mLength - 2;

    mActiveField[(mWidth / 2) - 1][mHeight / 2].type = BODY;
    mActiveField[(mWidth / 2) - 1][mHeight / 2].age = mLength - 1;

    mActiveField[(mWidth / 2) + 1][mHeight / 2].type = HEAD;
    mActiveField[(mWidth / 2) + 1][mHeight / 2].age = mLength;
}

Position Snake::getNextCell(Position curr, Direction direction) {
    Position next;
    switch(direction)
    {
        case UP:
            next.x = curr.x;
            next.y = curr.y - 1;
            break;
        case LEFT:
            next.x = curr.x - 1;
            next.y = curr.y;
            break;
        case RIGHT:
            next.x = curr.x + 1;
            next.y = curr.y;
            break;
        case DOWN:
            next.x = curr.x;
            next.y = curr.y + 1;
            break;
        default:
            next.x = curr.x;
            next.y = curr.y;
            break;
    }
    return next;
}