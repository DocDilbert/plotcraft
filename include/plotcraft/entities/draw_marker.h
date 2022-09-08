
#pragma once
#include <spdlog/spdlog.h>

#include <string>

#include "plotcraft/entities/i_draw_primitives.h"
#include "plotcraft/entities/line.h"
#include "plotcraft/entities/marker_style.h"
#include "plotcraft/entities/point.h"

namespace plotcraft {
namespace entities {

class DrawMarker {
 public:
  DrawMarker(IDrawPrimitives& draw_primitives) : draw_primitives_(draw_primitives) {}

  void DrawCross(const Point& marker_pos, double size) {
    auto left_h = Point(marker_pos.x - size, marker_pos.y);
    auto right_h = Point(marker_pos.x + size, marker_pos.y);
    auto line_h = Line(left_h, right_h);

    auto top_v = Point(marker_pos.x, marker_pos.y + size);
    auto bottom_v = Point(marker_pos.x, marker_pos.y - size);
    auto line_v = Line(top_v, bottom_v);

    draw_primitives_.DrawLine(line_h);
    draw_primitives_.DrawLine(line_v);
  }

  void DrawSquare(const Point& marker_pos, double size) {
    auto rect = Rect(marker_pos.x - size, marker_pos.y - size, 2.0 * size, 2.0 * size);
    draw_primitives_.DrawRect(rect);
  }

  void Draw(const Point& marker_pos, MarkerStyle markerstyle, double size) {
    switch (markerstyle) {
      case MarkerStyle::kPlus:
        DrawCross(marker_pos, size);
        break;
      case MarkerStyle::kSquare:
        DrawSquare(marker_pos, size);
        break;
      default:
        break;
    }
  }

 private:
  IDrawPrimitives& draw_primitives_;
};

}  // namespace entities
}  // namespace plotcraft
