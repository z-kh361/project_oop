#ifndef TYPES_H
#define TYPES_H

// Signal states.
enum class logicstate {
    low,
    high,
    undefined,
    floating
};

// Simple 2D point.
struct vector2d {
    float x;
    float y;

    vector2d(float xvalue = 0.0f, float yvalue = 0.0f);

    float distanceto(const vector2d& other) const;
};

// Simple RGB color.
class color {
public:
    int r;
    int g;
    int b;

    color(int red = 0, int green = 0, int blue = 0);

    static const color red;
    static const color green;
    static const color blue;
    static const color gray;
    static const color yellow;
};

#endif
