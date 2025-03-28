#ifndef AUTHOR_H
#define AUTHOR_H

#include <QString>
#include <QDateTime>

struct Author {
    int id;
    QString name;
    QDateTime createdAt;
    QDateTime updatedAt;
    QString imagePath;
};


#endif // AUTHOR_H
