#include "favoritebookrepository.h"
#include "core/repository/bookrepository.h"
#include <QStringLiteral>


Book FavoriteBookRepository::parseBookFromQuery(QSqlQuery &query) const {
    Book book;

    book.id = query.value("id").toInt();
    book.authorId = query.value("author_id").toInt();

    book.title = query.value("title").toString();

    book.createdAt = query.value("created_at").toDateTime();
    book.updatedAt = query.value("updated_at").toDateTime();

    book.filePath = query.value("file_path").toString();
    book.coverImagePath = query.value("cover_image_path").toString();

    return book;
}

FavoriteBookRepository::FavoriteBookRepository(const QSqlDatabase &db, QObject *parent): QObject(parent), m_db(db){}

bool FavoriteBookRepository::addFavorite(int bookId){
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO favorites (book_id) VALUES (?)");
    query.addBindValue(bookId);

    if(!query.exec()){
        qDebug() << "Failed to add favorite: " << query.lastError().text();
        return false;
    }
    return true;
}

bool FavoriteBookRepository::removeFavorite(int bookId){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM favorites WHERE book_id = ?");
    query.addBindValue(bookId);

    if(!query.exec()){
        qDebug() << "Failed to delete favorite: " << query.lastError().text();
        return false;
    }
    return true;
}

bool FavoriteBookRepository::removeFavorites(){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM favorites");
    if(!query.exec()){
        qDebug() << "Failed to remove favorite books: " << query.lastError().text();
        return false;
    }
    return true;
}

QList<Book> FavoriteBookRepository::getAllFavorites() const {
    QList<Book> favoriteBooks;
    QSqlQuery query(m_db);


    QString sql = QStringLiteral(
        "SELECT "
        "b.id, b.title, b.file_path, b.author_id, b.updated_at, b.created_at, b.cover_image_path "
        "FROM favorites f "
        "JOIN books b ON f.book_id = b.id"
        );

    query.prepare(sql);

    if(!query.exec()){
        qDebug() << "Failed to fetch favorite books: " << query.lastError().text();
        return favoriteBooks;
    }

    while(query.next()){
        Book book = parseBookFromQuery(query);
        qDebug() << "getAllFavorites()::BEGIN\n";
        qDebug() << "id: " << book.id << ", title: " << book.title;
        qDebug() << "getAllFavorites()::END\n\n";
        favoriteBooks.append(book);
    }

    return favoriteBooks;
}

bool FavoriteBookRepository::isFavorite(int bookId) const {
    QSqlQuery query(m_db);

    query.prepare("SELECT 1 FROM favorites WHERE book_id = ?");
    query.addBindValue(bookId);

    if(!query.exec()){
        qDebug() << "Failed to check if is favorite: " << query.lastError().text();
        return false;
    }

    return query.next();
}

bool FavoriteBookRepository::createTable() const {
    QSqlQuery query(m_db);
    QString sql = QStringLiteral("CREATE TABLE IF NOT EXISTS favorites ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "book_id INTEGER UNIQUE,"
                         "FOREIGN KEY (book_id) REFERENCES books(id) ON DELETE CASCADE)");

    query.prepare(sql);
    if(!query.exec()){
        qDebug() << "Failed to create favorites table: " << query.lastError().text();
        return false;
    }
    return true;
}
