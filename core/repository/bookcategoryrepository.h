#ifndef BOOKCATEGORYREPOSITORY_H
#define BOOKCATEGORYREPOSITORY_H

#include "interfaces/IBookCategoryRepository.h"

#include <QtCore>
#include <QtSql>

class BookCategoryRepository : public QObject, public IBookCategoryRepository {
    Q_OBJECT
public:
    explicit BookCategoryRepository(const QSqlDatabase& db, QObject* parent = nullptr);

    bool addBookToCategory(int bookId, int categoryId) override;
    bool removeBookFromCategory(int bookId, int categoryId) override;
    QList<int> getCategoriesForBook(int bookId) const override;
    QList<int> getBooksForCategory(int categoryId) const override;
    bool bookHasCategory(int bookId, int categoryId) const override;
    void clear() override;

    bool createTable() const override;

private:
    QSqlDatabase m_db;
};
#endif // BOOKCATEGORYREPOSITORY_H
