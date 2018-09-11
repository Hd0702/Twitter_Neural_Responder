#include "catch.hpp"
#include "dvector.h"
#include "dstring.h"
#include <cstring>
//tests with primitive data types
TEST_CASE("Vector Class","[DVector]") {
    DVector<int> a[5];
    for(int i =0; i < 10; i++) {
    a[0].push_back(i%5);
    a[1].push_back(i);
    a[4].push_back(i%5);
    }
    a[2].push_back(-4);
    a[2].push_back(1000000000);

    SECTION("Push Back") {
        a[0].push_back(20);
        REQUIRE(a[0].at(10) == 20);
        a[3].push_back(0);
        REQUIRE(a[3].at(0) == 0);
        a[2].push_back(-50);
        REQUIRE(a[2].at(2) == -50);
    }
    SECTION("GET SIZE"){
        REQUIRE(a[0].getsize() == 10);
        REQUIRE(a[3].getsize() == 0);
        REQUIRE(a[2].getsize() == 2);
    }
    SECTION("= Operator") {
        DVector<int> b;
        b[0]= a[0].at(0);
        REQUIRE(b[0] == 0);
        int h = -4;
        REQUIRE(a[2].at(0) == h);
        DVector<int> K = a[0];
        REQUIRE(K.at(4) == a[0].at(4));
        REQUIRE(K.at(0) == a[0].at(0));

    }
    SECTION("[] Operator") {
        REQUIRE(a[0][0] == 0);
        REQUIRE(a[2][1] != -4);
        REQUIRE(a[4][3] == a[0][3]);
        REQUIRE(a[1].at(9) == 9);

    }
    SECTION("Iterators") {
        auto iter = a[0].begin();
        REQUIRE(*iter == 0);
        auto iter2 = a[0].begin()+9;
        REQUIRE(*iter2 == a[0][9]);
        auto iter3 = a[2].begin()+1;
        REQUIRE(*iter3 == 1000000000);
        auto iter4 = a[1].end()-1;
        REQUIRE(*iter4 == 9);
    }
}
//tests with custom objects
TEST_CASE("Vector Class<custom objects>","[Dvector") {
    DVector<DString> a[5];
    a[0].push_back("hello world");
    a[0].push_back("world hello");
    a[1].push_back("12345");
    DString b = "Test string";
    a[1].push_back(b);
    a[2].push_back(b);
    DString v = "another test string";
    a[4].push_back(v+b);
    a[4].push_back(v);
    a[4].push_back("            ");
    a[4].push_back("[][]");
    for(int i =0; i <10; i++) {
        a[2].push_back("abc");
    }

    SECTION("Push Back") {
        a[0].push_back("ddd");
        REQUIRE(a[0][2] == "ddd");
        DString l = a[1][0];
        a[3].push_back(l);
        REQUIRE(a[3][0] == "12345");
        a[4].push_back(a[1][1] + " test");
        REQUIRE("teststring test");
    }

    SECTION("GET SIZE"){
        REQUIRE(a[0].getsize() == 2);
        a[0].push_back("sfs");
        REQUIRE(a[0].getsize() == 3);
        REQUIRE(a[4].getsize() == 4);
        REQUIRE(a[2].getsize() == 11);
    }

    SECTION("= Operator") {
        a[0].push_back("TESTING");
        a[3] = a[0];
        REQUIRE(a[3][1] == a[0][1]);
        REQUIRE(a[3][2] == a[0][2]);
        a[2][0] = a[4][2];
        REQUIRE(a[2][0] == "            ");
    }

    SECTION("[] Operator") {
        REQUIRE(a[4][3] == "[][]");
        REQUIRE(a[0].at(1) == "world hello");
        REQUIRE(a[4][0] == "another test stringTest string");
        DString o = "Test string";
        REQUIRE(a[2][0] == o);
    }
    SECTION("Iterators") {
        auto iter1 = a[0].begin();
        REQUIRE(*iter1 == "hello world");
        iter1 = a[4].begin()+2;
        REQUIRE(*iter1 == "            ");
        iter1 = a[4].end()-1;
        REQUIRE(*iter1 == "[][]");
        iter1 = a[0].end()-2;
        REQUIRE(*iter1 == "hello world");

    }
}
