#include "ComponentFactory.h"

#include "core/Battery.h"
#include "core/Ground.h"
#include "core/LED.h"
#include "core/LogicGates.h"
#include "core/Switch.h"
#include "resistor.h"

Component* ComponentFactory::create(const std::string& type,
                                    const std::string& name,
                                    const vector2d& position) {
    if (type == "Resistor") {
        return new Resistor(name, position);
    }
    if (type == "Battery") {
        return new Battery(name, position);
    }
    if (type == "Ground") {
        return new Ground(name, position);
    }
    if (type == "LED") {
        return new LED(name, position);
    }
    if (type == "Switch") {
        return new Switch(name, position);
    }
    if (type == "AND") {
        return new ANDGate(name, position);
    }
    if (type == "OR") {
        return new ORGate(name, position);
    }
    if (type == "NOT") {
        return new NOTGate(name, position);
    }
    if (type == "NAND") {
        return new NANDGate(name, position);
    }
    if (type == "XOR") {
        return new XORGate(name, position);
    }
    if (type == "DFF" || type == "D-FlipFlop") {
        return new DFlipFlop(name, position);
    }

    return nullptr;
}
