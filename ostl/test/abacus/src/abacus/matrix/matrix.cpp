#include <gtest/gtest.h>

#define abacus_matrix_type_aligned
#include <sstream>

#include <abacus/abacus.hpp>

template<class matrix>
void test_empty_constructor()
{
    matrix m;
    for (abacus::index row = 0; row < m.rows(); ++row)
    {
        for (abacus::index column = 0; column < m.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(0, m.at(row, column));
        }
    }
}

TEST(matrix, empty_constructor)
{
    test_empty_constructor<abacus::vec2>();
    test_empty_constructor<abacus::vec3>();
    test_empty_constructor<abacus::vec4>();
    test_empty_constructor<abacus::mat2x2>();
    test_empty_constructor<abacus::mat2x3>();
    test_empty_constructor<abacus::mat2x4>();
    test_empty_constructor<abacus::mat3x2>();
    test_empty_constructor<abacus::mat3x3>();
    test_empty_constructor<abacus::mat3x4>();
    test_empty_constructor<abacus::mat4x2>();
    test_empty_constructor<abacus::mat4x3>();
    test_empty_constructor<abacus::mat4x4>();
}

template<class matrix, class expected>
void check_elements(const matrix& m, expected e, abacus::index i)
{
    EXPECT_FLOAT_EQ(static_cast<float>(e), m.at(i / m.columns(), i % m.columns()));
}

template<class matrix, class... parameters>
void test_vargs_constructor(parameters... arguments)
{
    matrix m(arguments...);
    abacus::index i = 0;
    (check_elements(m, arguments, i++), ...);
}

TEST(matrix, vargs_constructor)
{
    test_vargs_constructor<abacus::vec2>(0, 0);
    test_vargs_constructor<abacus::vec2>(1u, 1l);
    test_vargs_constructor<abacus::vec2>(.1, .1f);
    test_vargs_constructor<abacus::vec2>('a', true);
    test_vargs_constructor<abacus::vec2>(0b101, 0x6c1);

    // this test is a reminder that using higher precision types than float
    // like double or long can be dangerous is this case, the cast is required
    // because 4294967297 is approximated by 4294967296 as a float
    test_vargs_constructor<abacus::vec2>(02471, static_cast<float>(4294967297ll));

    test_vargs_constructor<abacus::vec3>(0, 1, 2);
    test_vargs_constructor<abacus::vec4>(3, 4, 5, 6);
    test_vargs_constructor<abacus::mat2x2>(7, 8, 9, 10);
    test_vargs_constructor<abacus::mat2x3>(11, 12, 13, 14, 15, 16);
    test_vargs_constructor<abacus::mat2x4>(17, 18, 19, 20, 21, 22, 23, 24);
    test_vargs_constructor<abacus::mat3x2>(25, 26, 27, 28, 29, 30);
    test_vargs_constructor<abacus::mat3x3>(31, 32, 33, 34, 35, 36, 37, 38, 39);
    test_vargs_constructor<abacus::mat3x4>(40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51);
    test_vargs_constructor<abacus::mat4x2>(52, 53, 54, 55, 56, 57, 58, 59);
    test_vargs_constructor<abacus::mat4x3>(60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71);
    test_vargs_constructor<abacus::mat4x4>(72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87);
}

template<class vector, class scalar>
void test_vector_fill_constructor(scalar fill_value)
{
    vector v(fill_value);
    for (abacus::index column = 0; column < v.columns(); ++column)
    {
        EXPECT_FLOAT_EQ(static_cast<float>(fill_value), v.at(0, column));
    }
}

TEST(matrix, vector_fill_constructor)
{
    test_vector_fill_constructor<abacus::vec2>(1.);
    test_vector_fill_constructor<abacus::vec3>(2);
    test_vector_fill_constructor<abacus::vec4>(3);
}

template<class matrix, class scalar>
void test_matrix_diagonal_constructor(scalar diagonal_value)
{
    matrix m(diagonal_value);
    for (abacus::index row = 0; row < m.rows(); ++row)
    {
        for (abacus::index column = 0; column < m.columns(); ++column)
        {
            if (row == column)
            {
                EXPECT_FLOAT_EQ(static_cast<float>(diagonal_value), m.at(row, column));
            }
            else
            {
                EXPECT_FLOAT_EQ(0, m.at(row, column));
            }
        }
    }
}

