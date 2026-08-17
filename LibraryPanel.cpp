#include "LibraryPanel.h"

#include <QHeaderView>
#include <QPainter>
#include <QPixmap>
#include <QVBoxLayout>

#include <utility>

namespace {
constexpr int ComponentNameRole = Qt::UserRole + 1;
}

LibraryPanel::LibraryPanel(LibraryModel* model, QWidget* parent)
    : QWidget(parent),
      model_(model),
      tree_view_(new QTreeView(this)),
      search_edit_(new QLineEdit(this)),
      preview_label_(new QLabel(this)),
      add_button_(new QPushButton("Add to Devices", this)),
      tree_model_(new QStandardItemModel(this)),
      selected_component_("") {
    search_edit_->setPlaceholderText("Search components...");

    tree_view_->setModel(tree_model_);
    tree_view_->setHeaderHidden(true);
    tree_view_->setEditTriggers(QAbstractItemView::NoEditTriggers);

    preview_label_->setMinimumHeight(90);
    preview_label_->setAlignment(Qt::AlignCenter);
    preview_label_->setFrameShape(QFrame::StyledPanel);

    add_button_->setEnabled(false);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(search_edit_);
    layout->addWidget(tree_view_, 1);
    layout->addWidget(preview_label_);
    layout->addWidget(add_button_);
    setLayout(layout);

    connect(search_edit_, &QLineEdit::textChanged,
            this, &LibraryPanel::on_search_changed);
    connect(tree_view_->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &LibraryPanel::on_item_selected);
    connect(add_button_, &QPushButton::clicked,
            this, &LibraryPanel::on_add_clicked);

    setup_tree();
    update_preview("");
}

void LibraryPanel::setup_tree() {
    tree_model_->clear();
    tree_model_->setHorizontalHeaderLabels({"Components"});

    if (model_ == nullptr) {
        return;
    }

    for (const std::string& category : model_->get_all_categories()) {
        QStandardItem* category_item = new QStandardItem(QString::fromStdString(category));
        category_item->setSelectable(false);

        for (const ComponentInfo& component : model_->get_by_category(category)) {
            QStandardItem* component_item = new QStandardItem(QString::fromStdString(component.name));
            component_item->setData(QString::fromStdString(component.name), ComponentNameRole);
            category_item->appendRow(component_item);
        }

        tree_model_->appendRow(category_item);
    }

    tree_view_->expandAll();
}

void LibraryPanel::set_add_to_devices_callback(std::function<void(const QString&)> callback) {
    add_to_devices_callback_ = std::move(callback);
}

void LibraryPanel::on_search_changed(const QString& text) {
    selected_component_.clear();
    add_button_->setEnabled(false);
    update_preview("");

    if (text.trimmed().isEmpty()) {
        setup_tree();
        return;
    }

    tree_model_->clear();
    tree_model_->setHorizontalHeaderLabels({"Search Results"});

    if (model_ == nullptr) {
        return;
    }

    for (const ComponentInfo& component : model_->search(text.toStdString())) {
        QString item_text = QString::fromStdString(component.name + " (" + component.category + ")");
        QStandardItem* component_item = new QStandardItem(item_text);
        component_item->setData(QString::fromStdString(component.name), ComponentNameRole);
        tree_model_->appendRow(component_item);
    }
}

void LibraryPanel::on_item_selected(const QModelIndex& index) {
    if (!index.isValid()) {
        selected_component_.clear();
        add_button_->setEnabled(false);
        update_preview("");
        return;
    }

    QString component_name = index.data(ComponentNameRole).toString();
    selected_component_ = component_name;
    add_button_->setEnabled(!selected_component_.isEmpty());
    update_preview(selected_component_);
}

void LibraryPanel::on_add_clicked() {
    if (selected_component_.isEmpty()) {
        return;
    }

    if (add_to_devices_callback_) {
        add_to_devices_callback_(selected_component_);
    }
}

void LibraryPanel::update_preview(const QString& component_name) {
    QPixmap pixmap(220, 80);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(Qt::white);
    painter.setPen(QPen(QColor(120, 120, 120), 2));
    painter.drawRect(40, 20, 140, 40);

    painter.setPen(QColor(30, 30, 30));
    QString text = component_name.isEmpty() ? "No component" : component_name;
    painter.drawText(pixmap.rect(), Qt::AlignCenter, text);

    preview_label_->setPixmap(pixmap);
}
