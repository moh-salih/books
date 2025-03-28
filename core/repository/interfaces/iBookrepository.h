#ifndef IBOOKREPOSITORY_H
#define IBOOKREPOSITORY_H

#include "iTableRepository.h"
#include "core/data/book.h"

#include <QList>

class IBookRepository: public ITableRepository{
public:
    virtual ~IBookRepository() = default;

    virtual bool addBook(const Book& book) = 0;
    virtual Book getBookById(int bookId) const = 0;
    virtual QList<Book> getAllBooks() const = 0;
    virtual Book updateBook(const Book& book) = 0;
    virtual bool deleteBook(int bookId) = 0;
    virtual void clear() = 0;
};

#endif // IBOOKREPOSITORY_H
