#pragma once

#include <spdlog/spdlog.h>

#include <string>

#include "plotcraft/entities/line.h"
#include "plotcraft/entities/marker_style.h"
#include "plotcraft/entities/point.h"
#include "plotcraft/use_cases/draw/i_draw_primitives.h"

namespace plotcraft {
namespace use_cases {

class DrawMarker {
 public:
  DrawMarker(IDrawPrimitives& draw_primitives) : draw_primitives_(draw_primitives) {}

  void DrawPlus(const entities::Point& marker_pos, double size) {
    auto left_h = entities::Point(marker_pos.x - size, marker_pos.y);
    auto right_h = entities::Point(marker_pos.x + size, marker_pos.y);
    auto line_h = entities::Line(left_h, right_h);

    auto top_v = entities::Point(marker_pos.x, marker_pos.y + size);
    auto bottom_v = entities::Point(marker_pos.x, marker_pos.y - size);
    auto line_v = entities::Line(top_v, bottom_v);

    draw_primitives_.DrawLine(line_h);
    draw_primitives_.DrawLine(line_v);
  }

  void DrawSquare(const entities::Point& marker_pos, double size) {
    auto rect = entities::Rect(marker_pos.x - size, marker_pos.y - size, 2.0 * size, 2.0 * size);
    draw_primitives_.DrawRect(rect);
  }

  void DrawCross(const entities::Point& marker_pos, double size) {
    auto rect = entities::Rect(marker_pos.x - size, marker_pos.y - size, 2.0 * size, 2.0 * size);
    auto l0 = entities::Line(rect.GetTopLeft(), rect.GetBottomRight());
    auto l1 = entities::Line(rect.GetBottomLeft(), rect.GetTopRight());
    draw_primitives_.DrawLine(l0);
    draw_primitives_.DrawLine(l1);
  }

  void Draw(const entities::Point& marker_pos, entities::MarkerStyle markerstyle, double size) {
    switch (markerstyle) {
      case entities::MarkerStyle::kPlus:
        DrawPlus(marker_pos, size);
        break;
      case entities::MarkerStyle::kSquare:
        DrawSquare(marker_pos, size);
        break;
      case entities::MarkerStyle::kCross:
        DrawCross(marker_pos, size);
        break;
      default:
        break;
    }
  }

 private:
  IDrawPrimitives& draw_primitives_;
};

}  // namespace use_cases
}  // namespace plotcraft