TEST(matrix, matrix_diagonal_constructor)
{
    test_matrix_diagonal_constructor<abacus::mat2x2>(2);
    test_matrix_diagonal_constructor<abacus::mat2x3>(3);
    test_matrix_diagonal_constructor<abacus::mat2x4>(5);
    test_matrix_diagonal_constructor<abacus::mat3x2>(7);
    test_matrix_diagonal_constructor<abacus::mat3x3>(11);
    test_matrix_diagonal_constructor<abacus::mat3x4>(13);
    test_matrix_diagonal_constructor<abacus::mat4x2>(17);
    test_matrix_diagonal_constructor<abacus::mat4x3>(23);
    test_matrix_diagonal_constructor<abacus::mat4x4>(29);
}

#define test_operator(callback)                                                                                        \
    callback(abacus::vec2(2), 1);                                                                                      \
    callback(abacus::vec3(3), 4);                                                                                      \
    callback(abacus::vec4(7), 11);                                                                                     \
                                                                                                                       \
    callback(abacus::mat2x2(1), 1);                                                                                    \
    callback(abacus::mat2x3(2), 3);                                                                                    \
    callback(abacus::mat2x4(5), 8);                                                                                    \
    callback(abacus::mat3x2(13), 21);                                                                                  \
    callback(abacus::mat3x3(34), 55);                                                                                  \
    callback(abacus::mat3x4(89), 144);                                                                                 \
    callback(abacus::mat4x2(233), 377);                                                                                \
    callback(abacus::mat4x3(610), 987);                                                                                \
    callback(abacus::mat4x4(1597), 2584);                                                                              \
                                                                                                                       \
    callback(abacus::mat4x4(256), 128ll);                                                                              \
    callback(abacus::mat4x4(64), ' ');                                                                                 \
    callback(abacus::mat4x4(16), 8l);                                                                                  \
    callback(abacus::mat4x4(4), 2u);                                                                                   \
    callback(abacus::mat4x4(1), .5);                                                                                   \
    callback(abacus::mat4x4(.25), .125);                                                                               \
    callback(abacus::mat4x4(.0625), .03125f);                                                                          \
    callback(abacus::mat4x4(0.015625), 0.0078125f);

template<class matrix, class scalar>
void test_matrix_plus_scalar(const matrix& m, scalar x)
{
    matrix sum = m + x;
    for (abacus::index row = 0; row < m.rows(); ++row)
    {
        for (abacus::index column = 0; column < m.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(m.at(row, column) + static_cast<float>(x), sum.at(row, column));
        }
    }
}

TEST(matrix, matrix_plus_scalar) { test_operator(test_matrix_plus_scalar); }

template<class matrix, class scalar>
void test_matrix_minus_scalar(const matrix& m, scalar x)
{
    matrix diff = m - x;
    for (abacus::index row = 0; row < m.rows(); ++row)
    {
        for (abacus::index column = 0; column < m.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(m.at(row, column) - static_cast<float>(x), diff.at(row, column));
        }
    }
}

TEST(matrix, matrix_minus_scalar) { test_operator(test_matrix_minus_scalar); }

template<class matrix, class scalar>
void test_matrix_times_scalar(const matrix& m, scalar x)
{
    matrix prod = m * x;
    for (abacus::index row = 0; row < m.rows(); ++row)
    {
        for (abacus::index column = 0; column < m.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(m.at(row, column) * static_cast<float>(x), prod.at(row, column));
        }
    }
}

TEST(matrix, matrix_times_scalar) { test_operator(test_matrix_times_scalar); }

template<class matrix, class scalar>
void test_matrix_divided_by_scalar(const matrix& m, scalar x)
{
    matrix div = m / x;
    for (abacus::index row = 0; row < m.rows(); ++row)
    {
        for (abacus::index column = 0; column < m.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(m.at(row, column) / static_cast<float>(x), div.at(row, column));
        }
    }
}

