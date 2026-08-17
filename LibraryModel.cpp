#include "LibraryModel.h"

#include <algorithm>
#include <cctype>

namespace {
std::string to_lower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });

    return value;
}
}

LibraryModel::LibraryModel()
    : components_({
          {"Ground", "Sources"},
          {"Battery", "Sources"},
          {"DC Source", "Sources"},
          {"Resistor", "Passive"},
          {"Capacitor", "Passive"},
          {"Inductor", "Passive"},
          {"Switch", "Active"},
          {"Push Button", "Active"},
          {"LED", "Active"},
          {"7-Segment", "Active"},
          {"AND", "Digital"},
          {"OR", "Digital"},
          {"NOT", "Digital"},
          {"NAND", "Digital"},
          {"XOR", "Digital"},
          {"DFF", "Digital"}
      }) {}

std::vector<ComponentInfo> LibraryModel::get_by_category(const std::string& category) const {
    std::vector<ComponentInfo> result;

    for (const ComponentInfo& component : components_) {
        if (component.category == category) {
            result.push_back(component);
        }
    }

    return result;
}

std::vector<ComponentInfo> LibraryModel::search(const std::string& query) const {
    std::vector<ComponentInfo> result;
    std::string lower_query = to_lower(query);

    if (lower_query.empty()) {
        return components_;
    }

    for (const ComponentInfo& component : components_) {
        std::string lower_name = to_lower(component.name);
        std::string lower_category = to_lower(component.category);

        if (lower_name.find(lower_query) != std::string::npos ||
            lower_category.find(lower_query) != std::string::npos) {
            result.push_back(component);
        }
    }

    return result;
}

ComponentInfo LibraryModel::get_by_name(const std::string& name) const {
    for (const ComponentInfo& component : components_) {
        if (component.name == name) {
            return component;
        }
    }

    return {"", ""};
}

std::vector<std::string> LibraryModel::get_all_categories() const {
    std::vector<std::string> categories;

    for (const ComponentInfo& component : components_) {
        if (std::find(categories.begin(), categories.end(), component.category) == categories.end()) {
            categories.push_back(component.category);
        }
    }

    return categories;
}
