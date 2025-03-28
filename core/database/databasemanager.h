#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QtCore>
#include <QtSql>
#include "core/repository/interfaces/iTableRepository.h"

class DatabaseManager: public QObject{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject * parent = nullptr);

    template <typename Table>
    Table * createRepository(){
        static_assert(std::is_base_of<ITableRepository, Table>::value, "Repository must derive from ITableRepository");
        Table * table = new Table(m_db, this);

        if(!table->createTable()){
            throw std::runtime_error("Failed to create table!");
        }
        return table;
    }
private:
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
