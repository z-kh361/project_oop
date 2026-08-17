#include "LogicGates.h"

namespace {
bool is_bad_input(logicstate state) {
    return state == logicstate::floating ||
           state == logicstate::undefined;
}
}

LogicGate::LogicGate(const std::string& name,
                     const std::string& type,
                     const vector2d& position)
    : Component(name, type, position),
      propagation_delay_(10),
      output_state_(logicstate::low) {}

void LogicGate::read_input_states(int input_count) {
    input_states_.clear();

    for (int i = 0; i < input_count && i < static_cast<int>(pins.size()); ++i) {
        input_states_.push_back(pins[i].get_state());
    }
}

void LogicGate::update() {
    int output_index = static_cast<int>(pins.size()) - 1;
    read_input_states(output_index);
    output_state_ = compute_output(input_states_);

    if (output_index >= 0) {
        pins[output_index].set_state(output_state_);
    }
}

std::vector<std::pair<std::string, std::string>> LogicGate::get_properties() const {
    return {
        {"name", name},
        {"propagation_delay", std::to_string(propagation_delay_)}
    };
}

void LogicGate::set_property(const std::string& key, const std::string& value) {
    if (key == "propagation_delay" || key == "Propagation Delay") {
        propagation_delay_ = std::stoi(value);
        return;
    }

    Component::set_property(key == "Name" ? "name" : key, value);
}

ANDGate::ANDGate(const std::string& name, const vector2d& position)
    : LogicGate(name, "AND", position) {
    pins.emplace_back("In1", position);
    pins.emplace_back("In2", position);
    pins.emplace_back("Out", position);
    update_pins();
    update();
}

void ANDGate::update_pins() {
    pins[0].set_position(vector2d(position.x - 20.0f, position.y - 8.0f));
    pins[1].set_position(vector2d(position.x - 20.0f, position.y + 8.0f));
    pins[2].set_position(vector2d(position.x + 20.0f, position.y));
}

logicstate ANDGate::compute_output(const std::vector<logicstate>& inputs) {
    for (logicstate state : inputs) {
        if (is_bad_input(state)) {
            return logicstate::undefined;
        }
        if (state == logicstate::low) {
            return logicstate::low;
        }
    }

    return logicstate::high;
}

ORGate::ORGate(const std::string& name, const vector2d& position)
    : LogicGate(name, "OR", position) {
    pins.emplace_back("In1", position);
    pins.emplace_back("In2", position);
    pins.emplace_back("Out", position);
    update_pins();
    update();
}

void ORGate::update_pins() {
    pins[0].set_position(vector2d(position.x - 20.0f, position.y - 8.0f));
    pins[1].set_position(vector2d(position.x - 20.0f, position.y + 8.0f));
    pins[2].set_position(vector2d(position.x + 20.0f, position.y));
}

logicstate ORGate::compute_output(const std::vector<logicstate>& inputs) {
    for (logicstate state : inputs) {
        if (is_bad_input(state)) {
            return logicstate::undefined;
        }
        if (state == logicstate::high) {
            return logicstate::high;
        }
    }

    return logicstate::low;
}

NOTGate::NOTGate(const std::string& name, const vector2d& position)
    : LogicGate(name, "NOT", position) {
    pins.emplace_back("In", position);
    pins.emplace_back("Out", position);
    update_pins();
    update();
}

void NOTGate::update_pins() {
    pins[0].set_position(vector2d(position.x - 20.0f, position.y));
    pins[1].set_position(vector2d(position.x + 20.0f, position.y));
}

logicstate NOTGate::compute_output(const std::vector<logicstate>& inputs) {
    if (inputs.empty() || is_bad_input(inputs[0])) {
        return logicstate::undefined;
    }

    return inputs[0] == logicstate::high ? logicstate::low : logicstate::high;
}

