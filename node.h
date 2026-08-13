#ifndef NODE_H
#define NODE_H

#include "pin.h"
#include "types.h"

#include <string>
#include <vector>

// Connection point between pins.
class Node {
private:
    std::string id;
    std::vector<Pin*> pins;
    logicstate state;
    float voltage;

public:
    explicit Node(const std::string& id);

    void addpin(Pin* pin);
    void removepin(Pin* pin);
    void calculatestate();

    float getvoltage() const;

    std::string getid() const;
    void setid(const std::string& newid);

    std::vector<Pin*> getpins() const;

    logicstate getstate() const;
    void setstate(logicstate newstate);
};

#endif
