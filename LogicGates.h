#ifndef LOGIC_GATES_H
#define LOGIC_GATES_H

#include "component.h"

class LogicGate : public Component {
protected:
    int propagation_delay_;
    std::vector<logicstate> input_states_;
    logicstate output_state_;

    // input pin ha ro mikhoone
    void read_input_states(int input_count);

public:
    // gate jadid misaze
    LogicGate(const std::string& name,
              const std::string& type,
              const vector2d& position);

    // output ro hesab mikone
    virtual logicstate compute_output(const std::vector<logicstate>& inputs) = 0;

    // state gate ro update mikone
    void update() override;

    // property ha ro ba meghdar namayesh mide
    std::vector<std::pair<std::string, std::string>> get_properties() const override;

    // property ro avaz mikone
    void set_property(const std::string& key, const std::string& value) override;
};

class ANDGate : public LogicGate {
public:
    ANDGate(const std::string& name, const vector2d& position);
    void update_pins() override;
    logicstate compute_output(const std::vector<logicstate>& inputs) override;
};

class ORGate : public LogicGate {
public:
    ORGate(const std::string& name, const vector2d& position);
    void update_pins() override;
    logicstate compute_output(const std::vector<logicstate>& inputs) override;
};

class NOTGate : public LogicGate {
public:
    NOTGate(const std::string& name, const vector2d& position);
    void update_pins() override;
    logicstate compute_output(const std::vector<logicstate>& inputs) override;
};

class NANDGate : public LogicGate {
public:
    NANDGate(const std::string& name, const vector2d& position);
    void update_pins() override;
    logicstate compute_output(const std::vector<logicstate>& inputs) override;
};

class XORGate : public LogicGate {
public:
    XORGate(const std::string& name, const vector2d& position);
    void update_pins() override;
    logicstate compute_output(const std::vector<logicstate>& inputs) override;
};

class DFlipFlop : public LogicGate {
private:
    logicstate last_clk_state_;
    logicstate q_state_;
    logicstate qbar_state_;

public:
    DFlipFlop(const std::string& name, const vector2d& position);
    void update_pins() override;
    logicstate compute_output(const std::vector<logicstate>& inputs) override;
    void update() override;
    logicstate get_pin_state(int index) const override;
};

#endif
