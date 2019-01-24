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
