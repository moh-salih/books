#ifndef ICATEGORYREPOSITORY_H
#define ICATEGORYREPOSITORY_H


#include "iTableRepository.h"
#include "core/data/category.h"
#include <QList>

class ICategoryRepository: public ITableRepository{
public:
    virtual ~ICategoryRepository() = default;

    virtual bool addCategory(const Category& Category) = 0;
    virtual Category getCategoryById(int CategoryId) const = 0;
    virtual QList<Category> getAllCategories() const = 0;
    virtual Category updateCategory(const Category& Category) = 0;
    virtual bool deleteCategory(int CategoryId) = 0;
    virtual void clear() = 0;
};

#endif // ICATEGORYREPOSITORY_H
