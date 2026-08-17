#ifndef LIBRARY_MODEL_H
#define LIBRARY_MODEL_H

#include <string>
#include <vector>

struct ComponentInfo {
    std::string name;
    std::string category;
};

// Keeps available parts independent from Qt.
class LibraryModel {
private:
    std::vector<ComponentInfo> components_;

public:
    // model ro ba component haye avalie por mikone
    LibraryModel();

    // component haye yek category ro mide
    std::vector<ComponentInfo> get_by_category(const std::string& category) const;

    // component ha ro ba name/category search mikone
    std::vector<ComponentInfo> search(const std::string& query) const;

    // component ro ba name peyda mikone
    ComponentInfo get_by_name(const std::string& name) const;

    // category haye mojood ro mide
    std::vector<std::string> get_all_categories() const;
};

#endif
