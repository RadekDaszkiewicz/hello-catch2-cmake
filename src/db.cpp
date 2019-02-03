#include "db.hpp"

std::list<product_t> Database::getAll() {
    std::list<product_t> result;
    for (auto &e: database) {
        result.push_back(e.second);
    }
    return result;
}

void Database::insert(const product_t &p) {
    database[p.id] = p;
}

product_t Database::getProductById(const int id) {
    for (auto &e: database) {
        if (e.second.id == id) {
            return e.second;
        }
    }
}

void Database::remove(const int id) {
    if (database.count(id) == 0) throw std::invalid_argument("element was not found");
    database.erase(id);
}
