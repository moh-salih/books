#ifndef ITABLEREPOSITORY_H
#define ITABLEREPOSITORY_H

struct ITableRepository{
    virtual bool createTable() const = 0;

    virtual ~ITableRepository() = default;
};

#endif // ITABLEREPOSITORY_H
