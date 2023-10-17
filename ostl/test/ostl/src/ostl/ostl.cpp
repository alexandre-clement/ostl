#include <gtest/gtest.h>

#include <ostl/ostl.hpp>

TEST(ostl, simple_variable)
{
    ostl::vec2 position;

    std::string result = ostl::to_glsl(position);
    ASSERT_EQ(R"glsl(vec2 local_variable_1 = vec2())glsl", result);
}
