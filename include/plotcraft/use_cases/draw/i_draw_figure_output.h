#pragma once

#include <string>
#include <vector>

namespace plotcraft {
namespace use_cases {

struct DrawFigureResponse {
  std::string figure_id;  ///< Id of drawn figure
};

class IDrawFigureOutput {
 public:
  virtual void SetPen(std::string colour, double width) = 0;
  virtual void SetBrush(std::string colour) = 0;
  virtual void SetFont(std::string font_name, std::string color, double size) = 0;
  virtual void DrawText(std::string text, double x, double y, double angle) = 0;
  virtual void DrawRect(double left, double bottom, double width, double height) = 0;
  virtual void Clip(double left, double bottom, double width, double height) = 0;
  virtual void ResetClip() = 0;
  virtual void DrawLine(double x0, double y0, double x1, double y1) = 0;

  virtual void IsDrawn(const DrawFigureResponse& response) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
