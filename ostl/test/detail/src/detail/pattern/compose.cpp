#include <memory>

#include <gtest/gtest.h>

#include <detail/pattern/compose.hpp>

class grand_father;

class mother;

class aunt;

class son;

class sibling;

using visitables = detail::pack<grand_father, mother, aunt, son, sibling>;

class grand_father : public virtual detail::visitable<visitables, detail::qualifier::constant>
{
    make_visitable
};

class mother : public grand_father
{
    make_visitable
};

class aunt : public grand_father
{
public:
    grand_father gf;

    make_visitable
};

class son : public mother
{
public:
    aunt a;

    make_visitable
};

class sibling : public aunt
{
    make_visitable
};

enum class path_taken_cartesian_product
{
    visit_none = 0,
    visit_grand_father = 1 << 0,
    visit_mother = 1 << 1,
    visit_aunt = 1 << 2,
    visit_son = 1 << 3,
    visit_sibling = 1 << 4,

    visit_mother_and_grand_father = visit_grand_father | visit_mother,
    visit_aunt_and_grand_father = visit_grand_father | visit_aunt,
    visit_son_and_mother_and_grand_father_and_aunt = visit_grand_father | visit_mother | visit_aunt | visit_son,
    visit_sibling_and_aunt_and_grand_father = visit_grand_father | visit_aunt | visit_sibling,
};

inline path_taken_cartesian_product operator|(path_taken_cartesian_product a, path_taken_cartesian_product b)
{
    return static_cast<path_taken_cartesian_product>(static_cast<int>(a) | static_cast<int>(b));
}

inline path_taken_cartesian_product& operator|=(path_taken_cartesian_product& a, path_taken_cartesian_product b)
{
    return a = a | b;
}

class a : public detail::visitor<visitables, detail::qualifier::constant>
{
public:
    using detail::visitor<visitables, detail::qualifier::constant>::visit;

    void visit(const grand_father&) override {}

    void visit(const mother&) override {}

    void visit(const aunt& host) override { host.gf.accept(*this); }

    void visit(const son& host) override { host.a.accept(*this); }

    void visit(const sibling&) override {}
};

class b : public detail::visitor<visitables, detail::qualifier::constant>
{
public:
    void visit(const grand_father&) override {}

    void visit(const mother& host) override { visit(static_cast<grand_father>(host)); }

    void visit(const aunt&) override {}

    void visit(const son& host) override { visit(static_cast<mother>(host)); }

    void visit(const sibling& host) override { visit(static_cast<aunt>(host)); }
};

struct c : public detail::explicit_compose<a, b, grand_father, mother, aunt, son, sibling>
{
    using super = detail::explicit_compose<a, b, grand_father, mother, aunt, son, sibling>;

    void visit(const grand_father&) override { visited |= path_taken_cartesian_product::visit_grand_father; }

    void visit(const mother& host) override
    {
        visited |= path_taken_cartesian_product::visit_mother;
        super::visit(host);
    }

    void visit(const aunt& host) override
    {
        visited |= path_taken_cartesian_product::visit_aunt;
        super::visit(host);
    }

    void visit(const son& host) override
    {
        visited |= path_taken_cartesian_product::visit_son;
        super::visit(host);
    }

    void visit(const sibling& host) override
    {
        visited |= path_taken_cartesian_product::visit_sibling;
        super::visit(host);
    }

    path_taken_cartesian_product visited = path_taken_cartesian_product::visit_none;
};

TEST(compose, visit_none)
{
    c p;
    ASSERT_EQ(path_taken_cartesian_product::visit_none, p.visited);
}

TEST(compose, visit_grand_father)
{
    grand_father gf;
    c p;
    gf.accept(p);
    ASSERT_EQ(path_taken_cartesian_product::visit_grand_father, p.visited);
}

TEST(compose, visit_mother_and_grand_father)
{
    mother m;
    c p;
    m.accept(p);
    ASSERT_EQ(path_taken_cartesian_product::visit_mother_and_grand_father, p.visited);
}

TEST(compose, visit_aunt_and_grand_father)
{
    aunt a;
    c p;
    a.accept(p);
    ASSERT_EQ(path_taken_cartesian_product::visit_aunt_and_grand_father, p.visited);
}

TEST(compose, visit_son_and_mother_and_grand_father_and_aunt)
{
    son s;
    c p;
    s.accept(p);
    ASSERT_EQ(path_taken_cartesian_product::visit_son_and_mother_and_grand_father_and_aunt, p.visited);
}

TEST(compose, visit_sibling_and_aunt_and_grand_father)
{
    sibling s;
    c p;
    s.accept(p);
    ASSERT_EQ(path_taken_cartesian_product::visit_sibling_and_aunt_and_grand_father, p.visited);
}
