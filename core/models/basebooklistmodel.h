#ifndef BASEBOOKLISTMODEL_H
#define BASEBOOKLISTMODEL_H

#include "core/data/book.h"
#include "core/repository/bookrepository.h"
#include "core/repository/favoritebookrepository.h"
#include <QAbstractListModel>


struct BookItem{
    Book book;
    bool isFavorite;
    bool isSelected;
    BookItem(): book(Book()), isFavorite(false), isSelected(false){}
};

class BaseBookListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)
    Q_PROPERTY(int selectedCount READ selectedCount NOTIFY selectedCountChanged)
public:
    enum BookRoles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        AuthorIdRole,
        CreatedAtRole,
        UpdatedAtRole,
        CoverImageRole,
        FilePathRole,
        IsFavoriteRole,
        IsSelectedRole
    };

    explicit BaseBookListModel(QObject* parent = nullptr): QAbstractListModel(parent){}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        if (parent.isValid()) return 0;
        return bookItems.count();
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() < 0 || index.row() >= bookItems.size()) return QVariant();

        const BookItem &item = bookItems.at(index.row());

        switch (role) {
            case IdRole:          return item.book.id;
            case TitleRole:       return item.book.title;
            case AuthorIdRole:    return item.book.authorId;
            case CreatedAtRole:   return item.book.createdAt;
            case UpdatedAtRole:   return item.book.updatedAt;
            case CoverImageRole:  return item.book.coverImagePath;
            case FilePathRole:    return item.book.filePath;
            case IsFavoriteRole:  return item.isFavorite;
            case IsSelectedRole: return item.isSelected;
            default:              return QVariant();
        }
    }

    // bool setData(const QModelIndex &index, const QVariant &value, int role) override{
    //     if (!index.isValid() || index.row() >= bookItems.size())
    //         return false;


    //     BookItem &item = bookItems[index.row()];

    //     if (role == IsSelectedRole) {
    //         item.isSelected = value.toBool();
    //         emit dataChanged(index, index, {IsSelectedRole});
    //         return true;
    //     }
    //     return false;
    // }

    QHash<int, QByteArray> roleNames() const override {
        return {
            { IdRole,          "id" },
            { TitleRole,       "title" },
            { AuthorIdRole,    "authorId" },
            { CreatedAtRole,   "createdAt" },
            { UpdatedAtRole,   "updatedAt" },
            { CoverImageRole,  "coverImagePath" },
            { FilePathRole,    "filePath" },
            { IsFavoriteRole,  "isFavorite" },
            { IsSelectedRole,   "isSelected"}
        };
    }



    int selectedCount() const {
        return m_selected_count;
    }
signals:
    void rowCountChanged();
    void selectedCountChanged();

public slots:
    virtual void refreshBooks() = 0;
    virtual bool deleteBook(int index) = 0;
    virtual void removeBook(int index) = 0;


    void select(int idx) {
        if (idx >= 0 && idx < bookItems.size()) {
            BookItem &item = bookItems[idx];

            if(item.isSelected) return;

            item.isSelected = true;
            const QModelIndex modelIndex = this->index(idx);
            emit dataChanged(modelIndex, modelIndex, {IsSelectedRole});
            updateSelectedCount();
        }
    }

    void deselect(int idx) {
        if (idx >= 0 && idx < bookItems.size()) {
            BookItem &item = bookItems[idx];

            if(!item.isSelected) return;

            item.isSelected = false;
            const QModelIndex modelIndex = this->index(idx);
            emit dataChanged(modelIndex, modelIndex, {IsSelectedRole});
            updateSelectedCount();
        }
    }


    void selectAll(){
        if(bookItems.empty() || m_selected_count == bookItems.size()) return;

        const auto lastIdx = bookItems.size() - 1;
        for(BookItem &item: bookItems){
            item.isSelected = true;
        }


        m_selected_count = bookItems.size();
        emit dataChanged(index(0), index(lastIdx), {IsSelectedRole});
        emit selectedCountChanged();
    }

    void deselectAll(){
        if(bookItems.empty() || m_selected_count == 0) return;

        const auto lastIdx = bookItems.size() - 1;
        for(BookItem &item: bookItems){
            item.isSelected = false;
        }

        m_selected_count = 0;
        emit dataChanged(index(0), index(lastIdx), {IsSelectedRole});
        emit selectedCountChanged();
    }


protected:
    QVector<BookItem> bookItems;
    int m_selected_count{};

private:
    void updateSelectedCount(){
        int new_count = std::count_if(bookItems.begin(), bookItems.end(), [](const BookItem& item){ return item.isSelected; });
        if(new_count != m_selected_count){
            m_selected_count = new_count;
            emit selectedCountChanged();
        }
    }
};

#endif // BASEBOOKLISTMODEL_H
