#ifndef LIBRARY_COMPONENT_FACTORY_H
#define LIBRARY_COMPONENT_FACTORY_H

#include "component.h"
#include "types.h"

#include <string>

class ComponentFactory {
public:
    // component jadid bar asas type misaze
    static Component* create(const std::string& type,
                             const std::string& name,
                             const vector2d& position);
};

#endif
