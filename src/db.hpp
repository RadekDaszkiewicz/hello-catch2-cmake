#ifndef __MY_DB_H___
#define __MY_DB_H___
#include "person.hpp"
#include "product.hpp"
#include <list>
#include <map>

class Database {
    protected:
    std::map<int,person_t> database;
    std::map<int,product_t> productDB;
    public:
    std::list <person_t> getAll();
    std::list <product_t> getAllProducts();
    void insert(const person_t &p);
    void insertProduct(const product_t &p);
    void remove(const int id);
    void removeProduct(const int id);
};

#endif