#ifndef FAVORITEBOOKLISTMODEL_H
#define FAVORITEBOOKLISTMODEL_H


#include "basebooklistmodel.h"
class FavoriteBookListModel : public BaseBookListModel {
    Q_OBJECT
public:
    explicit FavoriteBookListModel(IFavoriteBookRepository* favBookRepo, QObject* parent = nullptr)
        : BaseBookListModel(parent), m_favoriteBookRepository(favBookRepo){
        refreshBooks();
    }


public slots:
    void refreshBooks() override {
        beginResetModel();
        bookItems.clear();
        foreach(const Book& book, m_favoriteBookRepository->getAllFavorites()){
            BookItem bookItem;
            bookItem.book = book;
            bookItem.isFavorite = true;
            bookItems.append(bookItem);
        }
        endResetModel();
        emit rowCountChanged();
    }

    bool removeFavorites(){
        return m_favoriteBookRepository->removeFavorites();
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

            if(m_favoriteBookRepository->removeFavorite(book.id)){
                beginRemoveRows(QModelIndex(), index, index);
                bookItems.removeAt(index);
                endRemoveRows();
                emit rowCountChanged();
            }
        }
    }

private:
    IFavoriteBookRepository * m_favoriteBookRepository;
};

#endif // FAVORITEBOOKLISTMODEL_H
