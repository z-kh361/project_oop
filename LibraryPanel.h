#ifndef LIBRARY_PANEL_H
#define LIBRARY_PANEL_H

#include "LibraryModel.h"

#include <QLabel>
#include <QLineEdit>
#include <QModelIndex>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTreeView>
#include <QWidget>

#include <functional>

class LibraryPanel : public QWidget {
private:
    LibraryModel* model_;
    QTreeView* tree_view_;
    QLineEdit* search_edit_;
    QLabel* preview_label_;
    QPushButton* add_button_;
    QStandardItemModel* tree_model_;
    QString selected_component_;
    std::function<void(const QString&)> add_to_devices_callback_;

    // preview sade ba rectangle va name misaze
    void update_preview(const QString& component_name);

public:
    // panel ro ba model misaze
    explicit LibraryPanel(LibraryModel* model, QWidget* parent = nullptr);

    // tree category ha ro misaze
    void setup_tree();

    // callback ezafe kardan be devices ro set mikone
    void set_add_to_devices_callback(std::function<void(const QString&)> callback);

public:
    // filter search ro update mikone
    void on_search_changed(const QString& text);

    // preview item selected ro update mikone
    void on_item_selected(const QModelIndex& index);

    // component selected ro be devices mifreste
    void on_add_clicked();
};

#endif
