#include "Color.h"

Color::Color(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Color Color::of(const std::string& name) {
    // Implementation to create a Color object from a string name
    // TODO
    return *(new Color(0, 0, 0));
}

Color Color::fromHex(const std::string& hex) {

    unsigned int val;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> val;
    int r = val >> 16;
    int g = (val & 0x00ff00) >> 8;
    int b = val & 0x0000ff;

    return *(new Color(r, g, b));
}
