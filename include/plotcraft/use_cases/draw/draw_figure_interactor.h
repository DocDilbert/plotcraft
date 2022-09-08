
#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "plotcraft/entities/axes.h"
#include "plotcraft/entities/axis.h"
#include "plotcraft/entities/draw_figure.h"
#include "plotcraft/entities/figure.h"
#include "plotcraft/entities/i_draw_primitives.h"
#include "plotcraft/entities/i_measure.h"
#include "plotcraft/entities/legend.h"
#include "plotcraft/entities/margins.h"
#include "plotcraft/entities/orientation.h"
#include "plotcraft/entities/plot2d.h"
#include "plotcraft/entities/rect.h"
#include "plotcraft/use_cases/draw/i_draw_figure_data_access.h"
#include "plotcraft/use_cases/draw/i_draw_figure_input.h"
#include "plotcraft/use_cases/draw/i_draw_figure_output.h"
#include "plotcraft/use_cases/i_measure.h"

namespace plotcraft {
namespace use_cases {

class DrawFigureInteractor : public IDrawFigureInput {
  class MeasureAdapter : public entities::IMeasure {
   public:
    MeasureAdapter(use_cases::IMeasure& uc_measure) : uc_measure_(uc_measure) {}

    virtual entities::TextExtent GetTextExtent(const std::string& text,
                                               const std::string& font_name, double size) {
      auto uc_text_extent = uc_measure_.GetTextExtent(text, font_name, size);

      entities::TextExtent text_extent{.width = uc_text_extent.width,
                                       .height = uc_text_extent.height,
                                       .descent = uc_text_extent.descent,
                                       .externalLeading = uc_text_extent.externalLeading};
      return text_extent;
    }

   private:
    use_cases::IMeasure& uc_measure_;
  };

  class DrawPrimitivesAdapter : public entities::IDrawPrimitives {
   public:
    DrawPrimitivesAdapter(IDrawFigureOutput& draw_figure_output)
        : draw_figure_output_(draw_figure_output) {}
    void SetPen(entities::Color color, double width) override {
      draw_figure_output_.SetPen(TranslateColor(color), width);
    };
    void SetBrush(entities::Color color) override {
      draw_figure_output_.SetBrush(TranslateColor(color));
    };

    void SetFont(entities::Color color, std::string font_name, double size) override {
      draw_figure_output_.SetFont(font_name, TranslateColor(color), size);
    };
    void DrawText(std::string text, double x, double y, double angle) override {
      draw_figure_output_.DrawText(text, x, y, angle);
    };
    void DrawRect(double left, double bottom, double width, double height) override {
      draw_figure_output_.DrawRect(left, bottom, width, height);
    };
    void Clip(double left, double bottom, double width, double height) override {
      draw_figure_output_.Clip(left, bottom, width, height);
    };
    void ResetClip() override { draw_figure_output_.ResetClip(); };
    void DrawLine(double x0, double y0, double x1, double y1) override {
      draw_figure_output_.DrawLine(x0, y0, x1, y1);
    };

   private:
    std::string TranslateColor(entities::Color color) {
      switch (color) {
        case entities::Color::kBlack:
          return "black";
        case entities::Color::kWhite:
          return "white";
        case entities::Color::kRed:
          return "red";
        case entities::Color::kGreen:
          return "green";
        case entities::Color::kBlue:
          return "blue";
        case entities::Color::kTransparent:
          return "transparent";
        default:
          break;
      }
      return "black";
    }
    IDrawFigureOutput& draw_figure_output_;
  };

 public:
  DrawFigureInteractor(IDrawFigureOutput& output, IDrawFigureDataAccesss& draw_figure_repo_access,
                       IMeasure& measure)
      : output_(output), data_access_(draw_figure_repo_access), measure_(measure) {}

  entities::Margins ConvertMargins(const IDrawFigureDataAccesss::MarginData& margin) {
    entities::Margins res = {
        .left = margin.left, .top = margin.top, .bottom = margin.bottom, .right = margin.right};
    return res;
  }

