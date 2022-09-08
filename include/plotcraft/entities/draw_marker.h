
#pragma once
#include <spdlog/spdlog.h>

#include <string>

#include "plotcraft/entities/i_draw_primitives.h"
#include "plotcraft/entities/line.h"
#include "plotcraft/entities/point.h"

namespace plotcraft {
namespace entities {

class DrawMarker {
 public:
  DrawMarker() = delete;
  ~DrawMarker() = delete;

  static void DrawCross(IDrawPrimitives& draw_primitives, const Point& marker_pos, double size) {
    auto left_h = Point(marker_pos.x - size, marker_pos.y);
    auto right_h = Point(marker_pos.x + size, marker_pos.y);
    auto line_h = Line(left_h, right_h);

    auto top_v = Point(marker_pos.x, marker_pos.y + size);
    auto bottom_v = Point(marker_pos.x, marker_pos.y - size);
    auto line_v = Line(top_v, bottom_v);

    draw_primitives.DrawLine(line_h);
    draw_primitives.DrawLine(line_v);
  }

  static void DrawRect(IDrawPrimitives& draw_primitives, const Point& marker_pos, double size) {
    auto rect = Rect(marker_pos.x - size, marker_pos.y - size, 2.0 * size, 2.0 * size);
    draw_primitives.DrawRect(rect);
  }
};

}  // namespace entities
}  // namespace plotcraft
