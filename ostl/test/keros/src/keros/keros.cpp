#include <gtest/gtest.h>

#include <keros/keros.hpp>

TEST(keros, simple_main)
{
    using model = keros::default_model<std::shared_ptr>;
    keros::file<model> f;
    keros::glsl_exporter<model> e;
    e.scan(f);

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