  void Draw(use_cases::DrawFigureRequest request) override {
    const auto& element_box = entities::Rect(request.screen_left, request.screen_bottom,
                                             request.screen_width, request.screen_height);

    const auto& figure_id = request.figure_id;

    // -----------------------
    // Calculate drawing region
    const auto& figure_margins = ConvertMargins(data_access_.GetMargins(figure_id));

    const auto& figure_paddings = ConvertMargins(data_access_.GetPaddings(figure_id));

    auto inner_region = figure_margins.DeflateRect(element_box);
    auto content_region = figure_paddings.DeflateRect(element_box);

    // -----------------------
    // Build Entity model
    std::vector<entities::Axes> e_axes;
    auto axes_ids = data_access_.GetAxesIds(figure_id);

    for (const auto& it : axes_ids) {
      auto axes_data = data_access_.GetAxesData(it);

      std::vector<entities::Axis> e_axis;
      for (auto& axis : axes_data.axis) {
        auto ot = entities::Orientation::kVertical;
        if (axis.orientation == IDrawFigureDataAccesss::Orientation::kHorizontal) {
          ot = entities::Orientation::kHorizontal;
        }

        e_axis.push_back(entities::Axis{
            .orientation = ot,
        });
      }

      std::vector<entities::Plot2d> e_plots;
      std::vector<entities::LegendEntry> e_legend_entries;
      for (auto& plot : axes_data.plots) {
        auto& p_color = plot.color;
        entities::Color color = entities::Color::kBlack;
        if (p_color == "black") {
          color = entities::Color::kBlack;
        } else if (p_color == "blue") {
          color = entities::Color::kBlue;
        } else if (p_color == "red") {
          color = entities::Color::kRed;
        } else if (p_color == "green") {
          color = entities::Color::kGreen;
        } else if (p_color == "white") {
          color = entities::Color::kWhite;
        } else if (p_color == "transparent") {
          color = entities::Color::kTransparent;
        }

        auto& p_markerstyle = plot.markerstyle;
        entities::MarkerStyle markerstyle = entities::MarkerStyle::kNone;
        if (p_markerstyle == "+") {
          markerstyle = entities::MarkerStyle::kPlus;
        } else if (p_markerstyle == "s") {
          markerstyle = entities::MarkerStyle::kSquare;
        } else if (p_markerstyle == "x") {
          markerstyle = entities::MarkerStyle::kCross;
        }

        auto e_plot = entities::Plot2d{.x = plot.x,
                                       .y = plot.y,
                                       .color = color,
                                       .marker_style = markerstyle,
                                       .marker_edge_color = color};
        e_plots.push_back(e_plot);

        // each Plot should gets its own legend entry
        auto e_legend_entry = entities::LegendEntry{.label = plot.label,
                                                    .color = e_plot.color,
                                                    .marker_size = e_plot.marker_size,
                                                    .marker_style = e_plot.marker_style};
        e_legend_entries.push_back(e_legend_entry);
      }

      entities::Legend e_legend = {.entries = e_legend_entries};

      e_axes.push_back(entities::Axes{
          .viewport = entities::Rect(axes_data.viewport_left, axes_data.viewport_bottom,
                                     axes_data.viewport_width, axes_data.viewport_height),
          .xlabel = axes_data.xlabel,
          .ylabel = axes_data.ylabel,
          .title = axes_data.title,
          .axis = e_axis,
          .plots = e_plots,
          .legend = e_legend});
    }

    auto e_figure =
        entities::Figure{.margins = figure_margins, .paddings = figure_paddings, .axes = e_axes};

    // -----------------------
    // Draw plot with entity model
    use_cases::DrawFigureResponse response = {.figure_id = figure_id};

    auto measure_adapter = MeasureAdapter(measure_);
    auto draw_primitives_adapter = DrawPrimitivesAdapter(output_);

    auto draw_figure = entities::DrawFigure<>(draw_primitives_adapter, inner_region, content_region,
                                              measure_adapter);
    draw_figure.Draw(e_figure);

    output_.IsDrawn(response);
  };

 private:
  IDrawFigureOutput& output_;
  IDrawFigureDataAccesss& data_access_;
  IMeasure& measure_;
};

}  // namespace use_cases
}  // namespace plotcraft
