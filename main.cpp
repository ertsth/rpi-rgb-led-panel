#include "lib/include/led-matrix.h"

#include <thread>
#include <chrono>

using namespace std::chrono_literals;
using rgb_matrix::RGBMatrix;

int main(int argc, char **argv) {

    RGBMatrix::Options led_options;
    led_options.chain_length = 3;
    led_options.show_refresh_rate = true;
    led_options.rows = 64;
    led_options.cols = 64;
    led_options.hardware_mapping = "adafruit-hat";
    led_options.brightness = 50;
    led_options.chain_length = 1;
    led_options.parallel = 1;
    led_options.pixel_mapper_config = "Mirror:V";
    led_options.pwm_lsb_nanoseconds = 180;

    rgb_matrix::RuntimeOptions runtime_options;
    runtime_options.drop_privileges = 1;
    runtime_options.gpio_slowdown = 1;

    if (!rgb_matrix::ParseOptionsFromFlags(&argc, &argv, &led_options, &runtime_options)) {
        rgb_matrix::PrintMatrixFlags(stderr);
        return 1;
    }

    RGBMatrix *matrix = RGBMatrix::CreateFromOptions(led_options, runtime_options);
    if (matrix == NULL) {
        return 1;
    }

    matrix->Fill(255, 255, 0);
    matrix->SetPixel(10, 10, 255, 0, 0);
    std::this_thread::sleep_for(10000ms);
    matrix->Clear();

    delete matrix;
    return 0;
}