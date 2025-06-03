//
// Created by louis on 01/06/25.
//
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>

#include "add.h"

TEST_CASE("Add") {
    float res = add(3.f, 5.f);
    REQUIRE(res == 8.f);
}