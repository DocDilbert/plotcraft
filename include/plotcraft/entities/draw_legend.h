#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "plotcraft/entities/axis.h"
#include "plotcraft/entities/i_draw_primitives.h"
#include "plotcraft/entities/i_measure.h"
#include "plotcraft/entities/legend.h"
#include "plotcraft/entities/line.h"
#include "plotcraft/entities/rect.h"

namespace plotcraft {
namespace entities {

class DrawLegend {
 public:
  DrawLegend(IDrawPrimitives& draw_primitives, const Rect& content_region, IMeasure& measure)

      : draw_primitives_(draw_primitives), measure_(measure), content_region_(content_region) {}

  void Draw(const Legend& legend) {
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

    auto legend_box = Rect(p0_x, p0_y, box_width, box_height);

    draw_primitives_.SetBrush(Color::kWhite);
    draw_primitives_.DrawRect(legend_box);

    // -----------------
    // Draw Lines
    auto line_x = p0_x + box_padding;
    auto line_y = p0_y + box_height - box_padding;

    for (auto& it : entries) {
      draw_primitives_.SetPen(it.color, 1.0);
      auto text_extent = measure_.GetTextExtent(it.label, "default", 12);

      auto l = Line(line_x, line_y - text_extent.height * 0.5, line_x + 40,
                    line_y - text_extent.height * 0.5);

      draw_primitives_.DrawLine(l);

      line_y -= text_extent.height;  // + text_extent.descent;
    }

    // -----------------
    // Write texts
    auto text_x = p0_x + box_padding + signifier_padding;
    auto text_y = p0_y + box_height - box_padding;

    draw_primitives_.SetFont(Color::kBlack, "default", 12);
    for (auto& it : entries) {
      auto text_extent = measure_.GetTextExtent(it.label, "default", 12);
      draw_primitives_.DrawText(it.label, text_x, text_y);
      text_y = text_y - text_extent.height;  // - text_extent.descent;
    }
  }

 private:
  std::vector<LegendEntry> FilterLegendEntries(const std::vector<LegendEntry>& legend_entries) {
    std::vector<LegendEntry> ret;
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
  const Rect& content_region_;
};

}  // namespace entities
}  // namespace plotcraft
