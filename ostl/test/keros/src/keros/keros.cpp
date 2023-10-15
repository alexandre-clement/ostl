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

    ASSERT_EQ(R"glsl(1 + 2)glsl", result);
}

TEST(keros, simple_variable)
{
    using model = keros::metamodel<std::shared_ptr>;

    keros::ptr<keros::type<model>> intt = std::make_shared<keros::type<model>>("int");
    keros::ptr<keros::variable<model>> index = std::make_shared<keros::variable<model>>("index", intt);

    auto result = keros::to_glsl(index);

    ASSERT_EQ(R"glsl(int index)glsl", result);
}

TEST(keros, uniform_variable)
{
    using model = keros::metamodel<std::shared_ptr>;

    keros::ptr<keros::type<model>> intt = std::make_shared<keros::type<model>>("int");
    keros::ptr<keros::variable<model>> imageCount = std::make_shared<keros::variable<model>>("imageCount", intt);
    imageCount->add_modifier(std::make_shared<keros::uniform<model>>());

    auto result = keros::to_glsl(imageCount);

    ASSERT_EQ(R"glsl(uniform int imageCount)glsl", result);
}

TEST(keros, local_variable)
{
    using model = keros::metamodel<std::shared_ptr>;

    keros::ptr<keros::type<model>> intt = std::make_shared<keros::type<model>>("int");
    keros::ptr<keros::local_variable<model>> width = std::make_shared<keros::local_variable<model>>("width", intt);
    width->right_hand_side = std::make_shared<keros::literal<model>>(intt, 1920);

    auto result = keros::to_glsl(width);

    ASSERT_EQ(R"glsl(int width = 1920)glsl", result);
}

TEST(keros, empty_for_loop)
{
    using model = keros::metamodel<std::shared_ptr>;

    keros::ptr<keros::for_<model>> for_loop = std::make_shared<keros::for_<model>>();

    keros::ptr<keros::type<model>> intt = std::make_shared<keros::type<model>>("int");
    keros::ptr<keros::local_variable<model>> i = std::make_shared<keros::local_variable<model>>("i", intt);
    i->right_hand_side = std::make_shared<keros::literal<model>>(intt, 0);
    for_loop->initializer = i;

    keros::ptr<keros::less_than<model>> halt_condition = std::make_shared<keros::less_than<model>>(intt);
    keros::ptr<keros::literal<model>> ten = std::make_shared<keros::literal<model>>(intt, 10);
    halt_condition->left = std::make_shared<keros::variable_reference<model>>(intt, "i");
    halt_condition->right = ten;
    for_loop->halt_condition = halt_condition;

    keros::ptr<keros::prefix_increment<model>> increment = std::make_shared<keros::prefix_increment<model>>(intt);
    increment->operand = std::make_shared<keros::variable_reference<model>>(intt, "i");
    for_loop->increment = increment;

    auto result = keros::to_glsl(for_loop);

    ASSERT_EQ(R"glsl(for (int i = 0; i < 10; ++i)
{
})glsl",
      result);
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
