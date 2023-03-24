#include "src/Color.h"
#include "src/LedMatrix.h"

#include <thread>
#include <chrono>

using namespace std::chrono_literals;
using rgb_matrix::RGBMatrix;

int main(int argc, char **argv) {

    LedMatrix* matrix = new LedMatrix();
    matrix->fill(*(new Color(0, 255, 0)));
    matrix->setPixel(10, 10, *(new Color(255, 255, 0)));
    // std::this_thread::sleep_for(10000ms);
    // matrix->clear();
    std::this_thread::sleep_for(5000ms);

    matrix->clear();
    matrix->fill(*(new Color(255, 255, 0)));
    std::this_thread::sleep_for(1000ms);

    delete matrix;
    return 0;
}