TEST(matrix, matrix_divided_by_scalar)
{
    ASSERT_THROW(abacus::vec2() / 0, std::domain_error);
    ASSERT_THROW(abacus::vec2() / 0.f, std::domain_error);
    ASSERT_THROW(abacus::vec2() / 0., std::domain_error);
    ASSERT_THROW(abacus::vec2() / 0u, std::domain_error);
    ASSERT_THROW(abacus::vec2() / 0l, std::domain_error);
    test_operator(test_matrix_divided_by_scalar);
}

template<class matrix, class scalar>
void test_scalar_plus_matrix(const matrix& m, scalar x)
{
    matrix sum = x + m;
    for (abacus::index row = 0; row < m.rows(); ++row)
    {
        for (abacus::index column = 0; column < m.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(static_cast<float>(x) + m.at(row, column), sum.at(row, column));
        }
    }
}

TEST(matrix, scalar_plus_matrix) { test_operator(test_scalar_plus_matrix); }

template<class matrix, class scalar>
void test_scalar_minus_matrix(const matrix& m, scalar x)
{
    matrix diff = x - m;
    for (abacus::index row = 0; row < m.rows(); ++row)
    {
        for (abacus::index column = 0; column < m.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(static_cast<float>(x) - m.at(row, column), diff.at(row, column));
        }
    }
}

TEST(matrix, scalar_minus_matrix) { test_operator(test_scalar_minus_matrix); }

template<class matrix, class scalar>
void test_scalar_times_matrix(const matrix& m, scalar x)
{
    matrix prod = x * m;
    for (abacus::index row = 0; row < m.rows(); ++row)
    {
        for (abacus::index column = 0; column < m.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(static_cast<float>(x) * m.at(row, column), prod.at(row, column));
        }
    }
}

TEST(matrix, scalar_times_matrix) { test_operator(test_scalar_times_matrix); }

template<class matrix, class scalar>
void test_scalar_divided_by_matrix(const matrix& m, scalar x)
{
    matrix div = x / m;
    for (abacus::index row = 0; row < m.rows(); ++row)
    {
        for (abacus::index column = 0; column < m.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(static_cast<float>(x) / m.at(row, column), div.at(row, column));
        }
    }
}

TEST(matrix, scalar_divided_by_matrix)
{
    ASSERT_THROW(1 / abacus::vec2(), std::domain_error);

    // note that mat2(1) is the identity matrix, therefore, it contains
    // multiples zeros
    ASSERT_THROW(1 / abacus::mat2(1), std::domain_error);

    // more generally, mat2(x) is the diagonal matrix Dx where all coefficients
    // outside the diagonal are zeros
    ASSERT_THROW(1 / abacus::mat2(0.707), std::domain_error);

    test_scalar_divided_by_matrix(abacus::vec2(2, 4), 1);
    test_scalar_divided_by_matrix(abacus::vec3(3, 9, 27), 4);
    test_scalar_divided_by_matrix(abacus::vec4(4, 16, 64, 256), 11);
    test_scalar_divided_by_matrix(abacus::mat2x2(5, 25, 125, 625), 1);
    test_scalar_divided_by_matrix(abacus::mat2x3(6, 36, 216, 1296, 7776, 46656), 3);
    test_scalar_divided_by_matrix(abacus::mat2x4(7, 49, 343, 2401, 16807, 117649, 823543, 5764801), 8);
    test_scalar_divided_by_matrix(abacus::mat3x2(8, 64, 512, 4096, 32768, 262144), 21);
    test_scalar_divided_by_matrix(abacus::mat3x3(9, 81, 729, 6561, 59049, 531441, 4782969, 43046721, 387420489), 55);
    test_scalar_divided_by_matrix(abacus::mat3x4(1.62, 2.62, 4.24, 6.85, 11.09, 17.94, 29.03, 46.98, 76.01, 122.99, 199.01, 322), 144);
    test_scalar_divided_by_matrix(abacus::mat4x2(-0.62, 0.38, -0.24, 0.15, -0.09, 0.06, -0.03, 0.02), 377);
    test_scalar_divided_by_matrix(abacus::mat4x3(0.79, 0.62, 0.48, 0.38, 0.3, 0.23, 0.18, 0.14, 0.11, 0.09, 0.07, 0.06), 987);
    test_scalar_divided_by_matrix(abacus::mat4x4(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1), 2584);
}

