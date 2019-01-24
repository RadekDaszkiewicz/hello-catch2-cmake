#ifndef __MY_DB_H___
#define __MY_DB_H___
#include "product.hpp"
#include <list>
#include <map>

class Database {
    protected:
    std::map<int,product_t> database;
    public:
    std::list <product_t> getAll();
    void insert(const product_t &p);
};

#endif