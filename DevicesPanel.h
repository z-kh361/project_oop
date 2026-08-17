#ifndef DEVICES_PANEL_H
#define DEVICES_PANEL_H

#include <QListWidget>
#include <QPushButton>
#include <QWidget>

#include <functional>

class DevicesPanel : public QWidget {
private:
    QListWidget* list_widget_;
    QPushButton* clear_button_;
    std::function<void(const QString&)> device_selected_callback_;
    std::function<void(const QString&)> device_removed_callback_;

    // row widget ba name va delete button misaze
    QWidget* create_device_row(const QString& name);

public:
    // devices panel jadid misaze
    explicit DevicesPanel(QWidget* parent = nullptr);

    // device jadid be list ezafe mikone
    void add_device(const QString& name);

    // device ro ba index hazf mikone
    void remove_device(int index);

    // hame device ha ro hazf mikone
    void clear_all();

    // device selected ro mide
    QString get_selected_device() const;

    // callback entekhab device ro set mikone
    void set_device_selected_callback(std::function<void(const QString&)> callback);

    // callback hazf device ro set mikone
    void set_device_removed_callback(std::function<void(const QString&)> callback);
};

#endif