template<class matrix, class scalar>
void test_matrix_plus_equal_scalar(const matrix& m, scalar x)
{
    matrix sum(m);
    sum += x;
    for (abacus::index row = 0; row < m.rows(); ++row)
    {
        for (abacus::index column = 0; column < m.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(m.at(row, column) + static_cast<float>(x), sum.at(row, column));
        }
    }
}

TEST(matrix, matrix_plus_equal_scalar) { test_operator(test_matrix_plus_equal_scalar); }

template<class matrix, class scalar>
void test_matrix_minus_equal_scalar(const matrix& m, scalar x)
{
    matrix diff(m);
    diff -= x;
    for (abacus::index row = 0; row < m.rows(); ++row)
    {
        for (abacus::index column = 0; column < m.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(m.at(row, column) - static_cast<float>(x), diff.at(row, column));
        }
    }
}

TEST(matrix, matrix_minus_equal_scalar) { test_operator(test_matrix_minus_equal_scalar); }

template<class matrix, class scalar>
void test_matrix_times_equal_scalar(const matrix& m, scalar x)
{
    matrix diff(m);
    diff *= x;
    for (abacus::index row = 0; row < m.rows(); ++row)
    {
        for (abacus::index column = 0; column < m.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(m.at(row, column) * static_cast<float>(x), diff.at(row, column));
        }
    }
}

TEST(matrix, matrix_times_equal_scalar) { test_operator(test_matrix_times_equal_scalar); }

template<class matrix, class scalar>
void test_matrix_divided_by_equal_scalar(const matrix& m, scalar x)
{
    matrix diff(m);
    diff /= x;
    for (abacus::index row = 0; row < m.rows(); ++row)
    {
        for (abacus::index column = 0; column < m.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(m.at(row, column) / static_cast<float>(x), diff.at(row, column));
        }
    }
}

TEST(matrix, matrix_divided_by_equal_scalar)
{
    ASSERT_THROW(abacus::vec2() /= 0, std::domain_error);
    ASSERT_THROW(abacus::vec2() /= 0.f, std::domain_error);
    ASSERT_THROW(abacus::vec2() /= 0., std::domain_error);
    ASSERT_THROW(abacus::vec2() /= 0u, std::domain_error);
    ASSERT_THROW(abacus::vec2() /= 0l, std::domain_error);
    test_operator(test_matrix_divided_by_equal_scalar)
}

#undef test_operator

template<class matrix>
void test_matrix_plus_matrix(const matrix& a, const matrix& b)
{
    matrix sum = a + b;
    for (abacus::index row = 0; row < sum.rows(); ++row)
    {
        for (abacus::index column = 0; column < sum.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(a.at(row, column) + b.at(row, column), sum.at(row, column));
        }
    }
}

TEST(matrix, matrix_plus_matrix)
{
    test_matrix_plus_matrix(abacus::vec2(), abacus::vec2());
    test_matrix_plus_matrix(abacus::vec2(0), abacus::vec2(1));
    test_matrix_plus_matrix(abacus::vec2(1, 2), abacus::vec2(1, 2));
    test_matrix_plus_matrix(abacus::vec3(1, 3, 2), abacus::vec3(2, 1, 3));
    test_matrix_plus_matrix(abacus::vec4(1, 2, 2, 4), abacus::vec4(1, 3, 1, 3));

    test_matrix_plus_matrix(abacus::mat2x2(2, 2, 1, 4), abacus::mat2x2(2, 2, 3, 3));
    test_matrix_plus_matrix(abacus::mat2x3(1, 3, 1, 5, 2, 2), abacus::mat2x3(2, 4, 1, 2, 2, 4));
    test_matrix_plus_matrix(abacus::mat2x4(1, 3, 1, 3, 3, 2, 1, 5), abacus::mat2x4(2, 3, 2, 3, 1, 4, 2, 4));

    test_matrix_plus_matrix(abacus::mat3x2(2, 2, 1, 4, 1, 2), abacus::mat3x2(3, 6, 2, 3, 1, 3));
    test_matrix_plus_matrix(abacus::mat3x3(2, 3, 1, 5, 1, 2, 3, 3, 2), abacus::mat3x3(3, 1, 5, 4, 2, 1, 4, 2, 2));
    test_matrix_plus_matrix(abacus::mat3x4(2, 4, 1, 4, 2, 3, 2, 2, 2, 6, 1, 3),
      abacus::mat3x4(3, 4, 1, 3, 1, 4, 3, 2, 1, 5, 1, 3));

    test_matrix_plus_matrix(abacus::mat4x2(2, 5, 1, 3, 2, 5, 1, 3), abacus::mat4x2(2, 3, 3, 2, 2, 5, 2, 2));
    test_matrix_plus_matrix(abacus::mat4x3(2, 3, 3, 4, 1, 7, 2, 3, 1, 4, 2, 2),
      abacus::mat4x3(4, 4, 1, 3, 1, 4, 2, 2, 2, 6, 2, 2));
    test_matrix_plus_matrix(abacus::mat4x4(3, 3, 1, 4, 1, 4, 3, 3, 2, 4, 1, 2, 2, 6, 2, 5),
      abacus::mat4x4(1, 3, 3, 2, 1, 5, 2, 3, 3, 3, 1, 3, 3, 5, 2, 2));
}

