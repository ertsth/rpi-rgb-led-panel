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
