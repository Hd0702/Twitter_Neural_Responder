//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstring>
#include "dstring.h"

TEST_CASE("String class", "[String]"){        //this is very close to the handout
    DString s[10];                              //I mainly added tests for the less than operator
    s[0] = DString("testString");
    s[1] = DString("a test string");
    s[2] = DString("");
    s[3] = DString("THIS IS AN UPPERCASE STRING");
    s[4] = DString("this is an uppercase string");
    s[5] = DString("\n");
    s[6] = DString("");
    s[7] = DString("  split  split  split  ");
    s[8] = DString("                          ");
    s[9] = DString("testString");

    SECTION("Less Than Operator") {
        REQUIRE(s[1] < s[0]);
        REQUIRE(s[3] < s[1]);
        REQUIRE(s[8] < s[9]);
        REQUIRE(s[5] < s[7]);
    }

    SECTION("Equality operators"){
        REQUIRE(s[0] == DString("testString"));
        REQUIRE(s[0] == s[9]);
        REQUIRE(s[2] == "");
        REQUIRE(s[1] == "a test string");
        REQUIRE(!(s[3] == s[4]));
    }

    SECTION("Assignment operators"){
        DString str;
        str = "a test string";
        REQUIRE(str == s[1]);
        str = DString("testString");
        REQUIRE(str == s[0]);
        str = "";
        REQUIRE(str == s[6]);
        str = DString("\n");
        REQUIRE(str == s[5]);
    }

    SECTION("Addition operator"){
        REQUIRE(DString("testStringtestString") == s[0]+s[9]);
        REQUIRE(s[6] + s[6] == "");
        REQUIRE(s[2] + s[1] + s[9] == "a test stringtestString");
        REQUIRE(s[5] + s[6] == DString("\n"));

    }

    SECTION("Greater than operator"){
        REQUIRE(s[0] > s[1]);
        REQUIRE(s[4] > s[3]);
        REQUIRE(s[9] > s[6]);
        REQUIRE(s[7] > s[6]);
    }

    SECTION("[] Operator"){
        REQUIRE(s[0][1] == 'e');
        REQUIRE(s[4][4] == ' ');
        REQUIRE(s[6][0] == 0);
    }

    SECTION("getLength function"){
        REQUIRE(s[9].getLength() == 10);
        REQUIRE(s[2].getLength() == 0);
        REQUIRE(s[8].getLength() == 26);
        REQUIRE(s[3].getLength() == 27);
    }

    SECTION("Substring function"){
        REQUIRE(s[0].substring(0, 5) == "testS");
        REQUIRE(s[4].substring(0, 4) == "this");
        REQUIRE(s[4].substring(1, 3) == "his");
    }

    SECTION("c_str function"){
        REQUIRE(strcmp(s[0].c_str(), "testString") == 0);
        REQUIRE(strcmp(s[9].c_str(), s[0].c_str()) == 0);
        REQUIRE(strcmp(s[2].c_str(), "") == 0);
    }

}
