
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "plotcraft/entities/draw_axes.h"
#include "plotcraft/entities/figure.h"
#include "plotcraft/entities/i_draw_primitives.h"
#include "plotcraft/entities/i_measure.h"

namespace plotcraft {
namespace entities {

template <class TDrawAxes = DrawAxes<>>
class DrawFigure {
 public:
  DrawFigure(IDrawPrimitives& draw_primitives, const Rect& inner_region, const Rect& content_region,
             IMeasure& measure)
      : draw_primitives_(draw_primitives),
        inner_region_(inner_region),
        content_region_(content_region),
        measure_(measure) {}

  void Draw(const entities::Figure& figure) {
    draw_primitives_.SetBrush(Color::kWhite);
    draw_primitives_.SetPen(Color::kBlack, 1);
    draw_primitives_.DrawRect(inner_region_.left, inner_region_.bottom, inner_region_.width,
                              inner_region_.height);

    auto draw_axes = TDrawAxes(draw_primitives_, content_region_, measure_);
    for (auto& axes : figure.axes) {
      draw_axes.Draw(axes);
    }
  }

 private:
  IDrawPrimitives& draw_primitives_;
  const Rect& inner_region_;
  const Rect& content_region_;
  IMeasure& measure_;
};

}  // namespace entities
}  // namespace plotcraft
