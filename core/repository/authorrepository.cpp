#include "authorrepository.h"

AuthorRepository::AuthorRepository(const QSqlDatabase& db, QObject * parent): m_db(db), QObject(parent) {}

Author AuthorRepository::parseAuthorFromQuery(QSqlQuery &query) const{
    Author author;
    author.id = query.value("id").toInt();
    author.name = query.value("name").toString();
    author.createdAt = query.value("created_at").toDateTime();
    author.updatedAt = query.value("updated_at").toDateTime();
    author.imagePath = query.value("image_path").toString();
    return author;
}


bool AuthorRepository::addAuthor(const Author &author){
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO authors (name, image_path) VALUES (?, ?)");
    query.addBindValue(author.name);
    query.addBindValue(author.imagePath);
    return query.exec();
}

Author AuthorRepository::getAuthorById(int authorId) const{
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM authors WHERE id = ?");
    query.addBindValue(authorId);
    if(query.exec() && query.next()){
        return parseAuthorFromQuery(query);
    }else{
        return Author();
    }
}

QList<Author> AuthorRepository::getAllAuthors() const{
    QSqlQuery query(m_db);
    QList<Author> authors;
    if(query.exec("SELECT * FROM authors")){
        while(query.next()){
            Author author = parseAuthorFromQuery(query);
            authors.append(author);
        }
    }
    return authors;
}

Author AuthorRepository::updateAuthor(const Author &author){
    return author;
}

bool AuthorRepository::deleteAuthor(int authorId){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM authors WHERE id = ?");
    query.addBindValue(authorId);
    return query.exec();
}

void AuthorRepository::clear(){
    QSqlQuery query(m_db);
    query.exec("DELETE FROM authors");
}

bool AuthorRepository::createTable() const{
    QSqlQuery query(m_db);

    QString sql = QStringLiteral("CREATE TABLE IF NOT EXISTS authors ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "name TEXT,"
                                 "image_path TEXT,"
                                 "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                                 "updated_at DATETIME DEFAULT CURRENT_TIMESTAMP"
                                 ")");

    if (!query.exec(sql)) {
        qDebug() << "Error creating authors table:" << query.lastError().text();
        return false;
    }

    sql = QStringLiteral("CREATE TRIGGER IF NOT EXISTS update_author_updated_at "
                         "AFTER UPDATE ON authors "
                         "BEGIN "
                         "    UPDATE authors SET updated_at = CURRENT_TIMESTAMP WHERE id = OLD.id; "
                         "END;");

    if (!query.exec(sql)) {
        qDebug() << "Error creating authors trigger:" << query.lastError().text();
        return false;
    }

    return true;
}
