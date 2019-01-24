#include "db.hpp"

std::list<person_t> Database::getAll() {
    std::list<person_t> result;
    for (auto &e: database) {
        result.push_back(e.second);
    }
    return result;
}

    void Database::insert(const person_t &p){
        database[p.id] = p;
    }
    void Database::remove(const int id){
        if (database.count(id) == 0) throw std::invalid_argument("element was not found");
        database.erase(id);
    }


std::list<product_t> Database::getAllProducts(){
    std::list<product_t> result;
    for (auto &e: productDB) {
        result.push_back(e.second);
    }
    return result;
}

void Database::insertProduct(const product_t &p){
    productDB[p.id] = p;
}
void Database::removeProduct(const int id){
    if (productDB.count(id) == 0) throw std::invalid_argument("element was not found");
    productDB.erase(id);
}