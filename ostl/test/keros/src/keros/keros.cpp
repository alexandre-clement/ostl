#include <gtest/gtest.h>

#include <keros/keros.hpp>

TEST(keros, empty_main_function)
{
    using model = keros::default_model<std::shared_ptr>;
    keros::ptr<keros::type<model>> voidt = std::make_shared<keros::type<model>>("void");
    keros::function<model> f("main", voidt);
    keros::glsl_exporter<model> e;
    e.scan(f);

    auto shader = e.result();

    ASSERT_EQ(R"glsl(void main()
{
}
)glsl",
      shader);
}

TEST(keros, simple_main)
{
    keros::writer<keros::stage::vertex> writer;
    writer.implement_main([&]() { writer.out.position = keros::vec4(0, 1, 0, 1); });
    auto shader = writer.to_glsl();

    ASSERT_EQ(R"glsl(#version 450

void main()
{
    gl_Position = vec4(0, 1, 0, 1);
}
)glsl",
      shader);
}
