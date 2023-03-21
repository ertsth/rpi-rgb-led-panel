#include "lib/include/led-matrix.h"

#include <thread>
#include <chrono>

using namespace std::chrono_literals;
using rgb_matrix::RGBMatrix;

int main(int argc, char **argv) {
    RGBMatrix::Options led_options;
    rgb_matrix::RuntimeOptions runtime;

    // Set defaults
    led_options.chain_length = 3;
    led_options.show_refresh_rate = true;
    led_options.rows = 64;
    led_options.cols = 64;
    led_options.hardware_mapping = "adafruit-hat";

    runtime.drop_privileges = 1;
    if (!rgb_matrix::ParseOptionsFromFlags(&argc, &argv, &led_options, &runtime)) {
        rgb_matrix::PrintMatrixFlags(stderr);
        return 1;
    }

    // Do your own command line handling with the remaining flags.
    //   while (getopt()) {...}

    // Looks like we're ready to start
    RGBMatrix *matrix = RGBMatrix::CreateFromOptions(led_options, runtime);
    if (matrix == NULL) {
        return 1;
    }

    //  .. now use matrix
    matrix->Fill(0, 255, 0);
    std::this_thread::sleep_for(5000ms);
    matrix->Clear();

    delete matrix;   // Make sure to delete it in the end to switch off LEDs.
    return 0;
}