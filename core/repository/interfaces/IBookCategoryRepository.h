#ifndef IBOOKCATEGORYREPOSITORY_H
#define IBOOKCATEGORYREPOSITORY_H


#include "iTableRepository.h"
#include <QList>

class IBookCategoryRepository : public ITableRepository {
public:
    virtual ~IBookCategoryRepository() = default;

    virtual bool addBookToCategory(int bookId, int categoryId) = 0;
    virtual bool removeBookFromCategory(int bookId, int categoryId) = 0;
    virtual QList<int> getCategoriesForBook(int bookId) const = 0;
    virtual QList<int> getBooksForCategory(int categoryId) const = 0;
    virtual bool bookHasCategory(int bookId, int categoryId) const = 0;
    virtual void clear() = 0;
};

#endif // IBOOKCATEGORYREPOSITORY_H
