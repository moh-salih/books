#include "bookrepository.h"


Book BookRepository::parseBookFromQuery(QSqlQuery& query) const {
    Book book;
    book.id = query.value("id").toInt();
    book.title = query.value("title").toString();
    book.authorId = query.value("author_id").toInt();
    book.createdAt = query.value("created_at").toDateTime();
    book.updatedAt = query.value("updated_at").toDateTime();
    book.coverImagePath = query.value("cover_image_path").toString();
    book.filePath = query.value("file_path").toString();

    qDebug() << "GETTING THE BOOK:::: " << book.title;

    return book;
}

BookRepository::BookRepository(const QSqlDatabase& db, QObject * parent): m_db(db), QObject(parent) {}

bool BookRepository::addBook(const Book &book){
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO books (title, author_id, cover_image_path, file_path) VALUES (?, ?, ?, ?)");
    query.addBindValue(book.title);
    query.addBindValue(book.authorId);
    query.addBindValue(book.coverImagePath);
    query.addBindValue(book.filePath);
    return query.exec();
}

Book BookRepository::getBookById(int bookId) const{
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM books WHERE id = ?");
    query.addBindValue(bookId);
    if(query.exec() && query.next()){
        return parseBookFromQuery(query);
    }else{
        return Book();
    }
}

QList<Book> BookRepository::getAllBooks() const{
    QSqlQuery query(m_db);
    QList<Book> books;
    if(query.exec("SELECT * FROM books")){
        while(query.next()){
            Book book = parseBookFromQuery(query);
            books.append(book);
        }
    }
    return books;
}

Book BookRepository::updateBook(const Book &book)
{
    return book;
}

bool BookRepository::deleteBook(int bookId){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM books WHERE id = ?");
    query.addBindValue(bookId);
    return query.exec();
}

void BookRepository::clear(){
    QSqlQuery query(m_db);
    query.exec("DELETE FROM books");
}

bool BookRepository::createTable() const{
    QSqlQuery query(m_db);

    QString sql = QStringLiteral("CREATE TABLE IF NOT EXISTS books ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "title TEXT,"
                                 "author_id INTEGER,"
                                 "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                                 "updated_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                                 "cover_image_path TEXT,"
                                 "file_path TEXT,"
                                 "FOREIGN KEY(author_id) REFERENCES authors(id)"
                                 ")");
    if(!query.exec(sql)){
        return false;
    }
    sql = QStringLiteral("CREATE TRIGGER IF NOT EXISTS update_book_updated_at "
                         "AFTER UPDATE ON books "
                         "BEGIN "
                         "UPDATE books SET updated_at = CURRENT_TIMESTAMP WHERE id = OLD.id; "
                         "END;");
    if(!query.exec(sql)){
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}
