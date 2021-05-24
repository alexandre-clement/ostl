#include <set>
#include <vector>

#include <gtest/gtest.h>

#include <detail/concepts/concepts.hpp>

template<class t>
bool test_is_iterable()
{
    return false;
}

template<detail::iterable t>
bool test_is_iterable()
{
    return true;
}

TEST(concepts, vector_is_iterable) { ASSERT_TRUE(test_is_iterable<std::vector<int>>()); }

TEST(concepts, set_is_iterable) { ASSERT_TRUE(test_is_iterable<std::set<int>>()); }

TEST(concepts, base_is_not_iterable) { ASSERT_FALSE(test_is_iterable<int>()); }