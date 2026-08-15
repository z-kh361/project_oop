#ifndef COMPONENT_H
#define COMPONENT_H

#include "pin.h"
#include "types.h"

#include <string>
#include <vector>

// Base class for all circuit parts.
class Component {
protected:
    std::string name;
    std::string type;
    vector2d position;
    std::vector<Pin> pins;
    bool selected;
    int rotation;
    bool flip_h;
    bool flip_v;

public:
    // component jadid misaze
    Component(const std::string& name,
              const std::string& type,
              const vector2d& position);

    virtual ~Component() = default;

    // pin ha ro update mikone
    virtual void update_pins();
    // esme namayeshi ro mide
    virtual std::string get_display_name() const;
    // list property ha ro mide
    virtual std::vector<std::string> get_property_names() const;
    // meghdar property ro mide
    virtual std::string get_property(const std::string& key) const;
    // property ro avaz mikone
    virtual void set_property(const std::string& key, const std::string& value);
    // check mikone point dakhele component hast
    virtual bool contains_point(const vector2d& point) const;

    // entekhab mikone
    void select();
    // az entekhab dar miyare
    void deselect();

    // name ro mide
    std::string get_name() const;
    // name ro avaz mikone
    void set_name(const std::string& new_name);

    // type ro mide
    std::string get_type() const;
    // type ro avaz mikone
    void set_type(const std::string& new_type);

    // position ro mide
    vector2d get_position() const;
    // position ro avaz mikone
    void set_position(const vector2d& new_position);

    // pin ha ro mide
    std::vector<Pin>& get_pins();
    // pin ha ro readonly mide
    const std::vector<Pin>& get_pins() const;

    // mige selected hast ya na
    bool is_selected() const;

    // rotation ro mide
    int get_rotation() const;
    // rotation ro avaz mikone
    void set_rotation(int new_rotation);
    // 90 daraje micharkhoone
    void rotate();

    // mige flip horizontal hast ya na
    bool is_flip_h() const;
    // flip horizontal ro avaz mikone
    void set_flip_h(bool value);

    // mige flip vertical hast ya na
    bool is_flip_v() const;
    // flip vertical ro avaz mikone
    void set_flip_v(bool value);
};

#endif
