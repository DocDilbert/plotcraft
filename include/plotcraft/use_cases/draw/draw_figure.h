#pragma once

#include <memory>
#include <string>
#include <vector>

#include "plotcraft/entities/figure.h"
#include "plotcraft/use_cases/draw/draw_axes.h"
#include "plotcraft/use_cases/draw/i_draw_primitives.h"
#include "plotcraft/use_cases/draw/i_measure.h"

namespace plotcraft {
namespace use_cases {

template <class TDrawAxes = DrawAxes<>>
class DrawFigure {
 public:
  DrawFigure(IDrawPrimitives& draw_primitives, const entities::Rect& inner_region,
             const entities::Rect& content_region, IMeasure& measure)
      : draw_primitives_(draw_primitives),
        inner_region_(inner_region),
        content_region_(content_region),
        measure_(measure) {}

  void Draw(const entities::Figure& figure) {
    draw_primitives_.SetBrush(entities::Color::kWhite);
    draw_primitives_.SetPen(entities::Color::kBlack, 1);
    draw_primitives_.DrawRect(inner_region_.left, inner_region_.bottom, inner_region_.width,
                              inner_region_.height);

    auto draw_axes = TDrawAxes(draw_primitives_, content_region_, measure_);
    for (auto& axes : figure.axes) {
      draw_axes.Draw(axes);
    }
  }

 private:
  IDrawPrimitives& draw_primitives_;
  const entities::Rect& inner_region_;
  const entities::Rect& content_region_;
  IMeasure& measure_;
};

}  // namespace use_cases
}  // namespace plotcraft
