#pragma once

#include <string>

#include "plotcraft/entities/point.h"

namespace plotcraft {
namespace entities {

struct Rect {
  Rect() : left(0.0), bottom(0.0), width(0.0), height(0.0) {}

  Rect(double pleft, double pbottom, double pwidth, double pheight) : left(pleft), bottom(pbottom), width(pwidth), height(pheight) {}

  Rect(const Rect& rect) : left(rect.left), bottom(rect.bottom), width(rect.width), height(rect.height) {}

  Rect& operator=(const Rect& other) {
    if (this != &other) {
      this->left = other.left;
      this->bottom = other.bottom;
      this->width = other.width;
      this->height = other.height;
    }

    return *this;
  }
  bool Contains(double x, double y) const {
    if ((x < left) || (x > (left + width))) {
      return false;
    }
    if ((y < bottom) || (y > (bottom + height))) {
      return false;
    }
    return true;
  }

  bool Contains(const Point& p) const { return Contains(p.x, p.y); }

  Point GetBottomLeft() const { return Point(left, bottom); }
  Point GetBottomRight() const { return Point(left + width, bottom); }
  Point GetTopLeft() const { return Point(left, bottom + height); }
  Point GetTopRight() const { return Point(left + width, bottom + height); }

  double GetLeft() const { return left; }
  double GetRight() const { return left + width; }
  double GetBottom() const { return bottom; }
  double GetTop() const { return bottom + height; }
  double GetWidth() const { return width; }
  double GetHeight() const { return height; }

  /**
   * distance from the left edge of the display to the left edge of the
   * figure
   */
  double left;

  /**
   * distance from the bottom edge of the primary display to the bottom
   * edge of the figure
   */
  double bottom;

  /**
   * distance between the right and left edge of the figure
   */
  double width;

  /**
   * distance between the top and bottom edge of the figure
   */
  double height;
};
}  // namespace entities
}  // namespace plotcraft
