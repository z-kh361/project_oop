#include "DevicesPanel.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include <utility>

DevicesPanel::DevicesPanel(QWidget* parent)
    : QWidget(parent),
      list_widget_(new QListWidget(this)),
      clear_button_(new QPushButton("Clear All", this)) {
    QLabel* title_label = new QLabel("Devices", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(title_label);
    layout->addWidget(list_widget_, 1);
    layout->addWidget(clear_button_);
    setLayout(layout);

    connect(clear_button_, &QPushButton::clicked,
            this, &DevicesPanel::clear_all);
    connect(list_widget_, &QListWidget::itemDoubleClicked,
            this, [this](QListWidgetItem* item) {
                if (item == nullptr) {
                    return;
                }

                if (device_selected_callback_) {
                    device_selected_callback_(item->data(Qt::UserRole).toString());
                }
            });
}

void DevicesPanel::add_device(const QString& name) {
    if (name.isEmpty()) {
        return;
    }

    QListWidgetItem* item = new QListWidgetItem(list_widget_);
    item->setData(Qt::UserRole, name);
    item->setSizeHint(QSize(150, 34));
    list_widget_->addItem(item);
    list_widget_->setItemWidget(item, create_device_row(name));
}

void DevicesPanel::remove_device(int index) {
    if (index < 0 || index >= list_widget_->count()) {
        return;
    }

    QListWidgetItem* item = list_widget_->takeItem(index);
    QString name = item->data(Qt::UserRole).toString();
    delete item;

    if (device_removed_callback_) {
        device_removed_callback_(name);
    }
}

void DevicesPanel::clear_all() {
    while (list_widget_->count() > 0) {
        remove_device(0);
    }
}

QString DevicesPanel::get_selected_device() const {
    QListWidgetItem* item = list_widget_->currentItem();
    if (item == nullptr) {
        return "";
    }

    return item->data(Qt::UserRole).toString();
}

QWidget* DevicesPanel::create_device_row(const QString& name) {
    QWidget* row_widget = new QWidget(list_widget_);
    QLabel* name_label = new QLabel(name, row_widget);
    QPushButton* remove_button = new QPushButton("X", row_widget);
    remove_button->setFixedWidth(28);

    QHBoxLayout* row_layout = new QHBoxLayout(row_widget);
    row_layout->setContentsMargins(6, 2, 2, 2);
    row_layout->addWidget(name_label, 1);
    row_layout->addWidget(remove_button);
    row_widget->setLayout(row_layout);

    connect(remove_button, &QPushButton::clicked, this, [this, row_widget]() {
        for (int i = 0; i < list_widget_->count(); ++i) {
            if (list_widget_->itemWidget(list_widget_->item(i)) == row_widget) {
                remove_device(i);
                return;
            }
        }
    });

    return row_widget;
}

void DevicesPanel::set_device_selected_callback(std::function<void(const QString&)> callback) {
    device_selected_callback_ = std::move(callback);
}

void DevicesPanel::set_device_removed_callback(std::function<void(const QString&)> callback) {
    device_removed_callback_ = std::move(callback);
}
