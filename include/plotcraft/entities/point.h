
#pragma once

#include <string>

namespace plotcraft {
namespace entities {

class Point {
 public:
  Point() : x(0.0), y(0.0) {}
  Point(double px, double py) : x(px), y(py) {}
  Point(const Point& point) : x(point.x), y(point.y) {}
  Point& operator=(const Point& other) {
    if (this != &other) {
      this->x = other.x;
      this->y = other.y;
    }

    return *this;
  }
  double x;
  double y;
};

}  // namespace entities
}  // namespace plotcraft
