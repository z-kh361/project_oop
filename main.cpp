#include "circuit.h"
#include "circuit_widget.h"
#include "resistor.h"

#include <QApplication>
#include <QMainWindow>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Test circuit with one resistor.
    Circuit circuit;
    circuit.add_component(new Resistor("R1", vector2d(200.0f, 300.0f)));

    QMainWindow window;
    window.setWindowTitle("Circuit Simulator - Qt");
    window.resize(900, 700);

    CircuitWidget* widget = new CircuitWidget(&circuit);
    window.setCentralWidget(widget);

    window.show();

    return app.exec();
}
