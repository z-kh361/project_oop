#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "component.h"
#include "node.h"

#include <string>
#include <vector>

// Wire data.
struct Wire {
    std::string id;
    std::string start_pin;
    std::string end_pin;

    // wire jadid misaze
    Wire(const std::string& id,
         const std::string& start_pin,
         const std::string& end_pin);
};

// Main circuit
class Circuit {
private:
    std::vector<Component*> components;
    std::vector<Wire> wires;
    std::vector<Node> nodes;
    bool running;
    int wire_counter;

    Pin* find_pin(const std::string& pin_id) const;

public:
    // circuit khali misaze
    Circuit();

    // component ezafe mikone
    void add_component(Component* comp);
    // component ro ba name hazf mikone
    void remove_component(const std::string& name);
    // component ro ba name peyda mikone
    Component* find_component(const std::string& name) const;

    // wire jadid beyne do pin misaze
    void add_wire(const std::string& pin1_id, const std::string& pin2_id);
    // wire ro ba id hazf mikone
    void remove_wire(const std::string& wire_id);

    // hame node ha ro update mikone
    void update_all_nodes();
    // yek step simulation mizane
    void run_simulation();

    // circuit ro JSON mikone
    std::string save_to_json() const;
    // circuit ro az JSON mikhoone
    void load_from_json(const std::string& data);

    // component ha ro mide
    std::vector<Component*> get_components() const;
    // wire ha ro mide
    std::vector<Wire> get_wires() const;
    // node ha ro mide
    std::vector<Node> get_nodes() const;

    // mige simulation run hast ya na
    bool is_running() const;
    // simulation ro stop mikone
    void stop();
};

#endif
