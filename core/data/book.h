#ifndef BOOK_H
#define BOOK_H
#include <QString>
#include <QDateTime>


struct Book {
    int id;
    int authorId;
    QString title;
    QDateTime createdAt;
    QDateTime updatedAt;
    QString filePath;
    QString coverImagePath;


    bool operator==(const Book& other) const{
        return this->id == other.id;
    }
};



#endif // BOOK_H
