#pragma once

#include <memory>

#include "plotcraft/use_cases/draw/i_draw_figure_input.h"

namespace plotcraft {
namespace controller {

class DrawController {
 public:
  DrawController(use_cases::IDrawFigureInput& output) : output_(output) {}

  void Draw(std::string figure_id, double left, double bottom, double width,
            double height) {
    use_cases::DrawFigureRequest request = {.figure_id = figure_id,
                                            .screen_left = left,
                                            .screen_bottom = bottom,
                                            .screen_width = width,
                                            .screen_height = height

    };
    output_.Draw(request);
  };

 private:
  use_cases::IDrawFigureInput& output_;
};

}  // namespace controller
}  // namespace plotcraft
