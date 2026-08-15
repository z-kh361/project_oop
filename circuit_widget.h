#ifndef CIRCUIT_WIDGET_H
#define CIRCUIT_WIDGET_H

#include "circuit.h"
#include "component.h"
#include "pin.h"
#include "types.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QTimer>
#include <QWheelEvent>
#include <QWidget>

// Qt canvas for drawing and interacting with circuit.
class CircuitWidget : public QWidget {
private:
    Circuit* circuit_;
    QTimer* timer_;
    float zoom_level_;
    QPoint view_offset_;
    bool is_panning_;
    QPoint pan_start_;

protected:
    // Redraws the canvas.
    void paintEvent(QPaintEvent* event) override;

    // Handles select and pan start.
    void mousePressEvent(QMouseEvent* event) override;

    // Handles panning and pin highlight.
    void mouseMoveEvent(QMouseEvent* event) override;

    // Stops panning.
    void mouseReleaseEvent(QMouseEvent* event) override;

    // Handles zoom.
    void wheelEvent(QWheelEvent* event) override;

public:
    // widget jadid misaze
    explicit CircuitWidget(QWidget* parent = nullptr);

    // widget ba circuit misaze
    explicit CircuitWidget(Circuit* circuit, QWidget* parent = nullptr);

    // circuit ro set mikone
    void set_circuit(Circuit* circuit);

    // grid ro mikoshe
    void draw_grid(QPainter& painter);

    // component ro mikoshe
    void draw_component(QPainter& painter, Component* comp);

    // pin ro mikoshe
    void draw_pin(QPainter& painter, Pin& pin);

    // world ro screen mikone
    QPoint world_to_screen(const vector2d& world_pos) const;

    // screen ro world mikone
    vector2d screen_to_world(const QPoint& screen_pos) const;
};

#endif
