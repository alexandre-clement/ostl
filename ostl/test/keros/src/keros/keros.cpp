#include <gtest/gtest.h>

#include <keros/keros.hpp>

TEST(keros, simple_main)
{
    keros::file<keros::default_model<std::shared_ptr>> f;
    keros::glsl_exporter<keros::default_model<std::shared_ptr>> e;
    e.scan(f);

    keros::writer<keros::stage::vertex> writer;
    writer.implement_main([&]() { writer.out.gl_position = keros::vec4(0, 1, 0, 1); });
    auto shader = writer.to_glsl();
    ASSERT_EQ(R"(#version 450

void main()
{
	gl_Position = vec4(0, 1, 0, 1);
}
)",
      shader);
}