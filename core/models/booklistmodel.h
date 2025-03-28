#ifndef BOOKLISTMODEL_H
#define BOOKLISTMODEL_H

#include "core/data/book.h"
#include "core/repository/bookrepository.h"
#include "core/repository/favoritebookrepository.h"
#include "basebooklistmodel.h"

class BookListModel : public BaseBookListModel {
    Q_OBJECT
public:
    explicit BookListModel(IBookRepository* bookRepo, IFavoriteBookRepository * favBookRepo, QObject* parent = nullptr): BaseBookListModel(parent),
        m_bookRepository(bookRepo), m_favoriteBookRepository(favBookRepo){}

    Q_INVOKABLE void updateDatabase(const QList<QString>& pdfs){
        if(pdfs.isEmpty()) return;

        beginInsertRows(QModelIndex(), rowCount(), rowCount());

        foreach (QString pdf, pdfs) {
            QFileInfo pdfFileInfo(pdf);

            Book book;
            book.title = pdfFileInfo.fileName();
            book.authorId = 1;
            book.filePath = pdf;
            m_bookRepository->addBook(book);
        }

        endInsertRows();
        refreshBooks();
        emit rowCountChanged();
    }

    Q_INVOKABLE void clearDatabase(){
        beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
        m_bookRepository->clear();
        bookItems.clear();
        endRemoveRows();
        emit rowCountChanged();
    }


    // Q_INVOKABLE bool addBookToFavorites(int index){
    //     if(index >= 0 && index < rowCount()){
    //         Book book = bookItems.at(index);
    //         bool success = m_favoriteBookRepository->addFavorite(book.id);
    //         if(success){
    //             emit dataChanged(this->index(index), this->index(index), {IsFavoriteRole});
    //         }
    //         return success;
    //     }
    //     return false;
    // }

    // Q_INVOKABLE bool removeBookToFavorites(int index){
    //     if(index >= 0 && index < rowCount()){
    //         Book book = booksItems.at(index).book;
    //         bool success = m_favoriteBookRepository->removeFavorite(book.id);
    //         if(success){
    //             emit dataChanged(this->index(index), this->index(index), {IsFavoriteRole});
    //         }

    //         return success;
    //     }
    //     return false;
    // }





public slots:
    void refreshBooks() override {
        beginResetModel();
        bookItems.clear();
        foreach(const Book& book, m_bookRepository->getAllBooks()){
            BookItem bookItem;
            bookItem.book = book;
            bookItem.isFavorite = m_favoriteBookRepository->isFavorite(book.id);
            bookItems.append(bookItem);
        }
        qDebug() << "Found" << bookItems.count() << "books";
        endResetModel();

        emit rowCountChanged();
    }

    bool toggleFavorite(int index) {
        if(index >= 0 && index < rowCount()){
            BookItem item = bookItems.at(index);
            bool success = item.isFavorite ? m_favoriteBookRepository->removeFavorite(item.book.id): m_favoriteBookRepository->addFavorite(item.book.id);
            qDebug() << "Favoriting BOOK: " << item.book.id;

            if(success){
                item.isFavorite = !item.isFavorite;
                bookItems[index] = item;
                emit dataChanged(this->index(index), this->index(index), {IsFavoriteRole});
            }
            return success;
        }
        return false;
    }

    bool deleteBook(int index) override {
        bool success = false;
        if(index >= 0 && index < rowCount()){
            BookItem item = bookItems.at(index);
            QFile file(item.book.filePath);
            if(file.exists()){
                success = file.remove();
            }


            if(success){
                removeBook(index);
            }
        }

        return success;
    }

    void removeBook(int index) override {
        if(index >= 0 && index < rowCount()){
            Book book = bookItems.at(index).book;

            if(m_bookRepository->deleteBook(book.id)){
                beginRemoveRows(QModelIndex(), index, index);
                bookItems.removeAt(index);
                endRemoveRows();
                emit rowCountChanged();
            }
        }
    }
private:
    IBookRepository* m_bookRepository;
    IFavoriteBookRepository * m_favoriteBookRepository;
};


#endif // BOOKLISTMODEL_H
