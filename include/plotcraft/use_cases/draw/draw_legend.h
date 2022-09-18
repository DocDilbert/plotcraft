#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "plotcraft/entities/axis.h"
#include "plotcraft/entities/legend.h"
#include "plotcraft/entities/line.h"
#include "plotcraft/entities/rect.h"
#include "plotcraft/use_cases/draw/draw_marker.h"
#include "plotcraft/use_cases/draw/i_draw_primitives.h"
#include "plotcraft/use_cases/draw/i_measure.h"

namespace plotcraft {
namespace use_cases {

class DrawLegend {
 public:
  DrawLegend(IDrawPrimitives& draw_primitives, const entities::Rect& content_region,
             IMeasure& measure)

      : draw_primitives_(draw_primitives), measure_(measure), content_region_(content_region) {}

  template <class TDrawMarker>
  void Draw(const entities::Legend& legend, TDrawMarker& draw_marker) {
    // only consider legend entries which are valid
    auto entries = FilterLegendEntries(legend.entries);

    // if no entries exist, do not draw the legend
    if (entries.size() == 0) {
      return;
    }

    auto top_right = content_region_.GetTopRight();

    auto box_padding = 6.0;
    auto signifier_padding = 50.0;

    // -----------------
    // Measure
    auto box_width = 0.0;
    auto box_height = 0.0;

    // calculate height and width of box
    for (auto& it : entries) {
      auto text_extent = measure_.GetTextExtent(it.label, "default", 12);
      box_height += text_extent.height;  // + text_extent.descent;
      box_width = std::max(box_width, text_extent.width);
    }

    // -----------------
    // Draw Box
    // Calculate box around legend
    box_height += 2.0 * box_padding;
    box_width += 2.0 * box_padding + signifier_padding;

    auto box_x_offset = 10.0;
    auto box_y_offset = 10.0;

    auto p0_x = top_right.x - box_width - box_x_offset;
    auto p0_y = top_right.y - box_height - box_y_offset;

    auto legend_box = entities::Rect(p0_x, p0_y, box_width, box_height);

    draw_primitives_.SetBrush(entities::Color::kWhite);
    draw_primitives_.DrawRect(legend_box);
    draw_primitives_.SetBrush(entities::Color::kTransparent);

    // -----------------
    // Draw Lines
    auto line_x = p0_x + box_padding;
    auto line_y = p0_y + box_height - box_padding;

    const double line_len = 37.0;
    for (auto& it : entries) {
      draw_primitives_.SetPen(it.color, 1.0);
      auto text_extent = measure_.GetTextExtent(it.label, "default", 12);

      auto p0 = entities::Point(line_x, line_y - text_extent.height * 0.5);
      auto p1 = entities::Point(line_x + line_len, line_y - text_extent.height * 0.5);
      auto l = entities::Line(p0, p1);
      auto p_marker = entities::Point(line_x + line_len * 0.5, line_y - text_extent.height * 0.5);

      draw_primitives_.DrawLine(l);
      draw_marker.Draw(p_marker, it.marker_style, it.marker_size);

      line_y -= text_extent.height;  // + text_extent.descent;
    }
    // -----------------
    // Write texts
    auto text_x = p0_x + box_padding + signifier_padding;
    auto text_y = p0_y + box_height - box_padding;

    draw_primitives_.SetFont(entities::Color::kBlack, "default", 12);
    for (auto& it : entries) {
      auto text_extent = measure_.GetTextExtent(it.label, "default", 12);
      draw_primitives_.DrawText(it.label, text_x, text_y);
      text_y = text_y - text_extent.height;  // - text_extent.descent;
    }
  }

  void Draw(const entities::Legend& legend) {
    auto draw_marker = DrawMarker(draw_primitives_);
    Draw<DrawMarker>(legend, draw_marker);
  }

 private:
  std::vector<entities::LegendEntry> FilterLegendEntries(
      const std::vector<entities::LegendEntry>& legend_entries) {
    std::vector<entities::LegendEntry> ret;
    for (auto& it : legend_entries) {
      // do not add entries with empty label to the legend
      if (it.label != "") {
        ret.push_back(it);
      }
    }
    return ret;
  }
  IDrawPrimitives& draw_primitives_;
  IMeasure& measure_;
  const entities::Rect& content_region_;
};

}  // namespace use_cases
}  // namespace plotcraft
