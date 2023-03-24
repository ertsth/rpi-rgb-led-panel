#include "LedMatrix.h"

LedMatrix::LedMatrix() {
    rgb_matrix::RGBMatrix::Options* led_options = parseConstOptions();
    rgb_matrix::RuntimeOptions* runtime_options = parseRuntimeOptions();

    rgb_matrix::RGBMatrix* matrix = rgb_matrix::RGBMatrix::CreateFromOptions(*led_options, *runtime_options);

    this->_libMatrix = std::unique_ptr<rgb_matrix::RGBMatrix>(matrix);
}

rgb_matrix::RGBMatrix::Options* LedMatrix::parseConstOptions() {
    // TODO: change to actual parsing from another module
    rgb_matrix::RGBMatrix::Options* led_options = new rgb_matrix::RGBMatrix::Options();
    led_options->chain_length = 3;
    led_options->show_refresh_rate = true;
    led_options->rows = 64;
    led_options->cols = 64;
    led_options->hardware_mapping = "adafruit-hat";
    led_options->brightness = 50;
    led_options->chain_length = 1;
    led_options->parallel = 1;
    led_options->pixel_mapper_config = "Mirror:V";
    led_options->pwm_lsb_nanoseconds = 180;

    return led_options;
}

rgb_matrix::RuntimeOptions* LedMatrix::parseRuntimeOptions() {
    // TODO: change to actual parsing from another module
    rgb_matrix::RuntimeOptions* runtime_options = new rgb_matrix::RuntimeOptions();
    runtime_options->drop_privileges = 1;
    runtime_options->gpio_slowdown = 4;

    return runtime_options;
}

void LedMatrix::setPixel(int x, int y, Color color) {
    _libMatrix->SetPixel(x, y, color.r, color.g, color.b);
}

void LedMatrix::fill(Color color) {
    _libMatrix->Fill(color.r, color.g, color.b);
}

void LedMatrix::clear() {
    _libMatrix->Clear();
}
