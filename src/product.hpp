//
// Created by radek on 22.01.19.
//

#ifndef __PRODUCT__
#define __PRODUCT__

#include <string>
#include <iostream>

struct product_t {
    int id;
    std::string name;
    double price;
};

inline bool operator==(const product_t &a, const product_t &b) {
    return (a.id == b.id) && (a.name == b.name) && (a.price == b.price);
}

inline std::ostream &operator<<(std::ostream &out, const product_t &p) {
    out << "{" << p.id << ", " << p.name << ", " << p.price << "}";
    return out;
}

#endif
