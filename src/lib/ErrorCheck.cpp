#include "ErrorCheck.hpp"

void Parser::error_check(int rad, int c_x, int c_y, int color_r, int color_g,
                         int color_b) {
  if (rad < 0) {
    Parser::program_stop(0);
  }
  if (c_x < 0) {
    Parser::program_stop(1);
  }
  if (c_y < 0) {
    Parser::program_stop(2);
  }
  if (color_r < 0 || color_g < 0 || color_b < 0) {
    Parser::program_stop(3);
  }
  if (color_r > 255 || color_g > 255 || color_b > 255) {
    Parser::program_stop(4);
  }
}

void Parser::program_stop(int type_error) {
  switch (type_error) {
  case 0:
    std::cout << "Ошибка ввода: радиус не может быть меньше нуля" << std::endl;
    exit(0);
    break;
  case 1:
    std::cout << "Ошибка ввода: координата X не может быть меньше нуля"
              << std::endl;
    exit(0);
    break;
  case 2:
    std::cout << "Ошибка ввода: координата Y не может быть меньше нуля"
              << std::endl;
    exit(0);
    break;
  case 3:
    std::cout << "Ошибка ввода: код цвета не может быть меньше нуля"
              << std::endl;
    exit(0);
    break;
  case 4:
    std::cout << "Ошибка ввода: код цвета не может быть больше 255"
              << std::endl;
    exit(0);
    break;
  }
}

void Parser::trinagle_error_check(std::vector<coordinate> v) {
  for (int i = 0; i < 3; i++) {
    if (v[i].x < 0) {
      Parser::program_stop(1);
    }
    if (v[i].y < 0) {
      Parser::program_stop(2);
    }
  }
}

void Parser::polygon_error_check(int size, std::vector<coordinate> v) {
  for (int i = 0; i < size; i++) {
    if (v[i].x < 0) {
      Parser::program_stop(1);
    }
    if (v[i].y < 0) {
      Parser::program_stop(2);
    }
  }
}

bool Parser::parse_circle(ShapeData circle) {
  Parser::error_check(circle.radius, circle.center.x, circle.center.y,
                      circle.color.r, circle.color.g, circle.color.b);
  std::cout << "Проверка на корректность введенных данных прошла "
               "успешна..."
            << std::endl;
  std::cout << "\nПериметр вашей окружности: "
            << float(2.0 * 3.14 * circle.radius) << std::endl;
  std::cout << "\nПлощадь ваше окружности: "
            << float(3.14 * (circle.radius * circle.radius)) << std::endl;
  return true;
}

bool Parser::parse_triangle(ShapeData triangle) {
  Parser::trinagle_error_check(triangle.vertices);
  Parser::error_check(20, 30, 30, triangle.color.r, triangle.color.g,
                      triangle.color.b);
  std::cout << "Проверка на корректность введенных данных прошла "
               "успешна...\n"
            << std::endl;
  float a =
      std::sqrt(std::pow(triangle.vertices[1].x - triangle.vertices[0].x, 2) +
                std::pow((triangle.vertices[1].y - triangle.vertices[0].y), 2));

  float b =
      std::sqrt(std::pow(triangle.vertices[2].x - triangle.vertices[1].x, 2) +
                std::pow((triangle.vertices[2].y - triangle.vertices[1].y), 2));
  float c =
      std::sqrt(std::pow(triangle.vertices[2].x - triangle.vertices[0].x, 2) +
                std::pow((triangle.vertices[2].y - triangle.vertices[0].y), 2));
  std::cout << "Периметр вашего треугольник: " << (a + b + c) << std::endl;
  float s = (a + b + c) / 2;
  std::cout << "\nПлощадь вашего треугольника: "
            << (s * (s - a) * (s - b) * (s - c)) / 1000000 << std::endl;
  return true;
}

bool Parser::parse_polygon(ShapeData polygon) {
  Parser::polygon_error_check(polygon.vertices.size(), polygon.vertices);
  Parser::error_check(30, 100, 100, polygon.color.r, polygon.color.g,
                      polygon.color.b);
  std::cout << "Проверка на корректность введенных данных прошла "
               "успешна...\n"
            << std::endl;
  int *arr = new int(polygon.vertices.size());
  for (int i = 0; i < polygon.vertices.size(); i++) {
    arr[i] =
        std::sqrt(std::pow(polygon.vertices[1].x - polygon.vertices[0].x, 2) +
                  std::pow(polygon.vertices[1].y - polygon.vertices[0].y, 2));
  }
  size_t per = 0;
  for (int i = 0; i < polygon.vertices.size(); i++) {
    per += arr[i];
  }
  std::cout << "Периметр вашего полигона: " << per << std::endl;
  std::cout << "\nПлощадь вашего полигона: "
            << (per * (per - arr[0]) * (per - arr[1]) * (per - arr[2])) /
                   1000000
            << std::endl;
  return true;
}