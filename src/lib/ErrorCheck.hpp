#include "../lib/MyParser.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>
#include <fstream>
#include <iostream>

class Parser {
public:
  bool parse_circle(ShapeData circle);

  bool parse_triangle(ShapeData triangle);

  bool parse_polygon(ShapeData polygon);

  void error_check(int rad, int c_x, int c_y, int color_r, int color_g,
                   int color_b);

  void program_stop(int type_error);

  void trinagle_error_check(std::vector<coordinate> v);

  void polygon_error_check(int size, std::vector<coordinate> v);
};
