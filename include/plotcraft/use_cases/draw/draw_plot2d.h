#pragma once

#include <spdlog/spdlog.h>

#include <string>

#include "plotcraft/entities/line.h"
#include "plotcraft/entities/plot2d.h"
#include "plotcraft/entities/point.h"
#include "plotcraft/entities/transform.h"
#include "plotcraft/use_cases/draw/clipping.h"
#include "plotcraft/use_cases/draw/draw_marker.h"
#include "plotcraft/use_cases/draw/i_draw_primitives.h"
#include "plotcraft/use_cases/draw/i_measure.h"

namespace plotcraft {
namespace use_cases {

class DrawPlot2d {
 public:
  DrawPlot2d(IDrawPrimitives& draw_primitives, const entities::Rect& content_region,
             const entities::Rect& viewport)
      : draw_primitives_(draw_primitives), content_region_(content_region), viewport_(viewport) {}

  template <class TDrawMarker>
  void Draw(const entities::Plot2d& plot, TDrawMarker& draw_marker) {
    const auto trafo = entities::Transform::FromRectToRect(content_region_, viewport_);
    const auto effective_size = std::min(plot.x.size(), plot.y.size());

    if (effective_size > 0u) {  // only enable clipping if there is at least one point
      if (plot.native_clipping) {
        draw_primitives_.Clip(content_region_);
      }
    }

    if (effective_size > 1u) {  // to draw a line we need two points
      draw_primitives_.SetPen(plot.color);
      auto x0 = plot.x[0];
      auto y0 = plot.y[0];

      // Draw Lines
      for (size_t i = 1; i < effective_size; i++) {
        auto& x1 = plot.x[i];
        auto& y1 = plot.y[i];

        auto p0 = trafo.Forward(entities::Point(x0, y0));
        auto p1 = trafo.Forward(entities::Point(x1, y1));
        auto l = entities::Line(p0, p1);

        if (plot.line_clipping) {
          cohenSutherlandClip(content_region_, l,
                              [this](const auto& l) { draw_primitives_.DrawLine(l); });
        } else {
          draw_primitives_.DrawLine(l);
        }

        x0 = x1;
        y0 = y1;
      }
    }

    if (effective_size > 0u) {  // Only draw point if I have at least one point
      if (plot.marker_style != entities::MarkerStyle::kNone) {
        draw_primitives_.SetPen(plot.marker_edge_color);
        draw_primitives_.SetBrush(plot.marker_face_color);

        // Draw Markers
        for (size_t i = 0; i < effective_size; i++) {
          auto& x0 = plot.x[i];
          auto& y0 = plot.y[i];
          auto p0 = trafo.Forward(entities::Point(x0, y0));
          // check if the marker is contained in the plotting area
          if (content_region_.Contains(p0)) {
            draw_marker.Draw(p0, plot.marker_style, plot.marker_size);
          }
        }
      }
    }

    if (effective_size > 0u) {  // only disable clipping if there is at least one point
      if (plot.native_clipping) {
        draw_primitives_.ResetClip();
      }
    }
  }
  void Draw(const entities::Plot2d& plot) {
    auto draw_marker = DrawMarker(draw_primitives_);
    Draw<DrawMarker>(plot, draw_marker);
  }

 private:
  IDrawPrimitives& draw_primitives_;
  const entities::Rect& content_region_;
  const entities::Rect& viewport_;
};

}  // namespace use_cases
}  // namespace plotcraft
