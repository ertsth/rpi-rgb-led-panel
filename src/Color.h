#ifndef COLOR_H
#define COLOR_H

#include <string>

class Color {
public:
    Color();
    Color(int r, int g, int b);

    int r;
    int g;
    int b;

    // Static method to create a color based on a string name
    static Color of(const std::string& name);
};

#endif // COLOR_H
