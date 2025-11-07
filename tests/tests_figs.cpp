#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include <cmath>
#include "../include/point.hpp"
#include "../include/array.hpp"
#include "../include/pentagon.hpp"
#include "../include/hexagon.hpp"
#include "../include/octagon.hpp"
#include "../src/point.cpp"
#include "../src/figure.cpp"
#include "../src/pentagon.cpp"
#include "../src/hexagon.cpp"
#include "../src/octagon.cpp"
#include "../src/array.cpp"

// Test fixture for Figures
template<typename T>
class FigureTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup for all tests
    }
    
    void TearDown() override {
        // Clean up after each test
    }
};

using NumericTypes = ::testing::Types<int, float, double, long double>;
TYPED_TEST_SUITE(FigureTest, NumericTypes);

// Point tests
TYPED_TEST(FigureTest, PointCreation) {
    Point<TypeParam> p1(1, 2);
    Point<TypeParam> p2(3, 4);
    
    EXPECT_EQ(p1.getX(), 1);
    EXPECT_EQ(p1.getY(), 2);
    EXPECT_EQ(p2.getX(), 3);
    EXPECT_EQ(p2.getY(), 4);
}

TYPED_TEST(FigureTest, PointEquality) {
    Point<TypeParam> p1(1, 2);
    Point<TypeParam> p2(1, 2);
    Point<TypeParam> p3(3, 4);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TYPED_TEST(FigureTest, PointOutput) {
    Point<TypeParam> p(1, 2);
    std::stringstream ss;
    ss << p;
    
    EXPECT_EQ(ss.str(), "(1, 2)");
}

// Pentagon tests
TYPED_TEST(FigureTest, PentagonCreation) {
    Point<TypeParam> center(0, 0);
    Pentagon<TypeParam> pentagon(center, 5);
    
    EXPECT_EQ(pentagon.center().getX(), 0);
    EXPECT_EQ(pentagon.center().getY(), 0);
}

TYPED_TEST(FigureTest, PentagonArea) {
    Point<TypeParam> center(0, 0);
    Pentagon<TypeParam> pentagon(center, 1);
    
    double expected_area = (5 * 2 * std::sin(M_PI / 5) * std::cos(M_PI / 5))/2;
    double actual_area = pentagon.area();
    
    EXPECT_NEAR(actual_area, expected_area, 1e-6);
}

TYPED_TEST(FigureTest, PentagonEquality) {
    Point<TypeParam> center1(0, 0);
    Point<TypeParam> center2(1, 1);
    
    Pentagon<TypeParam> p1(center1, 5);
    Pentagon<TypeParam> p2(center1, 5);
    Pentagon<TypeParam> p3(center2, 5);
    Pentagon<TypeParam> p4(center1, 10);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_FALSE(p1 == p4);
}

TYPED_TEST(FigureTest, PentagonReadWrite) {
    std::stringstream input("0 0 5");
    Pentagon<TypeParam> pentagon;
    
    EXPECT_NO_THROW(pentagon.read(input));
    
    std::stringstream output;
    pentagon.print(output);
    
    EXPECT_TRUE(output.str().find("Pentagon") != std::string::npos);
    EXPECT_TRUE(output.str().find("Center(0, 0)") != std::string::npos);
}

// Hexagon tests
TYPED_TEST(FigureTest, HexagonCreation) {
    Point<TypeParam> center(1, 1);
    Hexagon<TypeParam> hexagon(center, 3);
    
    EXPECT_EQ(hexagon.center().getX(), 1);
    EXPECT_EQ(hexagon.center().getY(), 1);
}

TYPED_TEST(FigureTest, HexagonArea) {
    Point<TypeParam> center(0, 0);
    Hexagon<TypeParam> hexagon(center, 1);
    
    double expected_area = (3 * std::sqrt(3) * 1 * 1) / 2;
    double actual_area = hexagon.area();
    
    EXPECT_NEAR(actual_area, expected_area, 1e-6);
}

TYPED_TEST(FigureTest, HexagonEquality) {
    Point<TypeParam> center1(0, 0);
    Point<TypeParam> center2(2, 2);
    
    Hexagon<TypeParam> h1(center1, 3);
    Hexagon<TypeParam> h2(center1, 3);
    Hexagon<TypeParam> h3(center2, 3);
    
    EXPECT_TRUE(h1 == h2);
    EXPECT_FALSE(h1 == h3);
}

TYPED_TEST(FigureTest, HexagonReadWrite) {
    std::stringstream input("1 1 3");
    Hexagon<TypeParam> hexagon;
    
    EXPECT_NO_THROW(hexagon.read(input));
    
    std::stringstream output;
    hexagon.print(output);
    
    EXPECT_TRUE(output.str().find("Hexagon") != std::string::npos);
    EXPECT_TRUE(output.str().find("Center(1, 1)") != std::string::npos);
}

// Octagon tests
TYPED_TEST(FigureTest, OctagonCreation) {
    Point<TypeParam> center(2, 2);
    Octagon<TypeParam> octagon(center, 4);
    
    EXPECT_EQ(octagon.center().getX(), 2);
    EXPECT_EQ(octagon.center().getY(), 2);
}

TYPED_TEST(FigureTest, OctagonArea) {
    Point<TypeParam> center(0, 0);
    Octagon<TypeParam> octagon(center, 1);
    
    double side = 2 * 1 * std::sin(M_PI / 8);
    double apothem = 1 * std::cos(M_PI / 8);
    double expected_area = (8 * side * apothem) / 2;
    double actual_area = octagon.area();
    
    EXPECT_NEAR(actual_area, expected_area, 1e-6);
}

TYPED_TEST(FigureTest, OctagonEquality) {
    Point<TypeParam> center1(0, 0);
    Point<TypeParam> center2(3, 3);
    
    Octagon<TypeParam> o1(center1, 4);
    Octagon<TypeParam> o2(center1, 4);
    Octagon<TypeParam> o3(center2, 4);
    
    EXPECT_TRUE(o1 == o2);
    EXPECT_FALSE(o1 == o3);
}

TYPED_TEST(FigureTest, OctagonReadWrite) {
    std::stringstream input("2 2 4");
    Octagon<TypeParam> octagon;
    
    EXPECT_NO_THROW(octagon.read(input));
    
    std::stringstream output;
    octagon.print(output);
    
    EXPECT_TRUE(output.str().find("Octagon") != std::string::npos);
    EXPECT_TRUE(output.str().find("Center(2, 2)") != std::string::npos);
}

// Array tests
class ArrayTest : public ::testing::Test {
protected:
    void SetUp() override {
        pentagon = std::make_shared<Pentagon<int>>(Point<int>(0, 0), 5);
        hexagon = std::make_shared<Hexagon<int>>(Point<int>(1, 1), 3);
        octagon = std::make_shared<Octagon<int>>(Point<int>(2, 2), 4);
    }
    
    std::shared_ptr<Figure<int>> pentagon;
    std::shared_ptr<Figure<int>> hexagon;
    std::shared_ptr<Figure<int>> octagon;
};

TEST_F(ArrayTest, ArrayCreation) {
    Array<std::shared_ptr<Figure<int>>> array;
    
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 10);
}

