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

    // noghte ro misaze
    vector2d(float x_value = 0.0f, float y_value = 0.0f);

    // fasele ta noghte dige
    float distance_to(const vector2d& other) const;
};

// Simple RGB color.
class color {
public:
    int r;
    int g;
    int b;

    // rang ro misaze
    color(int red = 0, int green = 0, int blue = 0);

    static const color red;
    static const color green;
    static const color blue;
    static const color gray;
    static const color yellow;
};

#endif