template<class matrix>
void test_matrix_minus_matrix(const matrix& a, const matrix& b)
{
    matrix diff = a - b;
    for (abacus::index row = 0; row < diff.rows(); ++row)
    {
        for (abacus::index column = 0; column < diff.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(a.at(row, column) - b.at(row, column), diff.at(row, column));
        }
    }
}

TEST(matrix, matrix_minus_matrix)
{
    test_matrix_minus_matrix(abacus::vec2(), abacus::vec2());
    test_matrix_minus_matrix(abacus::vec2(0), abacus::vec2(1));
    test_matrix_minus_matrix(abacus::vec2(1, 2), abacus::vec2(1, 2));
    test_matrix_minus_matrix(abacus::vec3(1, 3, 2), abacus::vec3(2, 1, 3));
    test_matrix_minus_matrix(abacus::vec4(1, 2, 2, 4), abacus::vec4(1, 3, 1, 3));

    test_matrix_minus_matrix(abacus::mat2x2(2, 2, 1, 4), abacus::mat2x2(2, 2, 3, 3));
    test_matrix_minus_matrix(abacus::mat2x3(1, 3, 1, 5, 2, 2), abacus::mat2x3(2, 4, 1, 2, 2, 4));
    test_matrix_minus_matrix(abacus::mat2x4(1, 3, 1, 3, 3, 2, 1, 5), abacus::mat2x4(2, 3, 2, 3, 1, 4, 2, 4));

    test_matrix_minus_matrix(abacus::mat3x2(2, 2, 1, 4, 1, 2), abacus::mat3x2(3, 6, 2, 3, 1, 3));
    test_matrix_minus_matrix(abacus::mat3x3(2, 3, 1, 5, 1, 2, 3, 3, 2), abacus::mat3x3(3, 1, 5, 4, 2, 1, 4, 2, 2));
    test_matrix_minus_matrix(abacus::mat3x4(2, 4, 1, 4, 2, 3, 2, 2, 2, 6, 1, 3),
      abacus::mat3x4(3, 4, 1, 3, 1, 4, 3, 2, 1, 5, 1, 3));

    test_matrix_minus_matrix(abacus::mat4x2(2, 5, 1, 3, 2, 5, 1, 3), abacus::mat4x2(2, 3, 3, 2, 2, 5, 2, 2));
    test_matrix_minus_matrix(abacus::mat4x3(2, 3, 3, 4, 1, 7, 2, 3, 1, 4, 2, 2),
      abacus::mat4x3(4, 4, 1, 3, 1, 4, 2, 2, 2, 6, 2, 2));
    test_matrix_minus_matrix(abacus::mat4x4(3, 3, 1, 4, 1, 4, 3, 3, 2, 4, 1, 2, 2, 6, 2, 5),
      abacus::mat4x4(1, 3, 3, 2, 1, 5, 2, 3, 3, 3, 1, 3, 3, 5, 2, 2));
}

