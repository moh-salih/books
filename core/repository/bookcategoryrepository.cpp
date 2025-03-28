#include "bookcategoryrepository.h"


BookCategoryRepository::BookCategoryRepository(const QSqlDatabase& db, QObject* parent)
    : QObject(parent), m_db(db) {}

bool BookCategoryRepository::createTable() const {
    QSqlQuery query(m_db);
    return query.exec(
        "CREATE TABLE IF NOT EXISTS book_category ("
        "book_id INTEGER NOT NULL,"
        "category_id INTEGER NOT NULL,"
        "PRIMARY KEY (book_id, category_id),"
        "FOREIGN KEY (book_id) REFERENCES books(id) ON DELETE CASCADE,"
        "FOREIGN KEY (category_id) REFERENCES categories(id) ON DELETE CASCADE"
        ")"
        );
}

bool BookCategoryRepository::addBookToCategory(int bookId, int categoryId) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO book_category (book_id, category_id) VALUES (?, ?)");
    query.addBindValue(bookId);
    query.addBindValue(categoryId);
    return query.exec();
}

bool BookCategoryRepository::removeBookFromCategory(int bookId, int categoryId) {
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM book_category WHERE book_id = ? AND category_id = ?");
    query.addBindValue(bookId);
    query.addBindValue(categoryId);
    return query.exec();
}

QList<int> BookCategoryRepository::getCategoriesForBook(int bookId) const {
    QList<int> categories;
    QSqlQuery query(m_db);
    query.prepare("SELECT category_id FROM book_category WHERE book_id = ?");
    query.addBindValue(bookId);

    if (query.exec()) {
        while (query.next()) {
            categories.append(query.value(0).toInt());
        }
    }
    return categories;
}

QList<int> BookCategoryRepository::getBooksForCategory(int categoryId) const {
    QList<int> books;
    QSqlQuery query(m_db);
    query.prepare("SELECT book_id FROM book_category WHERE category_id = ?");
    query.addBindValue(categoryId);

    if (query.exec()) {
        while (query.next()) {
            books.append(query.value(0).toInt());
        }
    }
    return books;
}

bool BookCategoryRepository::bookHasCategory(int bookId, int categoryId) const {
    QSqlQuery query(m_db);
    query.prepare("SELECT 1 FROM book_category WHERE book_id = ? AND category_id = ? LIMIT 1");
    query.addBindValue(bookId);
    query.addBindValue(categoryId);
    return query.exec() && query.next();
}

void BookCategoryRepository::clear() {
    QSqlQuery query(m_db);
    query.exec("DELETE FROM book_category");
}
