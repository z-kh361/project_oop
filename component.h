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
    bool flippedh;
    bool flippedv;

public:
    Component(const std::string& name,
              const std::string& type,
              const vector2d& position);

    virtual ~Component() = default;

    virtual void updatepins();
    virtual std::string getdisplayname() const;
    virtual std::vector<std::string> getpropertynames() const;
    virtual std::string getproperty(const std::string& key) const;
    virtual void setproperty(const std::string& key, const std::string& value);

    void select();
    void deselect();

    std::string getname() const;
    void setname(const std::string& newname);

    std::string gettype() const;
    void settype(const std::string& newtype);

    vector2d getposition() const;
    void setposition(const vector2d& newposition);

    std::vector<Pin>& getpins();
    const std::vector<Pin>& getpins() const;

    bool isselected() const;

    int getrotation() const;
    void setrotation(int newrotation);

    bool isflippedh() const;
    void setflippedh(bool value);

    bool isflippedv() const;
    void setflippedv(bool value);
};

#endif