template<class vector>
void test_vector_times_vector(const vector& a, const vector& b)
{
    vector prod = a * b;
    for (abacus::index row = 0; row < prod.rows(); ++row)
    {
        for (abacus::index column = 0; column < prod.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(a.at(row, column) * b.at(row, column), prod.at(row, column));
        }
    }
}

TEST(matrix, vector_times_vector)
{
    test_vector_times_vector(abacus::vec2(), abacus::vec2());
    test_vector_times_vector(abacus::vec2(0), abacus::vec2(1));
    test_vector_times_vector(abacus::vec2(1, 2), abacus::vec2(1, 2));
    test_vector_times_vector(abacus::vec3(1, 3, 2), abacus::vec3(2, 1, 3));
    test_vector_times_vector(abacus::vec4(1, 2, 2, 4), abacus::vec4(1, 3, 1, 3));
}

TEST(matrix, matrix_product)
{
    EXPECT_EQ(abacus::mat2(), abacus::mat2() * abacus::mat2());
    EXPECT_EQ(abacus::mat2(1), abacus::mat2(1) * abacus::mat2(1));

    EXPECT_EQ(abacus::mat2(1, 0, 0, 0), abacus::mat2(0, 1, 0, 0) * abacus::mat2(0, 0, 1, 0));
    EXPECT_EQ(abacus::mat2(0, 0, 0, 1), abacus::mat2(0, 0, 1, 0) * abacus::mat2(0, 1, 0, 0));
    EXPECT_EQ(abacus::mat2(3, 4, 8, 11), abacus::mat2(1, 0, 2, -1) * abacus::mat2(3, 4, -2, -3));

    EXPECT_EQ(abacus::mat2(9, 7, 23, 9), abacus::mat2x3(1, 2, 0, 4, 3, -1) * abacus::mat3x2(5, 1, 2, 3, 3, 4));
    EXPECT_EQ(abacus::mat3(9, 13, -1, 14, 13, -3, 19, 18, -4),
      abacus::mat3x2(5, 1, 2, 3, 3, 4) * abacus::mat2x3(1, 2, 0, 4, 3, -1));
}

template<class matrix>
void test_matrix_plus_equal_matrix(const matrix& a, const matrix& b)
{
    matrix sum(a);
    sum += b;
    for (abacus::index row = 0; row < sum.rows(); ++row)
    {
        for (abacus::index column = 0; column < sum.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(a.at(row, column) + b.at(row, column), sum.at(row, column));
        }
    }
}

TEST(matrix, matrix_plus_equal_matrix)
{
    test_matrix_plus_equal_matrix(abacus::vec2(), abacus::vec2());
    test_matrix_plus_equal_matrix(abacus::vec2(0), abacus::vec2(1));
    test_matrix_plus_equal_matrix(abacus::vec2(1, 2), abacus::vec2(1, 2));
    test_matrix_plus_equal_matrix(abacus::vec3(1, 3, 2), abacus::vec3(2, 1, 3));
    test_matrix_plus_equal_matrix(abacus::vec4(1, 2, 2, 4), abacus::vec4(1, 3, 1, 3));

    test_matrix_plus_equal_matrix(abacus::mat2x2(2, 2, 1, 4), abacus::mat2x2(2, 2, 3, 3));
    test_matrix_plus_equal_matrix(abacus::mat2x3(1, 3, 1, 5, 2, 2), abacus::mat2x3(2, 4, 1, 2, 2, 4));
    test_matrix_plus_equal_matrix(abacus::mat2x4(1, 3, 1, 3, 3, 2, 1, 5), abacus::mat2x4(2, 3, 2, 3, 1, 4, 2, 4));

    test_matrix_plus_equal_matrix(abacus::mat3x2(2, 2, 1, 4, 1, 2), abacus::mat3x2(3, 6, 2, 3, 1, 3));
    test_matrix_plus_equal_matrix(abacus::mat3x3(2, 3, 1, 5, 1, 2, 3, 3, 2), abacus::mat3x3(3, 1, 5, 4, 2, 1, 4, 2, 2));
    test_matrix_plus_equal_matrix(abacus::mat3x4(2, 4, 1, 4, 2, 3, 2, 2, 2, 6, 1, 3),
      abacus::mat3x4(3, 4, 1, 3, 1, 4, 3, 2, 1, 5, 1, 3));

    test_matrix_plus_equal_matrix(abacus::mat4x2(2, 5, 1, 3, 2, 5, 1, 3), abacus::mat4x2(2, 3, 3, 2, 2, 5, 2, 2));
    test_matrix_plus_equal_matrix(abacus::mat4x3(2, 3, 3, 4, 1, 7, 2, 3, 1, 4, 2, 2),
      abacus::mat4x3(4, 4, 1, 3, 1, 4, 2, 2, 2, 6, 2, 2));
    test_matrix_plus_equal_matrix(abacus::mat4x4(3, 3, 1, 4, 1, 4, 3, 3, 2, 4, 1, 2, 2, 6, 2, 5),
      abacus::mat4x4(1, 3, 3, 2, 1, 5, 2, 3, 3, 3, 1, 3, 3, 5, 2, 2));
}

