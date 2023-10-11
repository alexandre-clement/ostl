#include <gtest/gtest.h>

#include <keros/keros.hpp>

TEST(keros, empty_main_function)
{
    using model = keros::metamodel<std::shared_ptr>;
    keros::ptr<keros::type<model>> voidt = std::make_shared<keros::type<model>>("void");
    keros::ptr<keros::function<model>> main = std::make_shared<keros::function<model>>("main", voidt);

    auto result = keros::glsl_exporter<model>().scan(main).result();

    ASSERT_EQ(R"glsl(void main()
{
}
)glsl",
      result);
}

TEST(keros, add_two_numbers)
{
    using model = keros::metamodel<std::shared_ptr>;

    keros::ptr<keros::type<model>> intt = std::make_shared<keros::type<model>>("int");
    keros::ptr<keros::addition<model>> add = std::make_shared<keros::addition<model>>(intt);
    keros::ptr<keros::literal<model>> one = std::make_shared<keros::literal<model>>(intt, 1);
    keros::ptr<keros::literal<model>> two = std::make_shared<keros::literal<model>>(intt, 2);
    add->left = one;
    add->right = two;

    auto result = keros::to_glsl(add);

    ASSERT_EQ(R"glsl(1+2)glsl", result);
}

TEST(keros, ray_matcher)
{
    using model = keros::metamodel<std::shared_ptr>;

    keros::ptr<keros::file<model>> shader = std::make_shared<keros::file<model>>();

    keros::ptr<keros::version<model>> version = std::make_shared<keros::version<model>>(450);

    keros::ptr<keros::type<model>> voidt = std::make_shared<keros::type<model>>("void");
    keros::ptr<keros::function<model>> main = std::make_shared<keros::function<model>>("main", voidt);

    shader->add_directive(version);
    shader->add_function(main);

    auto result = keros::to_glsl(shader);

    ASSERT_EQ(R"glsl(#version 450

void main()
{
}

)glsl",
      result);
}

TEST(keros, simple_main)
{
    using model = keros::metamodel<std::shared_ptr>;
    keros::writer<model> writer;
    keros::shader<model> shader = writer.fragment([](auto ctx) { ctx.implement_main([]() {}); });

    auto result = keros::to_glsl(shader);

    ASSERT_EQ(R"glsl()glsl", result);
}
