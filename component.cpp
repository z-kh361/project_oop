#include "component.h"

Component::Component(const std::string& name,
                     const std::string& type,
                     const vector2d& position)
    : name(name),
      type(type),
      position(position),
      selected(false),
      rotation(0),
      flippedh(false),
      flippedv(false) {}

void Component::updatepins() {
    // Child classes can update pin positions here.
}

std::string Component::getdisplayname() const {
    return name;
}

std::vector<std::string> Component::getpropertynames() const {
    return {"name", "type", "x", "y", "rotation", "flippedh", "flippedv"};
}

std::string Component::getproperty(const std::string& key) const {
    if (key == "name") {
        return name;
    }
    if (key == "type") {
        return type;
    }
    if (key == "x") {
        return std::to_string(position.x);
    }
    if (key == "y") {
        return std::to_string(position.y);
    }
    if (key == "rotation") {
        return std::to_string(rotation);
    }
    if (key == "flippedh") {
        return flippedh ? "true" : "false";
    }
    if (key == "flippedv") {
        return flippedv ? "true" : "false";
    }

    return "";
}

void Component::setproperty(const std::string& key, const std::string& value) {
    if (key == "name") {
        name = value;
    } else if (key == "type") {
        type = value;
    } else if (key == "x") {
        position.x = std::stof(value);
    } else if (key == "y") {
        position.y = std::stof(value);
    } else if (key == "rotation") {
        setrotation(std::stoi(value));
    } else if (key == "flippedh") {
        flippedh = (value == "true" || value == "1");
    } else if (key == "flippedv") {
        flippedv = (value == "true" || value == "1");
    }
}

void Component::select() {
    selected = true;
}

void Component::deselect() {
    selected = false;
}

std::string Component::getname() const {
    return name;
}

void Component::setname(const std::string& newname) {
    name = newname;
}

std::string Component::gettype() const {
    return type;
}

void Component::settype(const std::string& newtype) {
    type = newtype;
}

vector2d Component::getposition() const {
    return position;
}

void Component::setposition(const vector2d& newposition) {
    position = newposition;
    updatepins();
}

std::vector<Pin>& Component::getpins() {
    return pins;
}

const std::vector<Pin>& Component::getpins() const {
    return pins;
}

bool Component::isselected() const {
    return selected;
}

int Component::getrotation() const {
    return rotation;
}

void Component::setrotation(int newrotation) {
    rotation = ((newrotation % 360) + 360) % 360;
    updatepins();
}

bool Component::isflippedh() const {
    return flippedh;
}

void Component::setflippedh(bool value) {
    flippedh = value;
    updatepins();
}

bool Component::isflippedv() const {
    return flippedv;
}

void Component::setflippedv(bool value) {
    flippedv = value;
    updatepins();
}