TEST_F(ArrayTest, ArrayAdd) {
    Array<std::shared_ptr<Figure<int>>> array;
    
    array.add(pentagon);
    array.add(hexagon);
    array.add(octagon);
    
    EXPECT_EQ(array.size(), 3);
}

TEST_F(ArrayTest, ArrayRemove) {
    Array<std::shared_ptr<Figure<int>>> array;
    
    array.add(pentagon);
    array.add(hexagon);
    array.add(octagon);
    
    array.remove(1); // Remove hexagon
    
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array[0], pentagon);
    EXPECT_EQ(array[1], octagon);
}

TEST_F(ArrayTest, ArrayRemoveInvalidIndex) {
    Array<std::shared_ptr<Figure<int>>> array;
    
    array.add(pentagon);
    
    EXPECT_THROW(array.remove(5), std::out_of_range);
    EXPECT_THROW(array.remove(-1), std::out_of_range);
}

TEST_F(ArrayTest, ArrayIndexOperator) {
    Array<std::shared_ptr<Figure<int>>> array;
    
    array.add(pentagon);
    array.add(hexagon);
    
    EXPECT_EQ(array[0], pentagon);
    EXPECT_EQ(array[1], hexagon);
}

TEST_F(ArrayTest, ArrayIndexOperatorInvalid) {
    Array<std::shared_ptr<Figure<int>>> array;
    
    array.add(pentagon);
    
    EXPECT_THROW(array[5], std::out_of_range);
    EXPECT_THROW(array[-1], std::out_of_range);
}

TEST_F(ArrayTest, ArrayTotalArea) {
    Array<std::shared_ptr<Figure<int>>> array;
    
    array.add(pentagon);
    array.add(hexagon);
    array.add(octagon);
    
    double total = array.totalArea();
    double expected = pentagon->area() + hexagon->area() + octagon->area();
    
    EXPECT_NEAR(total, expected, 1e-6);
}

TEST_F(ArrayTest, ArrayTotalAreaEmpty) {
    Array<std::shared_ptr<Figure<int>>> array;
    
    double total = array.totalArea();
    
    EXPECT_EQ(total, 0.0);
}

