#include <set>
#include <vector>

#include <gtest/gtest.h>

#include <detail/concepts/concepts.hpp>

class base
{
};

class subclass : public base
{
};

class not_a_subclass
{
};

template<class _base, class t>
bool test_derive_from(t)
{
    return false;
}

template<class _base, detail::derive_from<_base> t>
bool test_derive_from(t)
{
    return true;
}

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

TEST(concepts, is_same) { ASSERT_TRUE(test_derive_from<base>(base())); }

TEST(concepts, is_derived_from) { ASSERT_TRUE(test_derive_from<base>(subclass())); }

TEST(concepts, is_not_derived_from) { ASSERT_FALSE(test_derive_from<base>(not_a_subclass())); }

TEST(concepts, is_base_of) { ASSERT_FALSE(test_derive_from<subclass>(base())); }

TEST(concepts, vector_is_iterable) { ASSERT_TRUE(test_is_iterable<std::vector<int>>()); }

TEST(concepts, set_is_iterable) { ASSERT_TRUE(test_is_iterable<std::set<int>>()); }

TEST(concepts, base_is_not_iterable) { ASSERT_FALSE(test_is_iterable<base>()); }