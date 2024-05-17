#include "../src/lib/MyParser.h"
#include <gtest/gtest.h>

TEST(ParseShapeDataTest, CircleParsing) 
{
    std::string input = "circle (1.0 2.0, 3.0, 255 0 0)";
    ShapeData data = parseShapeData(input);
    ASSERT_EQ(data.type, ShapeType::Circle);
    ASSERT_EQ(data.name, "Circle");
    ASSERT_EQ(data.center.x, 1.0);
    ASSERT_EQ(data.center.y, 2.0);
    ASSERT_EQ(data.radius, 3.0);
    ASSERT_EQ(data.color.r, 255);
    ASSERT_EQ(data.color.g, 0);
    ASSERT_EQ(data.color.b, 0);
}

TEST(ParseShapeDataTest, TriangleParsing) 
{
    std::string input = "triangle (1.0 2.0, 3.0 4.0, 5.0 6.0, 255 255 0)";
    ShapeData data = parseShapeData(input);
    ASSERT_EQ(data.type, ShapeType::Triangle);
    ASSERT_EQ(data.name, "Triangle");
    ASSERT_EQ(data.vertices.size(), 3);
    ASSERT_EQ(data.vertices[0].x, 1.0);
    ASSERT_EQ(data.vertices[0].y, 2.0);
    ASSERT_EQ(data.vertices[1].x, 3.0);
    ASSERT_EQ(data.vertices[1].y, 4.0);
    ASSERT_EQ(data.vertices[2].x, 5.0);
    ASSERT_EQ(data.vertices[2].y, 6.0);
    ASSERT_EQ(data.color.r, 255);
    ASSERT_EQ(data.color.g, 255);
    ASSERT_EQ(data.color.b, 0);
}

TEST(ParseShapeDataTest, PolygonParsing) 
{
    std::string input = "polygon (4, 1.0 2.0, 3.0 4.0, 5.0 6.0, 7.0 8.0, 255 0 255)";
    ShapeData data = parseShapeData(input);
    ASSERT_EQ(data.type, ShapeType::Polygon);
    ASSERT_EQ(data.name, "Polygon");
    ASSERT_EQ(data.vertices.size(), 4); // Предположим, что в многоугольнике 4 вершины
    ASSERT_EQ(data.vertices[0].x, 1.0);
    ASSERT_EQ(data.vertices[0].y, 2.0);
    ASSERT_EQ(data.vertices[1].x, 3.0);
    ASSERT_EQ(data.vertices[1].y, 4.0);
    ASSERT_EQ(data.vertices[2].x, 5.0);
    ASSERT_EQ(data.vertices[2].y, 6.0);
    ASSERT_EQ(data.vertices[3].x, 7.0);
    ASSERT_EQ(data.vertices[3].y, 8.0);
    ASSERT_EQ(data.color.r, 255);
    ASSERT_EQ(data.color.g, 0);
    ASSERT_EQ(data.color.b, 255);
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}