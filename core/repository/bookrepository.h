#ifndef BOOKREPOSITORY_H
#define BOOKREPOSITORY_H

#include "core/repository/interfaces/iBookrepository.h"
#include "core/database/databasemanager.h"

class BookRepository : public QObject, public IBookRepository{
    Q_OBJECT
private:
    Book parseBookFromQuery(QSqlQuery& query) const;
public:
    explicit BookRepository(const QSqlDatabase& db, QObject * parent = nullptr);

    bool addBook(const Book& book) override;
    Book getBookById(int bookId) const override;
    QList<Book> getAllBooks() const override;
    Book updateBook(const Book& book) override;
    bool deleteBook(int bookId) override;
    void clear() override;


    bool createTable() const override;
private:
    QSqlDatabase m_db;
};

#endif // BOOKREPOSITORY_H
