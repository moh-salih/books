#include "categoryrepository.h"



Category CategoryRepository::parseCategoryFromQuery(QSqlQuery &query) const{
    Category category;
    category.id = query.value("id").toInt();
    category.name = query.value("name").toString();
    category.createdAt = query.value("created_at").toDateTime();
    category.updatedAt = query.value("updated_at").toDateTime();
    category.imagePath = query.value("image_path").toString();
    return category;
}

CategoryRepository::CategoryRepository(const QSqlDatabase &db, QObject *parent): m_db(db), QObject(parent){

}

bool CategoryRepository::addCategory(const Category &category){
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO categories (name, image_path) VALUES (?, ?)");
    query.addBindValue(category.name);
    query.addBindValue(category.imagePath);
    return query.exec();
}

Category CategoryRepository::getCategoryById(int categoryId) const{
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM categories WHERE id = ?");
    query.addBindValue(categoryId);
    if(query.exec() && query.next()){
        return parseCategoryFromQuery(query);
    }else{
        return Category();
    }
}

QList<Category> CategoryRepository::getAllCategories() const{
    QSqlQuery query(m_db);
    QList<Category> categories;
    if(query.exec("SELECT * FROM categories")){
        while(query.next()){
            Category category = parseCategoryFromQuery(query);
            categories.append(category);
        }
    }
    return categories;
}

Category CategoryRepository::updateCategory(const Category &category){
    return category;
}

bool CategoryRepository::deleteCategory(int categoryId){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM categories WHERE id = ?");
    query.addBindValue(categoryId);
    return query.exec();
}

void CategoryRepository::clear(){
    QSqlQuery query(m_db);
    query.exec("DELETE FROM categories");
}

bool CategoryRepository::createTable() const{
    QSqlQuery query(m_db);

    QString sql = QStringLiteral("CREATE TABLE IF NOT EXISTS categories ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "name TEXT,"
                                 "image_path TEXT,"
                                 "created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
                                 "updated_at DATETIME DEFAULT CURRENT_TIMESTAMP"
                                 ")");

    if (!query.exec(sql)) {
        qDebug() << "Error creating categories table:" << query.lastError().text();
        return false;
    }

    sql = QStringLiteral("CREATE TRIGGER IF NOT EXISTS update_category_updated_at "
                         "AFTER UPDATE ON categories "
                         "BEGIN "
                         "    UPDATE categories SET updated_at = CURRENT_TIMESTAMP WHERE id = OLD.id; "
                         "END;");

    if (!query.exec(sql)) {
        qDebug() << "Error creating categories trigger:" << query.lastError().text();
        return false;
    }

    return true;
}