template<class matrix>
void test_matrix_minus_equal_matrix(const matrix& a, const matrix& b)
{
    matrix diff(a);
    diff -= b;
    for (abacus::index row = 0; row < diff.rows(); ++row)
    {
        for (abacus::index column = 0; column < diff.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(a.at(row, column) - b.at(row, column), diff.at(row, column));
        }
    }
}

TEST(matrix, matrix_minus_equal_matrix)
{
    test_matrix_minus_equal_matrix(abacus::vec2(), abacus::vec2());
    test_matrix_minus_equal_matrix(abacus::vec2(0), abacus::vec2(1));
    test_matrix_minus_equal_matrix(abacus::vec2(1, 2), abacus::vec2(1, 2));
    test_matrix_minus_equal_matrix(abacus::vec3(1, 3, 2), abacus::vec3(2, 1, 3));
    test_matrix_minus_equal_matrix(abacus::vec4(1, 2, 2, 4), abacus::vec4(1, 3, 1, 3));

    test_matrix_minus_equal_matrix(abacus::mat2x2(2, 2, 1, 4), abacus::mat2x2(2, 2, 3, 3));
    test_matrix_minus_equal_matrix(abacus::mat2x3(1, 3, 1, 5, 2, 2), abacus::mat2x3(2, 4, 1, 2, 2, 4));
    test_matrix_minus_equal_matrix(abacus::mat2x4(1, 3, 1, 3, 3, 2, 1, 5), abacus::mat2x4(2, 3, 2, 3, 1, 4, 2, 4));

    test_matrix_minus_equal_matrix(abacus::mat3x2(2, 2, 1, 4, 1, 2), abacus::mat3x2(3, 6, 2, 3, 1, 3));
    test_matrix_minus_equal_matrix(abacus::mat3x3(2, 3, 1, 5, 1, 2, 3, 3, 2), abacus::mat3x3(3, 1, 5, 4, 2, 1, 4, 2, 2));
    test_matrix_minus_equal_matrix(abacus::mat3x4(2, 4, 1, 4, 2, 3, 2, 2, 2, 6, 1, 3),
      abacus::mat3x4(3, 4, 1, 3, 1, 4, 3, 2, 1, 5, 1, 3));

    test_matrix_minus_equal_matrix(abacus::mat4x2(2, 5, 1, 3, 2, 5, 1, 3), abacus::mat4x2(2, 3, 3, 2, 2, 5, 2, 2));
    test_matrix_minus_equal_matrix(abacus::mat4x3(2, 3, 3, 4, 1, 7, 2, 3, 1, 4, 2, 2),
      abacus::mat4x3(4, 4, 1, 3, 1, 4, 2, 2, 2, 6, 2, 2));
    test_matrix_minus_equal_matrix(abacus::mat4x4(3, 3, 1, 4, 1, 4, 3, 3, 2, 4, 1, 2, 2, 6, 2, 5),
      abacus::mat4x4(1, 3, 3, 2, 1, 5, 2, 3, 3, 3, 1, 3, 3, 5, 2, 2));
}

template<class vector>
void test_vector_times_equal_vector(const vector& a, const vector& b)
{
    vector prod(a);
    prod *= b;
    for (abacus::index row = 0; row < prod.rows(); ++row)
    {
        for (abacus::index column = 0; column < prod.columns(); ++column)
        {
            EXPECT_FLOAT_EQ(a.at(row, column) * b.at(row, column), prod.at(row, column));
        }
    }
}

