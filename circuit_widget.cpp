#include "circuit_widget.h"

#include <algorithm>
#include <cmath>

CircuitWidget::CircuitWidget(QWidget* parent)
    : QWidget(parent),
      circuit_(nullptr),
      timer_(new QTimer(this)),
      zoom_level_(1.0f),
      view_offset_(0, 0),
      is_panning_(false),
      pan_start_(0, 0) {
    setWindowTitle("Circuit Simulator");
    resize(800, 600);
    setMouseTracking(true);

    connect(timer_, &QTimer::timeout, this, [this]() {
        update();
    });
    timer_->start(100);
}

CircuitWidget::CircuitWidget(Circuit* circuit, QWidget* parent)
    : CircuitWidget(parent) {
    set_circuit(circuit);
}

void CircuitWidget::set_circuit(Circuit* circuit) {
    circuit_ = circuit;
    update();
}

void CircuitWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillRect(rect(), QColor(245, 245, 245));

    draw_grid(painter);

    if (circuit_ == nullptr) {
        return;
    }

    for (Component* comp : circuit_->get_components()) {
        draw_component(painter, comp);
    }
}

void CircuitWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton) {
        is_panning_ = true;
        pan_start_ = event->position().toPoint();
        return;
    }

    if (event->button() != Qt::LeftButton || circuit_ == nullptr) {
        return;
    }

    vector2d world_pos = screen_to_world(event->position().toPoint());
    bool found = false;

    for (Component* comp : circuit_->get_components()) {
        if (comp != nullptr && comp->contains_point(world_pos)) {
            comp->select();
            found = true;
        } else if (comp != nullptr) {
            comp->deselect();
        }
    }

    Q_UNUSED(found);
    update();
}

void CircuitWidget::mouseMoveEvent(QMouseEvent* event) {
    QPoint current_pos = event->position().toPoint();

    if (is_panning_) {
        QPoint delta = current_pos - pan_start_;
        view_offset_ += delta;
        pan_start_ = current_pos;
    }

    if (circuit_ != nullptr) {
        vector2d world_pos = screen_to_world(current_pos);

        for (Component* comp : circuit_->get_components()) {
            if (comp == nullptr) {
                continue;
            }

            for (Pin& pin : comp->get_pins()) {
                pin.set_highlighted(pin.is_mouse_over(world_pos));
            }
        }
    }

    update();
}

void CircuitWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton) {
        is_panning_ = false;
        update();
    }
}

void CircuitWidget::wheelEvent(QWheelEvent* event) {
    if (event->angleDelta().y() > 0) {
        zoom_level_ *= 1.1f;
    } else {
        zoom_level_ *= 0.9f;
    }

    zoom_level_ = std::clamp(zoom_level_, 0.2f, 5.0f);
    update();
}

void CircuitWidget::draw_grid(QPainter& painter) {
    painter.setPen(QPen(QColor(215, 215, 215), 1));

    double step = 20.0 * zoom_level_;
    if (step < 4.0) {
        return;
    }

    double start_x = std::fmod(static_cast<double>(view_offset_.x()), step);
    double start_y = std::fmod(static_cast<double>(view_offset_.y()), step);

    if (start_x < 0.0) {
        start_x += step;
    }
    if (start_y < 0.0) {
        start_y += step;
    }

    for (double x = start_x; x <= width(); x += step) {
        painter.drawLine(static_cast<int>(x), 0, static_cast<int>(x), height());
    }

    for (double y = start_y; y <= height(); y += step) {
        painter.drawLine(0, static_cast<int>(y), width(), static_cast<int>(y));
    }
}

void CircuitWidget::draw_component(QPainter& painter, Component* comp) {
    if (comp == nullptr) {
        return;
    }

    QPoint center = world_to_screen(comp->get_position());
    int body_w = static_cast<int>(60.0f * zoom_level_);
    int body_h = static_cast<int>(30.0f * zoom_level_);
    QRect body(center.x() - body_w / 2, center.y() - body_h / 2, body_w, body_h);

    painter.setBrush(Qt::white);
    painter.setPen(QPen(comp->is_selected() ? QColor(30, 120, 220) : QColor(30, 30, 30), 2));
    painter.drawRect(body);

    painter.setPen(QPen(QColor(20, 20, 20), 1));
    painter.drawText(body.x(), body.y() - 6, QString::fromStdString(comp->get_display_name()));

    for (Pin& pin : comp->get_pins()) {
        draw_pin(painter, pin);
    }
}

void CircuitWidget::draw_pin(QPainter& painter, Pin& pin) {
    QPoint pos = world_to_screen(pin.get_position());
    int radius = std::max(3, static_cast<int>(4.0f * zoom_level_));

    QColor pin_color = pin.is_highlighted() ? QColor(255, 220, 0) : QColor(30, 30, 30);
    painter.setBrush(pin_color);
    painter.setPen(QPen(QColor(30, 30, 30), 1));
    painter.drawEllipse(pos, radius, radius);
}

QPoint CircuitWidget::world_to_screen(const vector2d& world_pos) const {
    int x = static_cast<int>(world_pos.x * zoom_level_) + view_offset_.x();
    int y = static_cast<int>(world_pos.y * zoom_level_) + view_offset_.y();

    return QPoint(x, y);
}

vector2d CircuitWidget::screen_to_world(const QPoint& screen_pos) const {
    float x = static_cast<float>(screen_pos.x() - view_offset_.x()) / zoom_level_;
    float y = static_cast<float>(screen_pos.y() - view_offset_.y()) / zoom_level_;

    return vector2d(x, y);
}
