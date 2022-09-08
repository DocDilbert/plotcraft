
#pragma once
#include <spdlog/spdlog.h>

#include <string>

#include "plotcraft/entities/clipping.h"
#include "plotcraft/entities/draw_marker.h"
#include "plotcraft/entities/i_draw_primitives.h"
#include "plotcraft/entities/i_measure.h"
#include "plotcraft/entities/line.h"
#include "plotcraft/entities/plot2d.h"
#include "plotcraft/entities/point.h"
#include "plotcraft/entities/transform.h"

namespace plotcraft {
namespace entities {

template <class TDrawMarker = DrawMarker>
class DrawPlot2d {
 public:
  DrawPlot2d(IDrawPrimitives& draw_primitives, const Rect& content_region, const Rect& viewport)
      : draw_primitives_(draw_primitives), content_region_(content_region), viewport_(viewport) {}

  void Draw(const Plot2d& plot) {
    const auto trafo = Transform::FromRectToRect(content_region_, viewport_);

    draw_primitives_.SetPen(plot.color);
    auto x0 = plot.x[0];
    auto y0 = plot.y[0];

    if (plot.native_clipping) {
      draw_primitives_.Clip(content_region_);
    }
    // Draw Lines
    for (size_t i = 1; i < plot.y.size(); i++) {
      auto& x1 = plot.x[i];
      auto& y1 = plot.y[i];

      auto p0 = trafo.Forward(Point(x0, y0));
      auto p1 = trafo.Forward(Point(x1, y1));
      auto l = Line(p0, p1);

      if (plot.line_clipping) {
        cohenSutherlandClip(content_region_, l,
                            [this](const auto& l) { draw_primitives_.DrawLine(l); });
      } else {
        draw_primitives_.DrawLine(l);
      }

      x0 = x1;
      y0 = y1;
    }

    if (plot.marker_style != MarkerStyle::kNone) {
      draw_primitives_.SetPen(plot.marker_edge_color);
      draw_primitives_.SetBrush(plot.marker_face_color);

      // Draw Markers
      for (size_t i = 0; i < plot.y.size(); i++) {
        auto& x0 = plot.x[i];
        auto& y0 = plot.y[i];
        auto p0 = trafo.Forward(Point(x0, y0));
        // check if the marker is contained in the plotting area
        if (content_region_.Contains(p0)) {
          switch (plot.marker_style) {
            case MarkerStyle::kPlus:
              TDrawMarker::DrawCross(draw_primitives_, p0, plot.marker_size);
              break;
            case MarkerStyle::kSquare:
              TDrawMarker::DrawRect(draw_primitives_, p0, plot.marker_size);
              break;
            default:
              break;
          }
        }
      }
    }

    if (plot.native_clipping) {
      draw_primitives_.ResetClip();
    }
  }

 private:
  IDrawPrimitives& draw_primitives_;
  const Rect& content_region_;
  const Rect& viewport_;
};

}  // namespace entities
}  // namespace plotcraft
