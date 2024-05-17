#include "../lib/ErrorCheck.hpp"

using namespace sf;

int main(int args, char *argv[]) {
  std::string line;

  Parser ErrorCheck;
  ShapeData circleData[10];
  int countCircles = 0;

  ShapeData triangleData[10];
  int countTriangles = 0;

  ShapeData polygonData[10];
  int countPolygons = 0;

  bool entered = false;

  if (args != 2) {
    char ch = 'a';
    while (ch != 'q') {
      std::cout << "Введите букву 'w', чтобы добавить фигуру "
                   "в WKT формате\nВведите букву 'h', если "
                   "хотите узнать как работать с приложением\n"
                   "Введите букву 'q', если хотите прекратить "
                   "ввод фигур"
                << std::endl;
      std::cin >> ch;
      std::cin.ignore();
      entered = true;
      if (ch == 'w') {
        std::cout << "Введите фигуру и ее параметры в формате wkt: ";
        std::getline(std::cin, line);
        if (line[0] == 'c') {
          circleData[countCircles] = parseShapeData(line);
          if (ErrorCheck.parse_circle(circleData[countCircles])) {
            countCircles++;
          };
        } else if (line[0] == 't') {
          triangleData[countTriangles] = parseShapeData(line);
          if (ErrorCheck.parse_triangle(triangleData[countTriangles])) {
            countTriangles++;
          };
        } else if (line[0] == 'p') {
          polygonData[countPolygons] = parseShapeData(line);
          if (ErrorCheck.parse_polygon(polygonData[countPolygons])) {
            countPolygons++;
          }
        }
      } else if (ch == 'h') {
        std::cout << "\n\nПример ввода фигур в WKT формате:\n\ncircle "
                     "(1200 "
                     "600, 140.0, 80 0 40)"
                     "\ntriangle (300 450, 800 300, 130 60, 0 200 180)"
                     "\npolygon (6, 300 450, 450 600, 600 750, 750 "
                     "600, 900 450, 600 150, 255 255 255)"
                  << std::endl;
        std::cout << "\nГде:\n\n"
                     "circle - окружность (x y - координаты, r - радиус"
                     ", r g b - цвет в формате RGB)\n\n"
                     "triangle - треугольник (x y, - координаты "
                     "вершины 1, x y - координаты вершины 2, x y - "
                     "координаты вершины 3, r g b - цвет в формате RGB)"
                     "\n\npolygon - полигон или многоульник (n - коли"
                     "чество вершин, x y - координаты n вершин, r g b "
                     "- цвет в формате RGB)\n\n"
                  << std::endl;
        std::cout << "Код цвета имеет значения от 0 до 255 включительно."
                     "\nКоординаты не могут иметь "
                     "отрицательные значения\nРазрешение окна 1500 x 900 "
                     "точек.\nВвод в программу осуществляется при "
                     "помощи стандартного потока ввода или указания "
                     "текстового файла,\nкак аргумента при запуске "
                     "программы (текстовый файл находится в "
                     "директории с программой,\nлибо вы указываете "
                     "путь до этого файла при запуске программы)\n\n"
                  << std::endl;
      } else if (ch == 'q') {
        break;
      }
    }
  }
  std::ifstream file(argv[1]);

  if (!file.is_open() & !entered) {
    std::cout << "Ошибка: файл не найден" << std::endl;
    return 1;
  }

  while (std::getline(file, line)) {
    if (line[0] == 'c') {
      circleData[countCircles] = parseShapeData(line);
      if (ErrorCheck.parse_circle(circleData[countCircles])) {
        countCircles++;
      };
    } else if (line[0] == 't') {
      triangleData[countTriangles] = parseShapeData(line);
      if (ErrorCheck.parse_triangle(triangleData[countTriangles])) {
        countTriangles++;
      };
    } else if (line[0] == 'p') {
      polygonData[countPolygons] = parseShapeData(line);
      if (ErrorCheck.parse_polygon(polygonData[countPolygons])) {
        countPolygons++;
      }
    }
    std::cout << "\nНажмите \"Enter\" чтобы продолжить" << std::endl;
    getchar();
  }

  RenderWindow window(VideoMode(1500, 900), L"МОЙ ЛЮБИМЫЙ ПАРСЕР",
                      Style::Titlebar);

  CircleShape circle(0);

  CircleShape triangle(100);

  for (int i = 0; i < countCircles; i++) {
    circle.setPosition(circleData[i].center.x, circleData[i].center.y);
    circle.setRadius(circleData[i].radius);
    circle.setFillColor(sf::Color(circleData[i].color.r, circleData[i].color.g,
                                  circleData[i].color.b));
    window.draw(circle);
  }

  ConvexShape triangleShape;
  triangleShape.setPointCount(3);
  Vector2f points[3];
  for (int i = 0; i < countTriangles; i++) {
    for (int j = 0; j < 3; j++) {
      points[j].x = triangleData[i].vertices[j].x;
      points[j].y = triangleData[i].vertices[j].y;
      triangleShape.setPoint(j, points[j]);
      triangleShape.setFillColor(sf::Color(triangleData[i].color.r,
                                           triangleData[i].color.g,
                                           triangleData[i].color.b));
    }
    window.draw(triangleShape);
  }

  ConvexShape polygon;
  for (int i = 0; i < countPolygons; i++) {
    for (int j = 0; j < polygonData[i].vertices.size(); i++) {
      polygon.setPointCount(polygonData[i].vertices.size());
      for (int k = 0; k < polygonData[i].vertices.size(); k++) {
        polygon.setPoint(k, Vector2f(polygonData[i].vertices[k].x,
                                     polygonData[i].vertices[k].y));
      }
      polygon.setFillColor(sf::Color(polygonData[i].color.r,
                                     polygonData[i].color.g,
                                     polygonData[i].color.b));
      window.draw(polygon);
    }
  }

  window.display();

  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
      }
    }
  }
  return 0;
}
