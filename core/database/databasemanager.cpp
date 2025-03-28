#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject *parent): QObject(parent){
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("books_db.sqlite");
    if(!m_db.open()){
        throw std::runtime_error("Connection to database failed!");
    }
}
