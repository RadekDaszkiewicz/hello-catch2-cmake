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

TEST_CASE("testing getting all data from database")
{
    using namespace std;
    SECTION("getAll is implemented")
    {
        REQUIRE_NOTHROW([]() {Database db; db.getAll(); }());
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

TEST_CASE("testing inserting elements to database")
{
    using namespace std;
    SECTION("database is available with mocked data")
    {
        DatabaseInh db;
        map<int, product_t> alldb = {{1, {1, "Pierwszy produkt", 1.0}},
                                     {2, {2, "Drugi", 2.22}}};
        db.setDb(alldb);
        list<product_t> alllist;
        for (auto e : alldb)
            alllist.push_back(e.second);
        REQUIRE(db.getAll() == alllist);
        SECTION("one product was added to database")
        {
            REQUIRE_NOTHROW(db.insert({3, "Kolejna rzecz", 9.99}));
            SECTION("the database should contain Kolejna rzecz ")
            {
                alllist.push_back({3, "Kolejna rzecz", 9.99});
                REQUIRE(db.getAll() == alllist);
            }
        }

    }
}

TEST_CASE("testing getting element by id")
{
    using namespace std;
    SECTION("database is available with mocked data")
    {
        DatabaseInh db;
        map<int, product_t> alldb = {{1, {1, "Pierwszy produkt", 1.0}},
                                     {2, {2, "Drugi", 2.22}}};
        db.setDb(alldb);
        SECTION("getProductById is implemented")
        {
            REQUIRE_NOTHROW(db.getProductById(2));
            SECTION("database return product with id 2")
            {
                product_t product_to_cmp = {2, "Drugi", 2.22};
                REQUIRE(db.getProductById(2) == product_to_cmp);
            }
        }

    }
}

SCENARIO("deleting product from database")
{
    using namespace Catch::Matchers;
    using namespace std;
    GIVEN("database is available with mocked data")
    {
        DatabaseInh db;
        map<int, product_t> alldb = {{1, {1, "Pierwszy produkt", 1.0}},
                                     {2, {2, "Drugi", 2.22}},
                                     {3, {3, "Kolejna rzecz", 9.99}}};
        db.setDb(alldb);
        list<product_t> alllist;
        for (auto e : alldb)
            alllist.push_back(e.second);
        CHECK(db.getAll() == alllist);
        WHEN("product with id 2 was removed from database")
        {
            REQUIRE_NOTHROW(db.remove(2));
            THEN("the database shouldn't contain product with id 2")
            {
                for (auto p : db.getAll())
                {
                    CHECK(p.id != 2);
                }
            }
        }
        WHEN("we try to remove nonexistent element")
        {
            THEN("exception should be thrown")
            {
                REQUIRE_THROWS_AS(db.remove(100),std::invalid_argument);
            }
            THEN("exception should contain correct text")
            {

                REQUIRE_THROWS_WITH(db.remove(100),
                                    EndsWith("was not found") || StartsWith("element"));
            }
        }
    }
}