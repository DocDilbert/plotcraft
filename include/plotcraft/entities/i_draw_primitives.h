#pragma once

#include <string>

#include "plotcraft/entities/color.h"
#include "plotcraft/entities/line.h"
#include "plotcraft/entities/rect.h"

namespace plotcraft {
namespace entities {

class IDrawPrimitives {
 public:
  virtual void SetPen(Color color, double width = 1.0) = 0;
  virtual void SetBrush(Color color) = 0;
  virtual void SetFont(Color color, std::string font_name = "default", double size = 14.0) = 0;
  virtual void DrawText(std::string text, double x, double y, double angle = 0.0) = 0;
  virtual void DrawRect(double left, double bottom, double width, double height) = 0;
  void DrawRect(const Rect& rect) { DrawRect(rect.left, rect.bottom, rect.width, rect.height); }
  virtual void Clip(double left, double bottom, double width, double height) = 0;
  void Clip(const entities::Rect& rect) { Clip(rect.left, rect.bottom, rect.width, rect.height); }
  virtual void ResetClip() = 0;
  virtual void DrawLine(double x0, double y0, double x1, double y1) = 0;
  void DrawLine(const Line& line) { DrawLine(line.x0, line.y0, line.x1, line.y1); }
};

}  // namespace entities
}  // namespace plotcraft
