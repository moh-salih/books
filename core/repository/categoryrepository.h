#ifndef CATEGORYREPOSITORY_H
#define CATEGORYREPOSITORY_H

#include "interfaces/ICategoryRepository.h"
#include <QtCore>
#include <QtSql>

class CategoryRepository: public QObject, public ICategoryRepository{
    Q_OBJECT
private:
    Category parseCategoryFromQuery(QSqlQuery &query) const;
public:
    explicit CategoryRepository(const QSqlDatabase& db, QObject * parent = nullptr);

    bool addCategory(const Category& category) override;
    Category getCategoryById(int categoryId) const override;
    QList<Category> getAllCategories() const override;
    Category updateCategory(const Category& category) override;
    bool deleteCategory(int categoryId) override;
    void clear() override;


    bool createTable() const override;
private:
    QSqlDatabase m_db;
};

#endif // CATEGORYREPOSITORY_H
