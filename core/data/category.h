#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <QDateTime>

struct Category{
    int id;
    QString name;
    QDateTime createdAt;
    QDateTime updatedAt;
    QString imagePath;
};
#endif // CATEGORY_H
