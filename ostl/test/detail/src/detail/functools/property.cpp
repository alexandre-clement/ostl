#include <gtest/gtest.h>

#include <detail/functools/property.hpp>

struct default_property
{
    detail::property<int> i;
};

TEST(property, default_property)
{
    default_property dp;
    dp.i = 2;
    ASSERT_EQ(2, dp.i);
}

struct custom_property
{
    detail::property<std::string> i{[](std::string& self) -> const std::string& { return self; },
      [](std::string& self, const std::string& j) -> const std::string& { return self = j + '\n'; }};

    std::string _j;

    std::string getj() { return _j; }
    std::string putj(std::string k) { return _j = k; }

    __declspec(property(get = getj, put = putj)) std::string j;
};

TEST(property, custom_property)
{
    custom_property cp;
    cp.i = "Hello world !";
    ASSERT_EQ("Hello world !\n", cp.i);
    cp.j.c_str();
}