TEST(matrix, vector_times_equal_vector)
{
    test_vector_times_equal_vector(abacus::vec2(), abacus::vec2());
    test_vector_times_equal_vector(abacus::vec2(0), abacus::vec2(1));
    test_vector_times_equal_vector(abacus::vec2(1, 2), abacus::vec2(1, 2));
    test_vector_times_equal_vector(abacus::vec3(1, 3, 2), abacus::vec3(2, 1, 3));
    test_vector_times_equal_vector(abacus::vec4(1, 2, 2, 4), abacus::vec4(1, 3, 1, 3));
}

TEST(matrix, matrix_product_assignment)
{
    EXPECT_EQ(abacus::mat2(), abacus::mat2() *= abacus::mat2());
    EXPECT_EQ(abacus::mat2(1), abacus::mat2(1) *= abacus::mat2(1));

    EXPECT_EQ(abacus::mat2(1, 0, 0, 0), abacus::mat2(0, 1, 0, 0) *= abacus::mat2(0, 0, 1, 0));
    EXPECT_EQ(abacus::mat2(0, 0, 0, 1), abacus::mat2(0, 0, 1, 0) *= abacus::mat2(0, 1, 0, 0));
    EXPECT_EQ(abacus::mat2(3, 4, 8, 11), abacus::mat2(1, 0, 2, -1) *= abacus::mat2(3, 4, -2, -3));
}

TEST(matrix, row)
{
    abacus::mat4x3 m4x3;
    abacus::vec3& first_row = m4x3.row(0);
    EXPECT_EQ(abacus::vec3(), first_row);
    first_row.y = 10;
    EXPECT_EQ(10, m4x3.at(0, 1));
    m4x3.row(1) += first_row;
    EXPECT_FLOAT_EQ(10, m4x3.at(1, 1));
    m4x3.row(2) -= first_row + m4x3.row(1);
    EXPECT_FLOAT_EQ(-20, m4x3.at(2, 1));
    m4x3.row(2).at(2) = 22;
}

TEST(matrix, alignment)
{
    // alignment from Khronos Vulkan specs 14.6.4. Offset and Stride Assignment
    // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#interfaces-resources-layout
    EXPECT_EQ(2 * sizeof(float), sizeof(abacus::vec2));
    EXPECT_EQ(4 * sizeof(float), sizeof(abacus::vec3));
    EXPECT_EQ(4 * sizeof(float), sizeof(abacus::vec4));
    EXPECT_EQ(4 * sizeof(float), sizeof(abacus::mat2x2));
    EXPECT_EQ(8 * sizeof(float), sizeof(abacus::mat2x3));
    EXPECT_EQ(8 * sizeof(float), sizeof(abacus::mat2x4));
    EXPECT_EQ(6 * sizeof(float), sizeof(abacus::mat3x2));
    EXPECT_EQ(12 * sizeof(float), sizeof(abacus::mat3x3));
    EXPECT_EQ(12 * sizeof(float), sizeof(abacus::mat3x4));
    EXPECT_EQ(8 * sizeof(float), sizeof(abacus::mat4x2));
    EXPECT_EQ(16 * sizeof(float), sizeof(abacus::mat4x3));
    EXPECT_EQ(16 * sizeof(float), sizeof(abacus::mat4x4));
}

TEST(matrix, to_iostream)
{
    abacus::mat4x3 m4x3;
    EXPECT_EQ("mat4x3{(0, 0, 0) (0, 0, 0) (0, 0, 0) (0, 0, 0)}", (std::stringstream() << m4x3).str());
    abacus::vec2 v2(10, 20);
    EXPECT_EQ("vec2(10, 20)", (std::stringstream() << v2).str());
    abacus::vec2 v3(3, 5);
    EXPECT_EQ("vec2(3, 5)", (std::stringstream() << v3).str());
    abacus::mat3x3 m3x3(1, 2, 3, 4, 5, 6, 7, 8, 9);
    EXPECT_EQ("mat3x3{(1, 2, 3) (4, 5, 6) (7, 8, 9)}", (std::stringstream() << m3x3).str());
}