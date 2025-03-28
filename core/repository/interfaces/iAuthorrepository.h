#ifndef IAUTHORREPOSITORY_H
#define IAUTHORREPOSITORY_H
#include "iTableRepository.h"
#include "core/data/author.h"
#include <QList>

class IAuthorRepository: public ITableRepository{
public:
    virtual ~IAuthorRepository() = default;


    virtual bool addAuthor(const Author& Author) = 0;
    virtual Author getAuthorById(int AuthorId) const = 0;
    virtual QList<Author> getAllAuthors() const = 0;
    virtual Author updateAuthor(const Author& Author) = 0;
    virtual bool deleteAuthor(int authorId) = 0;
    virtual void clear() = 0;
};

#endif // IAUTHORREPOSITORY_H
