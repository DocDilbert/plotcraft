#pragma once

#include <spdlog/spdlog.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "plotcraft/entities/axis.h"
#include "plotcraft/entities/orientation.h"
#include "plotcraft/entities/point.h"
#include "plotcraft/entities/transform.h"
#include "plotcraft/use_cases/draw/i_draw_primitives.h"
#include "plotcraft/use_cases/draw/i_measure.h"
#include "plotcraft/use_cases/draw/locators.h"

namespace plotcraft {
namespace use_cases {

class DrawAxis {
 public:
  DrawAxis(IDrawPrimitives& draw_primitives, const entities::Rect& content_region,
           const entities::Rect& viewport, IMeasure& measure)

      : draw_primitives_(draw_primitives),
        measure_(measure),
        content_region_(content_region),
        viewport_(viewport) {
    bottom_left_ = content_region.GetBottomLeft();
    bottom_right_ = content_region.GetBottomRight();
    top_left_ = content_region.GetTopLeft();
  }

  double Draw(const entities::Axis& axis) {
    const auto trafo = entities::Transform::FromRectToRect(content_region_, viewport_);

    double vmin = 0.0f;
    double vmax = 0.0f;
    if (axis.orientation == entities::Orientation::kVertical) {
      vmin = viewport_.bottom;
      vmax = viewport_.bottom + viewport_.height;
    } else if (axis.orientation == entities::Orientation::kHorizontal) {
      vmin = viewport_.left;
      vmax = viewport_.left + viewport_.width;
    }
    spdlog::trace("DrawAxis: vmin={}, vmax={}", vmin, vmax);

    auto tvmin = ToString(vmin);
    auto tvmax = ToString(vmax);

    MaxNLocator locator(10);
    auto ticks = locator.GetTickValues(vmin, vmax);

    double offset = 0.0;
    const double& tick_text_offset = axis.tick_text_offset;

    draw_primitives_.SetFont(entities::Color::kBlack, "default", 12);
    if (axis.orientation == entities::Orientation::kHorizontal) {
      for (auto tick : ticks) {
        auto tick_pos = trafo.ForwardX(tick);

        auto tick_p0 = entities::Point(tick_pos, bottom_left_.y);
        auto tick_p1 = entities::Point(tick_pos, bottom_left_.y - axis.major_tick_len);

        auto l = entities::Line(tick_p0, tick_p1);
        draw_primitives_.DrawLine(l);

        auto tick_text = ToString(tick);
        auto text_extent = measure_.GetTextExtent(tick_text, "default", 12);
        auto& t_width = text_extent.width;
        auto& t_height = text_extent.height;
        auto& t_descent = text_extent.descent;

        draw_primitives_.DrawText(tick_text, tick_p1.x - t_width / 2.0,
                                  tick_p1.y - tick_text_offset);

        // the height of the tick text plus its offset
        offset = std::max(offset, t_height + tick_text_offset + t_descent);
      }
    } else {
      for (auto tick : ticks) {
        auto tick_pos = trafo.ForwardY(tick);
        auto tick_p0 = entities::Point(bottom_left_.x, tick_pos);
        auto tick_p1 = entities::Point(bottom_left_.x - axis.major_tick_len, tick_pos);
        auto l = entities::Line(tick_p0, tick_p1);
        draw_primitives_.DrawLine(l);

        auto tick_text = ToString(tick);
        auto text_extent = measure_.GetTextExtent(tick_text, "default", 12);
        auto& t_width = text_extent.width;
        auto& t_height = text_extent.height;

        draw_primitives_.DrawText(tick_text, tick_p1.x - t_width - tick_text_offset,
                                  tick_p1.y + t_height / 2.0);

        // the length of the tick text plus its offset
        offset = std::max(offset, t_width + tick_text_offset);
      }
    }
    return offset;
  }

 private:
  std::string ToString(const double& val) {
    std::ostringstream ss;
    // Set Fixed -entities::Point Notation
    ss << std::fixed;
    ss << std::setprecision(2);
    //. double to stream
    ss << val;
    // Get string from output string stream
    return (ss.str());
  }
  IDrawPrimitives& draw_primitives_;

  // Start/stop coordinates in system space
  entities::Point bottom_left_;
  entities::Point bottom_right_;
  entities::Point top_left_;

  IMeasure& measure_;
  const entities::Rect& content_region_;
  const entities::Rect& viewport_;
};

}  // namespace use_cases
}  // namespace plotcraft
