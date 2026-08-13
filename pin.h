#ifndef PIN_H
#define PIN_H

#include "types.h"

#include <string>

//connection point for circuit components
class Pin {
private:
    std::string name;
    vector2d position;
    logicstate state;
    float sensitivityRadius;
    bool highlighted;

public:
    Pin(const std::string& name, const vector2d& position);

    bool isMouseOver(const vector2d& mousePos) const;

    std::string getName() const;
    void setName(const std::string& newName);

    vector2d getPosition() const;
    void setPosition(const vector2d& newPosition);

    logicstate getState() const;
    void setState(logicstate newState);

    float getSensitivityRadius() const;
    void setSensitivityRadius(float newRadius);

    bool isHighlighted() const;
    void setHighlighted(bool value);
};

#endif
