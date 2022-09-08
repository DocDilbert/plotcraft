#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>

#include "plotcraft/presenter/i_draw_primitives.h"
#include "plotcraft/use_cases/draw/i_draw_figure_output.h"

namespace plotcraft {
namespace presenter {

class DrawPresenter : public use_cases::IDrawFigureOutput {
 public:
  DrawPresenter(IDrawPrimitives& draw_primitives) : draw_primitives_(draw_primitives) {}

  const std::string& GetFigureId() { return figure_id_; }

  int GetDrawCalls() { return draw_calls_; }

  void SetPen(std::string color, double width) override {
    draw_calls_++;
    draw_primitives_.SetPen(color, width);
  }
  void SetBrush(std::string color) override {
    draw_calls_++;
    draw_primitives_.SetBrush(color);
  }
  void SetFont(std::string font_name, std::string color, double size) override {
    draw_calls_++;
    draw_primitives_.SetFont(font_name, color, size);
  }
  void DrawText(std::string text, double x, double y, double angle) override {
    draw_calls_++;
    draw_primitives_.DrawText(text, x, y, angle);
  }
  void DrawRect(double left, double bottom, double width, double height) override {
    draw_calls_++;
    draw_primitives_.DrawRect(left, bottom, width, height);
  }
  void Clip(double left, double bottom, double width, double height) override {
    draw_calls_++;
    draw_primitives_.Clip(left, bottom, width, height);
  }
  void ResetClip() override {
    draw_calls_++;
    draw_primitives_.ResetClip();
  }
  void DrawLine(double x0, double y0, double x1, double y1) override {
    draw_calls_++;
    draw_primitives_.DrawLine(x0, y0, x1, y1);
  }
  void IsDrawn(const use_cases::DrawFigureResponse& response) override {
    figure_id_ = response.figure_id;
  }

 private:
  IDrawPrimitives& draw_primitives_;
  std::string figure_id_ = {"invalid"};
  int draw_calls_ = {0};
};

}  // namespace presenter
}  // namespace plotcraft
