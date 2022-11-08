//
// Created by mw on 08.11.22.
//

#include "doctest.h"
#include "MockedTimer.h"

TEST_CASE("simple timer") {
    MockedTimer mocked_timer{0, 1};
    CHECK(mocked_timer.get_func()() == 0);
    CHECK(mocked_timer.get_func()() == 1);
}

TEST_CASE("two timer do not interfere") {
    MockedTimer mocked_timer{0, 1};
    CHECK(mocked_timer.get_func()() == 0);
    CHECK(mocked_timer.get_func()() == 1);

    MockedTimer mocked_timer2{0, 1};
    CHECK(mocked_timer2.get_func()() == 0);
    CHECK(mocked_timer.get_func()() == 2);
    CHECK(mocked_timer2.get_func()() == 1);
}

TEST_CASE("lambda function can be copied") {
    MockedTimer mocked_timer{0, 1};
    auto get_func = mocked_timer.get_func();

    CHECK(get_func() == 0);
    CHECK(mocked_timer.get_func()() == 1);
    CHECK(get_func() == 2);
}

TEST_CASE("mocked timer supports parameters") {
    MockedTimer mocked_timer{3, 2};
    auto get_func = mocked_timer.get_func();

    CHECK(get_func() == 3);
    CHECK(mocked_timer.get_func()() == 5);
    CHECK(get_func() == 7);
}

TEST_CASE("mocked timer has zero step and You can set the counter") {
    MockedTimer mocked_timer{0L, 0L};
    auto get_func = mocked_timer.get_func();

    CHECK(get_func() == 0L);
    CHECK(get_func() == 0L);
    mocked_timer.set_counter(2L);
    CHECK(get_func() == 2L);
    CHECK(get_func() == 2L);
}
