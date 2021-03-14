#include <memory>

#include <gtest/gtest.h>

#include <detail/pattern/visitor.hpp>

class root;

class intermediate_node;

class leaf;

using visitables = detail::pack<root, intermediate_node, leaf>;

enum class path_taken
{
    visit_none = 0,
    visit_root = 1,
    visit_intermediate_node = 2,
    visit_leaf = 4,

    visit_root_and_intermediate_node = visit_root | visit_intermediate_node,
    visit_root_and_leaf = visit_root | visit_leaf,
    visit_intermediate_node_and_leaf = visit_intermediate_node | visit_leaf,
    visit_all = visit_root | visit_intermediate_node | visit_leaf,
};

path_taken operator|(path_taken a, path_taken b)
{
    return static_cast<path_taken>(static_cast<int>(a) | static_cast<int>(b));
}

path_taken& operator|=(path_taken& a, path_taken b) { return a = a | b; }

class root : public virtual detail::visitable<visitables, detail::qualifier::const_>
{
    make_visitable
};

class intermediate_node : public root
{
    make_visitable
};

class leaf : public intermediate_node
{
    make_visitable
};

class printer : public detail::visitor<visitables, detail::qualifier::const_>
{
public:
    void visit(const root&) override { visited |= path_taken::visit_root; }

    void visit(const intermediate_node&) override { visited |= path_taken::visit_intermediate_node; }

    void visit(const leaf&) override { visited |= path_taken::visit_leaf; }

    path_taken visited = path_taken::visit_none;
};

TEST(visitor, visit_none)
{
    printer p;
    ASSERT_EQ(path_taken::visit_none, p.visited);
}

TEST(visitor, visit_root)
{
    root r;
    printer p;
    r.accept(p);
    ASSERT_EQ(path_taken::visit_root, p.visited);
}

TEST(visitor, visit_intermediate_node)
{
    intermediate_node i;
    printer p;
    i.accept(p);
    ASSERT_EQ(path_taken::visit_intermediate_node, p.visited);
}

TEST(visitor, visit_leaf)
{
    leaf l;
    printer p;
    l.accept(p);
    ASSERT_EQ(path_taken::visit_leaf, p.visited);
}

TEST(visitor, visit_all)
{
    root r;
    intermediate_node i;
    leaf l;
    printer p;
    r.accept(p);
    i.accept(p);
    l.accept(p);
    ASSERT_EQ(path_taken::visit_all, p.visited);
}

TEST(visitor, dynamic_visit)
{
    leaf l;
    root& r = l;
    printer p;
    r.accept(p);
    ASSERT_EQ(path_taken::visit_leaf, p.visited);
}

TEST(visitor, std_shared_ptr_visit)
{
    std::shared_ptr<root> r = std::make_shared<intermediate_node>();
    printer p;
    r->accept(p);
    ASSERT_EQ(path_taken::visit_intermediate_node, p.visited);
}