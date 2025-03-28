#ifndef AUTHORREPOSITORY_H
#define AUTHORREPOSITORY_H
#include <QtSql>
#include "core/repository/interfaces/iAuthorrepository.h"
#include "core/data/author.h"
#include <QtCore>

class AuthorRepository : public QObject, public IAuthorRepository{
    Q_OBJECT
private:
    Author parseAuthorFromQuery(QSqlQuery& query) const;
public:
    explicit AuthorRepository(const QSqlDatabase& db, QObject * parent = nullptr);

    bool addAuthor(const Author& author) override;
    Author getAuthorById(int authorId) const override;
    QList<Author> getAllAuthors() const override;
    Author updateAuthor(const Author& author) override;
    bool deleteAuthor(int authorId) override;
    void clear() override;


    bool createTable() const override;
private:
    QSqlDatabase m_db;
};

#endif // AUTHORREPOSITORY_H
