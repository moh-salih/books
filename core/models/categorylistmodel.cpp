#include "categorylistmodel.h"


int CategoryListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_categories.size();
}

QVariant CategoryListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_categories.size())
        return QVariant();

    const Category &category = m_categories[index.row()];
    switch (role) {
    case IdRole: return category.id;
    case NameRole: return category.name;
    case ImagePathRole: return category.imagePath;
    case CreatedAtRole: return category.createdAt;
    case UpdatedAtRole: return category.updatedAt;
    default: return QVariant();
    }
}

QHash<int, QByteArray> CategoryListModel::roleNames() const {
    return {
        {IdRole, "id"},
        {NameRole, "name"},
        {ImagePathRole, "imagePath"},
        {CreatedAtRole, "createdAt"},
        {UpdatedAtRole, "updatedAt"}
    };
}

void CategoryListModel::refreshCategories() {
    beginResetModel();
    m_categories = m_categoryRepository->getAllCategories();
    endResetModel();
}

void CategoryListModel::addCategory(const QString &name, const QString &imagePath) {
    Category newCategory;
    newCategory.name = name;
    newCategory.imagePath = imagePath;

    if (m_categoryRepository->addCategory(newCategory)) {
        refreshCategories();
    }
}

void CategoryListModel::deleteCategory(int categoryId) {
    if (m_categoryRepository->deleteCategory(categoryId)) {
        refreshCategories();
    }
}
