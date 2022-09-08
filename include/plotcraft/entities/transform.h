
#pragma once

#include <string>

#include "plotcraft/entities/point.h"
#include "plotcraft/entities/rect.h"

namespace plotcraft {
namespace entities {

struct Transform {
  static Transform Identity() {
    return Transform{
        .a11 = 1.0f,
        .a13 = 0.0f,
        .a22 = 1.0f,
        .a23 = 0.0f,
    };
  }

  static Transform FromRectToRect(const Rect& to, const Rect& from) {
    // 0.1 -> (left - axes.box.left)*figure.box.width/axes.box +
    // figure.box_left
    return Transform{
        .a11 = to.width / from.width,
        .a13 = to.left - from.left * to.width / from.width,
        .a22 = to.height / from.height,
        .a23 = to.bottom - from.bottom * to.height / from.height,
    };
  }
  double ForwardX(double x) const {
    // clang-format off
    return x * a11 /*+  p.y * a12 .. */ + a13;
    // clang-format on
  };

  double ForwardY(double y) const {
    // clang-format off
    return /*p.x * a21 + */ y * a22 + a23;
    // clang-format on
  };

  Point Forward(const Point& p) const {
    Point ret(
        // clang-format off
        ForwardX(p.x),
        ForwardY(p.y)
        // clang-format on
    );

    return ret;
  };

  double a11 = 0.0f;
  double a13 = 0.0f;
  double a22 = 0.0f;
  double a23 = 0.0f;
};

}  // namespace entities
}  // namespace plotcraft
