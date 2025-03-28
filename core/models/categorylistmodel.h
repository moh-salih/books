#ifndef CATEGORYLISTMODEL_H
#define CATEGORYLISTMODEL_H

#include <QAbstractListModel>
#include "core/repository/interfaces/ICategoryRepository.h"

class CategoryListModel : public QAbstractListModel{
    Q_OBJECT
public:
    explicit CategoryListModel(ICategoryRepository * categoryRepository ,QObject *parent = nullptr): m_categoryRepository(categoryRepository), QAbstractListModel(parent){}


    enum CategoryRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        ImagePathRole,
        CreatedAtRole,
        UpdatedAtRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void refreshCategories(); // Refresh categories from database
    Q_INVOKABLE void addCategory(const QString &name, const QString &imagePath);
    Q_INVOKABLE void deleteCategory(int categoryId);

private:
    ICategoryRepository * m_categoryRepository;
    QList<Category> m_categories;
};

#endif // CATEGORYLISTMODEL_H
