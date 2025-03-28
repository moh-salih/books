#ifndef FAVORITEBOOKREPOSITORY_H
#define FAVORITEBOOKREPOSITORY_H
#include "core/repository/interfaces/iFavoriteBookRepository.h"
#include "core/data/book.h"

#include <QObject>
#include <QtSql>

class FavoriteBookRepository: public QObject, public IFavoriteBookRepository{
private:
    Book parseBookFromQuery(QSqlQuery& query) const;
public:
    explicit FavoriteBookRepository(const QSqlDatabase& db, QObject* parent = nullptr);

    bool addFavorite(int bookId) override;
    bool removeFavorite(int bookId) override;
    bool removeFavorites() override;
    QList<Book> getAllFavorites() const override;
    bool isFavorite(int bookId) const override;

    bool createTable() const override;


private:
    QSqlDatabase m_db;
};

#endif // FAVORITEBOOKREPOSITORY_H
