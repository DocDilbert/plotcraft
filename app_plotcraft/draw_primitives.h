#pragma once

#include <spdlog/spdlog.h>
#include <wx/dcgraph.h>
#include <wx/graphics.h>
#include <wx/sizer.h>
#include <wx/wx.h>

#include "plotcraft/plotcraft.h"

class DrawPrimitives : public plotcraft::presenter::IDrawPrimitives,
                       public plotcraft::gateway::IMeasure {
 public:
  DrawPrimitives(wxGraphicsContext& gc) : gc_(gc) {}

  void DrawText(std::string text, double x, double y, double angle) override {
    double screen_height = 0.0f;
    double screen_width = 0.0f;
    gc_.GetSize(&screen_width, &screen_height);

    // change coordinate system
    auto x_n = x;
    auto y_n = screen_height - y;

    spdlog::trace("DrawText(\"{}\", {}, {}, angle={})", text, x_n, y_n, angle);
    gc_.DrawText(text, x_n, y_n, angle);
  };

  void DrawLine(double x0, double y0, double x1, double y1) override {
    double screen_height = 0.0f;
    double screen_width = 0.0f;
    gc_.GetSize(&screen_width, &screen_height);
    gc_.StrokeLine(x0, screen_height - y0, x1, screen_height - y1);
  }

  const wxColour& GetColor(const std::string& color) {
    if (color == "black") {
      auto& ret = *wxBLACK;
      return ret;
    } else if (color == "white") {
      auto& ret = *wxWHITE;
      return ret;
    } else if (color == "red") {
      auto& ret = *wxRED;
      return ret;
    } else if (color == "green") {
      auto& ret = *wxGREEN;
      return ret;
    } else if (color == "blue") {
      auto& ret = *wxBLUE;
      return ret;
    }
    auto& ret = *wxBLACK;
    return ret;
  }

  void SetPen(std::string color, double width) override {
    spdlog::trace("SetPen(\"{}\", {})", color, width);
    auto& color_obj = GetColor(color);
    auto pen = gc_.CreatePen(wxGraphicsPenInfo(color_obj).Width(width));
    gc_.SetPen(pen);
  }

  void SetFont(std::string font_name, std::string color, double size) override {
    spdlog::trace("SetFont(\"{}\", \"{}\", {})", font_name, color, size);
    wxFontWeight font_weight = wxFontWeight::wxFONTWEIGHT_NORMAL;
    if (font_name == "bold") {
      font_weight = wxFontWeight::wxFONTWEIGHT_SEMIBOLD;
    }

    wxFont font(size, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, font_weight);

    auto& color_obj = GetColor(color);
    auto gc_font = gc_.CreateFont(font, color_obj);
    gc_.SetFont(gc_font);
  }

  void SetBrush(std::string color) override {
    spdlog::trace("SetBrush(\"{}\")", color);
    if (color == "black") {
      auto& brush = *wxBLACK_BRUSH;
      auto gc_brush = gc_.CreateBrush(brush);
      gc_.SetBrush(gc_brush);
    } else if (color == "white") {
      auto& brush = *wxWHITE_BRUSH;
      auto gc_brush = gc_.CreateBrush(brush);
      gc_.SetBrush(gc_brush);
    } else if (color == "red") {
      auto& brush = *wxRED_BRUSH;
      auto gc_brush = gc_.CreateBrush(brush);
      gc_.SetBrush(gc_brush);
    } else if (color == "green") {
      auto& brush = *wxGREEN_BRUSH;
      auto gc_brush = gc_.CreateBrush(brush);
      gc_.SetBrush(gc_brush);
    } else if (color == "blue") {
      auto& brush = *wxBLUE_BRUSH;
      auto gc_brush = gc_.CreateBrush(brush);
      gc_.SetBrush(gc_brush);
    } else if (color == "transparent") {
      auto& brush = *wxTRANSPARENT_BRUSH;
      auto gc_brush = gc_.CreateBrush(brush);
      gc_.SetBrush(gc_brush);
    }
  }

  void DrawRect(double left, double bottom, double width, double height) override {
    // x (0,0)
    // |
    // |  x (left, bottom + height)
    // |  |
    // |  |
    // |  x (left, bottom)
    // |
    // x  (0, display_height)
    double screen_height = 0.0f;
    double screen_width = 0.0f;
    gc_.GetSize(&screen_width, &screen_height);

    // change coordinate system
    auto x = left;
    auto y = screen_height - (bottom + height);
    spdlog::trace("DrawRect({},{},{},{})", x, y, width, height);
    gc_.DrawRectangle(x, y, width, height);
  }

  void Clip(double left, double bottom, double width, double height) override {
    // x (0,0)
    // |
    // |  x (left, bottom + height)
    // |  |
    // |  |
    // |  x (left, bottom)
    // |
    // x  (0, display_height)
    double screen_height = 0.0f;
    double screen_width = 0.0f;
    gc_.GetSize(&screen_width, &screen_height);

    // change coordinate system
    auto x = left;
    auto y = screen_height - (bottom + height);
    spdlog::trace("Clip({},{},{},{})", x, y, width, height);
    gc_.Clip(x, y, width, height);
  }

  void ResetClip() override {
    spdlog::trace("ResetClip");
    gc_.ResetClip();
  }

  plotcraft::gateway::TextExtent GetTextExtent(const std::string& text,
                                               const std::string& font_name, double size) override {
    SetFont(font_name, "black", size);
    plotcraft::gateway::TextExtent text_extent;
    gc_.GetTextExtent(text, &text_extent.width, &text_extent.height, &text_extent.descent,
                      &text_extent.externalLeading);
    spdlog::trace("GetTextExtent(\"{}\",{},{},{},{})", text, text_extent.width, text_extent.height,
                  text_extent.descent, text_extent.externalLeading);
    return text_extent;
  }

 private:
  wxGraphicsContext& gc_;
};

