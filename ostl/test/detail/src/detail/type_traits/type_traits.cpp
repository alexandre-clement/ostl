#include <gtest/gtest.h>

#include <detail/type_traits/type_traits.hpp>

template<class t>
class test;

template<>
class test<int>
{
};

TEST(type_traits, complete_type) { ASSERT_TRUE(detail::is_complete<test<int>>); }

TEST(type_traits, imcomplete_type) { ASSERT_FALSE(detail::is_complete<test<float>>); }