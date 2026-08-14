#include "circuit.h"

#include <nlohmann/json.hpp>

#include <algorithm>

using json = nlohmann::json;

Wire::Wire(const std::string& id,
           const std::string& start_pin,
           const std::string& end_pin)
    : id(id), start_pin(start_pin), end_pin(end_pin) {}

Circuit::Circuit()
    : running(false), wire_counter(0) {}

void Circuit::add_component(Component* comp) {
    if (comp == nullptr) {
        return;
    }

    components.push_back(comp);
}

void Circuit::remove_component(const std::string& name) {
    components.erase(
        std::remove_if(
            components.begin(),
            components.end(),
            [&name](Component* comp) {
                return comp != nullptr && comp->get_name() == name;
            }),
        components.end());
}

Component* Circuit::find_component(const std::string& name) const {
    for (Component* comp : components) {
        if (comp != nullptr && comp->get_name() == name) {
            return comp;
        }
    }

    return nullptr;
}

void Circuit::add_wire(const std::string& pin1_id, const std::string& pin2_id) {
    std::string wire_id = "wire_" + std::to_string(++wire_counter);
    wires.emplace_back(wire_id, pin1_id, pin2_id);
}

void Circuit::remove_wire(const std::string& wire_id) {
    wires.erase(
        std::remove_if(
            wires.begin(),
            wires.end(),
            [&wire_id](const Wire& wire) {
                return wire.id == wire_id;
            }),
        wires.end());
}

void Circuit::update_all_nodes() {
    nodes.clear();

    for (const Wire& wire : wires) {
        Node node(wire.id);

        // pin id format: component.pin
        Pin* start = find_pin(wire.start_pin);
        Pin* end = find_pin(wire.end_pin);

        node.add_pin(start);
        node.add_pin(end);
        node.calculate_state();

        nodes.push_back(node);
    }
}

void Circuit::run_simulation() {
    running = true;

    for (Component* comp : components) {
        if (comp != nullptr) {
            comp->update_pins();
        }
    }

    update_all_nodes();
}

std::string Circuit::save_to_json() const {
    json data;
    data["running"] = running;
    data["components"] = json::array();
    data["wires"] = json::array();

    for (Component* comp : components) {
        if (comp == nullptr) {
            continue;
        }

        vector2d pos = comp->get_position();

        data["components"].push_back({
            {"name", comp->get_name()},
            {"type", comp->get_type()},
            {"x", pos.x},
            {"y", pos.y},
            {"rotation", comp->get_rotation()},
            {"flip_h", comp->is_flip_h()},
            {"flip_v", comp->is_flip_v()}
        });
    }

    for (const Wire& wire : wires) {
        data["wires"].push_back({
            {"id", wire.id},
            {"start_pin", wire.start_pin},
            {"end_pin", wire.end_pin}
        });
    }

    return data.dump(4);
}

void Circuit::load_from_json(const std::string& data) {
    wires.clear();
    nodes.clear();

    json circuitdata = json::parse(data);
    running = circuitdata.value("running", false);

    // felan component factory nadarim va faqat wire ha load mishan
    for (const auto& item : circuitdata["wires"]) {
        wires.emplace_back(
            item.value("id", ""),
            item.value("start_pin", ""),
            item.value("end_pin", ""));
    }

    update_all_nodes();
}

std::vector<Component*> Circuit::get_components() const {
    return components;
}

std::vector<Wire> Circuit::get_wires() const {
    return wires;
}

std::vector<Node> Circuit::get_nodes() const {
    return nodes;
}

bool Circuit::is_running() const {
    return running;
}

void Circuit::stop() {
    running = false;
    nodes.clear();
}

Pin* Circuit::find_pin(const std::string& pin_id) const {
    for (Component* comp : components) {
        if (comp == nullptr) {
            continue;
        }

        std::vector<Pin>& comp_pins = comp->get_pins();
        for (Pin& pin : comp_pins) {
            std::string full_id = comp->get_name() + "." + pin.get_name();

            if (full_id == pin_id) {
                return &pin;
            }
        }
    }

    return nullptr;
}
