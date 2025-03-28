#ifndef IFAVORITEBOOKREPOSITORY_H
#define IFAVORITEBOOKREPOSITORY_H

#include <QList>

#include "iTableRepository.h"
#include "core/data/book.h"

class IFavoriteBookRepository: public ITableRepository{
public:
    virtual ~IFavoriteBookRepository() = default;

    virtual bool addFavorite(int bookId) = 0;
    virtual bool removeFavorite(int bookId) = 0;
    virtual bool removeFavorites() = 0;
    virtual QList<Book> getAllFavorites() const = 0;
    virtual bool isFavorite(int bookId) const = 0;

    virtual bool createTable() const = 0;
};

#endif // IFAVORITEBOOKREPOSITORY_H
