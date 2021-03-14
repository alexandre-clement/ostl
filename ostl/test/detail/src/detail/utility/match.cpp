#include <gtest/gtest.h>

#include <detail/utility/match.hpp>

TEST(match, match_int)
{
    int i = 0;
    detail::match{[](auto&& arg) { arg += 1; }, [](int& arg) { arg += 2; }, [](float& arg) { arg += 4.f; }}.with(i);
    ASSERT_EQ(2, i);
}

TEST(match, match_float)
{
    float f = 0.f;
    detail::match{[](auto&& arg) { arg += 1; }, [](int& arg) { arg += 2; }, [](float& arg) { arg += 4.f; }}.with(f);
    ASSERT_FLOAT_EQ(4.f, f);
}

TEST(match, match_any)
{
    double d = 0.;
    detail::match{[](auto&& arg) { arg += 1; }, [](int& arg) { arg += 2; }, [](float& arg) { arg += 4.f; }}.with(d);
    ASSERT_DOUBLE_EQ(1., d);
}
