#include <gtest/gtest.h>

#include <keros/keros.hpp>

TEST(keros, empty_main_function)
{
    using model = keros::default_model<std::shared_ptr>;
    keros::ptr<keros::type<model>> voidt = std::make_shared<keros::type<model>>("void");
    keros::ptr<keros::function<model>> f = std::make_shared<keros::function<model>>("main", voidt);

    auto result = keros::glsl_exporter<model>().scan(f).result();

    ASSERT_EQ(R"glsl(void main()
{
}
)glsl",
      result);
}

TEST(keros, simple_main)
{
    using model = keros::default_model<std::shared_ptr>;
    keros::writer<model> writer;
    keros::shader<model> shader = writer.fragment([](auto ctx) {

    });

    auto result = keros::to_glsl(shader);

    ASSERT_EQ(R"glsl(#version 450

void main()
{
    gl_Position = vec4(0, 1, 0, 1);
}
)glsl",
      result);
}
