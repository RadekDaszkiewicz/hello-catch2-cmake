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

SCENARIO("database operations", "[db][crud]")
{
    using namespace Catch::Matchers;
    using namespace std;
    GIVEN("database is available with mocked data")
    {
        DatabaseInh db;
        map<int, product_t> alldb = {{1, {1, "Pierwszy produkt", 1.0}},
                                     {2, {2, "Drugi", 2.22}}};
        db.setDb(alldb);
        list<product_t> alllist;
        for (auto e : alldb)
            alllist.push_back(e.second);
        CHECK(db.getAll() == alllist);
        WHEN("one element was added to database")
        {
            REQUIRE_NOTHROW(db.insert({3, "Kolejna rzecz", 9.99}));
            THEN("the database should contain Kolejna rzecz ")
            {
                alllist.push_back({3, "Kolejna rzecz", 9.99});
                CHECK(db.getAll() == alllist);
            }
        }

    }
}