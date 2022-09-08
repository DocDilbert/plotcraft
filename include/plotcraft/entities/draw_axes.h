
#pragma once
#include <spdlog/spdlog.h>

#include <memory>
#include <string>
#include <vector>

#include "plotcraft/entities/axes.h"
#include "plotcraft/entities/draw_axis.h"
#include "plotcraft/entities/draw_legend.h"
#include "plotcraft/entities/draw_plot2d.h"
#include "plotcraft/entities/i_draw_primitives.h"
#include "plotcraft/entities/i_measure.h"

namespace plotcraft {
namespace entities {

template <class TDrawAxis = DrawAxis, class TDrawPlot2d = DrawPlot2d<>,
          class TDrawLegend = DrawLegend>
class DrawAxes {
 public:
  DrawAxes(IDrawPrimitives& draw_primitives, const Rect& content_region, IMeasure& measure)
      : draw_primitives_(draw_primitives), content_region_(content_region), measure_(measure) {}

  void Draw(const entities::Axes& axes) {
    const auto& viewport = axes.viewport;
    double v_offset = 0.0;
    double h_offset = 0.0;
    auto draw_axis = TDrawAxis(draw_primitives_, content_region_, viewport, measure_);
    for (auto& axis : axes.axis) {
      double offset = draw_axis.Draw(axis);
      // collect offsets from the various ticks
      if (axis.orientation == Orientation::kVertical) {
        v_offset = std::max(offset, v_offset);
      } else {
        h_offset = std::max(offset, h_offset);
      }
    }

    auto draw_plot2d = TDrawPlot2d(draw_primitives_, content_region_, viewport);
    for (auto& plot : axes.plots) {
      draw_plot2d.Draw(plot);
    }

    // Draw Labels
    DrawHorizontalLabel(axes.xlabel, h_offset + axes.label_offset);
    DrawVerticalLabel(axes.ylabel, v_offset + axes.label_offset);
    DrawTitle(axes.title, axes.title_offset);

    // Draw Rectangle
    draw_primitives_.SetBrush(Color::kTransparent);
    draw_primitives_.SetPen(Color::kBlack, 1.0);
    draw_primitives_.DrawRect(content_region_);
    draw_primitives_.SetFont(Color::kBlack);

    auto draw_legend = TDrawLegend(draw_primitives_, content_region_, measure_);
    draw_legend.Draw(axes.legend);
  }

 private:
  void DrawVerticalLabel(const std::string& text, double offset) {
    draw_primitives_.SetFont(Color::kBlack, "bold", 14);
    double pos_x = content_region_.GetBottomLeft().x;
    double pos_y = content_region_.GetBottomLeft().y + content_region_.GetHeight() * 0.5;

    auto text_extent = measure_.GetTextExtent(text, "bold", 14);
    auto& t_width = text_extent.width;
    auto& t_height = text_extent.height;
    auto& t_descent = text_extent.descent;
    draw_primitives_.DrawText(text, pos_x - offset - t_height - t_descent, pos_y - t_width / 2.0,
                              M_PI * 90.0 / 180.0);
  }

  void DrawHorizontalLabel(const std::string& text, double offset) {
    draw_primitives_.SetFont(Color::kBlack, "bold", 14);
    double pos_x = content_region_.GetBottomLeft().x + content_region_.GetWidth() * 0.5;
    double pos_y = content_region_.GetBottomLeft().y;

    auto text_extent = measure_.GetTextExtent(text, "bold", 14);
    auto& t_width = text_extent.width;

    draw_primitives_.DrawText(text, pos_x - t_width * 0.5, pos_y - offset);
  }

  void DrawTitle(const std::string& text, double offset) {
    draw_primitives_.SetFont(Color::kBlack, "bold", 14);
    double pos_x = content_region_.GetTopLeft().x + content_region_.GetWidth() * 0.5;
    double pos_y = content_region_.GetTopLeft().y;

    auto text_extent = measure_.GetTextExtent(text, "bold", 14);
    auto& t_width = text_extent.width;
    auto& t_height = text_extent.height;
    auto& t_descent = text_extent.descent;

    draw_primitives_.DrawText(text, pos_x - t_width * 0.5, pos_y + t_descent + t_height + offset);
  }
  Rect content_region_;
  IMeasure& measure_;
  IDrawPrimitives& draw_primitives_;
};

}  // namespace entities
}  // namespace plotcraft