TEST_F(ArrayTest, ArrayResize) {
    Array<std::shared_ptr<Figure<int>>> array;
    
    // Add more than initial capacity (10)
    for (int i = 0; i < 15; ++i) {
        auto fig = std::make_shared<Pentagon<int>>(Point<int>(i, i), i+1);
        array.add(fig);
    }
    
    EXPECT_EQ(array.size(), 15);
    EXPECT_GE(array.capacity(), 15);
}

TEST_F(ArrayTest, ArrayMoveSemantics) {
    Array<std::shared_ptr<Figure<int>>> array1;
    array1.add(pentagon);
    array1.add(hexagon);
    
    Array<std::shared_ptr<Figure<int>>> array2(std::move(array1));
    
    EXPECT_EQ(array2.size(), 2);
    EXPECT_EQ(array1.size(), 0);
    EXPECT_EQ(array1.capacity(), 0);
}

// Exception tests
TEST(FigureExceptionTest, PentagonInvalidInput) {
    Pentagon<int> pentagon;
    std::stringstream invalid_input1("abc");
    std::stringstream invalid_input2("0 0 -5");
    std::stringstream invalid_input3("inf inf 5");
    
    EXPECT_THROW(pentagon.read(invalid_input1), std::runtime_error);
    EXPECT_THROW(pentagon.read(invalid_input2), std::invalid_argument);
}

TEST(FigureExceptionTest, HexagonInvalidInput) {
    Hexagon<int> hexagon;
    std::stringstream invalid_input1("abc");
    std::stringstream invalid_input2("0 0 -3");
    
    EXPECT_THROW(hexagon.read(invalid_input1), std::runtime_error);
    EXPECT_THROW(hexagon.read(invalid_input2), std::invalid_argument);
}

TEST(FigureExceptionTest, OctagonInvalidInput) {
    Octagon<int> octagon;
    std::stringstream invalid_input1("abc");
    std::stringstream invalid_input2("0 0 -4");
    
    EXPECT_THROW(octagon.read(invalid_input1), std::runtime_error);
    EXPECT_THROW(octagon.read(invalid_input2), std::invalid_argument);
}

// Clone tests
TEST(FigureCloneTest, PentagonClone) {
    auto pentagon = std::make_shared<Pentagon<int>>(Point<int>(0, 0), 5);
    auto cloned = pentagon->clone();
    
    EXPECT_TRUE(*pentagon == *cloned);
    EXPECT_NE(pentagon.get(), cloned.get());
}

TEST(FigureCloneTest, HexagonClone) {
    auto hexagon = std::make_shared<Hexagon<int>>(Point<int>(1, 1), 3);
    auto cloned = hexagon->clone();
    
    EXPECT_TRUE(*hexagon == *cloned);
    EXPECT_NE(hexagon.get(), cloned.get());
}

TEST(FigureCloneTest, OctagonClone) {
    auto octagon = std::make_shared<Octagon<int>>(Point<int>(2, 2), 4);
    auto cloned = octagon->clone();
    
    EXPECT_TRUE(*octagon == *cloned);
    EXPECT_NE(octagon.get(), cloned.get());
}

// Mixed figures in array test
TEST(MixedFiguresTest, DifferentFiguresInArray) {
    Array<std::shared_ptr<Figure<int>>> array;
    
    auto pentagon = std::make_shared<Pentagon<int>>(Point<int>(0, 0), 5);
    auto hexagon = std::make_shared<Hexagon<int>>(Point<int>(1, 1), 3);
    auto octagon = std::make_shared<Octagon<int>>(Point<int>(2, 2), 4);
    
    array.add(pentagon);
    array.add(hexagon);
    array.add(octagon);
    
    EXPECT_EQ(array.size(), 3);
    
    // Test that each figure maintains its type
    EXPECT_NEAR(array[0]->area(), pentagon->area(), 1e-6);
    EXPECT_NEAR(array[1]->area(), hexagon->area(), 1e-6);
    EXPECT_NEAR(array[2]->area(), octagon->area(), 1e-6);
}

// Performance test for large arrays
TEST(ArrayPerformanceTest, LargeArray) {
    Array<std::shared_ptr<Figure<int>>> array;
    
    const int NUM_FIGURES = 1000;
    for (int i = 0; i < NUM_FIGURES; ++i) {
        auto pentagon = std::make_shared<Pentagon<int>>(Point<int>(i, i), i % 10 + 1);
        array.add(pentagon);
    }
    
    EXPECT_EQ(array.size(), NUM_FIGURES);
    
    // Ensure we can calculate total area without crashing
    double total = array.totalArea();
    EXPECT_GT(total, 0.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}