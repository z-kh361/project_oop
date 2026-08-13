#include "types.h"

#include <cmath>

vector2d::vector2d(float xvalue, float yvalue)
    : x(xvalue), y(yvalue) {}

float vector2d::distanceto(const vector2d& other) const {
    const float dx = x - other.x;
    const float dy = y - other.y;

    return std::sqrt(dx * dx + dy * dy);
}

color::color(int red, int green, int blue)
    : r(red), g(green), b(blue) {}

const color color::red(255, 0, 0);
const color color::green(0, 255, 0);
const color color::blue(0, 0, 255);
const color color::gray(128, 128, 128);
const color color::yellow(255, 255, 0);
