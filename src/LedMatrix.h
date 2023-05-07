#ifndef LED_MATRIX_H
#define LED_MATRIX_H

// TODO: consider avoiding relative includes
#include "../lib/rpi-rgb-led-matrix/include/led-matrix.h"
#include "../lib/rpi-rgb-led-matrix/include/canvas.h"
#include "Color.h"

#include <memory>

class LedMatrix {
public:
    LedMatrix();
    void setPixel(int x, int y, Color color);
    void fill(Color color);
    void clear();

private:
    std::unique_ptr<rgb_matrix::Canvas> _libMatrix;

    rgb_matrix::RGBMatrix::Options* parseConstOptions();
    rgb_matrix::RuntimeOptions* parseRuntimeOptions();
};

#endif // LED_MATRIX_H
