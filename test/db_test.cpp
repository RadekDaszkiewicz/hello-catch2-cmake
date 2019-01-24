#include <catch2/catch.hpp>
#include <db.hpp>
#include <list>
#include <map>
#include <iostream>

class DatabaseInh : public Database
{
  public:
    void setDb(std::map<int, product_t> d)
    {
        database = d;
    };
};

TEST_CASE("testing getting data from database", "[db][crud][getAll]")
{
    using namespace std;
    SECTION("we can create database object")
    {
        REQUIRE_NOTHROW([]() {Database db; return db; }());
    }
    SECTION("getAll on empty database should return empty list")
    {
        Database db;
        list<product_t> result = db.getAll();
        REQUIRE(result == list<product_t>{});
    }
    SECTION("getAll should return correct database")
    {

        DatabaseInh db;
        std::map<int, product_t> expected = {
                {1, {1, "Pierwszy produkt", 1.0}},
                {2, {2, "Drugi", 2.22}}};
        db.setDb(expected);
        list<product_t> expected_list;
        for (auto e : expected)
        {
            expected_list.push_back(e.second);
        }
        REQUIRE(db.getAll() == expected_list);
    }
}