NANDGate::NANDGate(const std::string& name, const vector2d& position)
    : LogicGate(name, "NAND", position) {
    pins.emplace_back("In1", position);
    pins.emplace_back("In2", position);
    pins.emplace_back("Out", position);
    update_pins();
    update();
}

void NANDGate::update_pins() {
    pins[0].set_position(vector2d(position.x - 20.0f, position.y - 8.0f));
    pins[1].set_position(vector2d(position.x - 20.0f, position.y + 8.0f));
    pins[2].set_position(vector2d(position.x + 20.0f, position.y));
}

logicstate NANDGate::compute_output(const std::vector<logicstate>& inputs) {
    for (logicstate state : inputs) {
        if (is_bad_input(state)) {
            return logicstate::undefined;
        }
        if (state == logicstate::low) {
            return logicstate::high;
        }
    }

    return logicstate::low;
}

XORGate::XORGate(const std::string& name, const vector2d& position)
    : LogicGate(name, "XOR", position) {
    pins.emplace_back("In1", position);
    pins.emplace_back("In2", position);
    pins.emplace_back("Out", position);
    update_pins();
    update();
}

void XORGate::update_pins() {
    pins[0].set_position(vector2d(position.x - 20.0f, position.y - 8.0f));
    pins[1].set_position(vector2d(position.x - 20.0f, position.y + 8.0f));
    pins[2].set_position(vector2d(position.x + 20.0f, position.y));
}

logicstate XORGate::compute_output(const std::vector<logicstate>& inputs) {
    if (inputs.size() < 2) {
        return logicstate::undefined;
    }

    for (logicstate state : inputs) {
        if (is_bad_input(state)) {
            return logicstate::undefined;
        }
    }

    return inputs[0] != inputs[1] ? logicstate::high : logicstate::low;
}

DFlipFlop::DFlipFlop(const std::string& name, const vector2d& position)
    : LogicGate(name, "DFF", position),
      last_clk_state_(logicstate::low),
      q_state_(logicstate::low),
      qbar_state_(logicstate::high) {
    pins.emplace_back("D", position);
    pins.emplace_back("CLK", position);
    pins.emplace_back("Q", position);
    pins.emplace_back("Qbar", position);
    update_pins();
}

void DFlipFlop::update_pins() {
    pins[0].set_position(vector2d(position.x - 20.0f, position.y - 8.0f));
    pins[1].set_position(vector2d(position.x - 20.0f, position.y + 8.0f));
    pins[2].set_position(vector2d(position.x + 20.0f, position.y - 8.0f));
    pins[3].set_position(vector2d(position.x + 20.0f, position.y + 8.0f));
    pins[2].set_state(q_state_);
    pins[3].set_state(qbar_state_);
}

logicstate DFlipFlop::compute_output(const std::vector<logicstate>& inputs) {
    if (inputs.size() < 2 || is_bad_input(inputs[0]) || is_bad_input(inputs[1])) {
        return logicstate::undefined;
    }

    if (last_clk_state_ == logicstate::low && inputs[1] == logicstate::high) {
        return inputs[0];
    }

    return q_state_;
}

void DFlipFlop::update() {
    read_input_states(2);
    logicstate clk_state = input_states_.size() > 1 ? input_states_[1] : logicstate::undefined;
    q_state_ = compute_output(input_states_);

    if (q_state_ == logicstate::high) {
        qbar_state_ = logicstate::low;
    } else if (q_state_ == logicstate::low) {
        qbar_state_ = logicstate::high;
    } else {
        qbar_state_ = logicstate::undefined;
    }

    pins[2].set_state(q_state_);
    pins[3].set_state(qbar_state_);

    if (!is_bad_input(clk_state)) {
        last_clk_state_ = clk_state;
    }
}

logicstate DFlipFlop::get_pin_state(int index) const {
    if (index == 2) {
        return q_state_;
    }
    if (index == 3) {
        return qbar_state_;
    }

    return LogicGate::get_pin_state(index);
}
