#pragma once

#include <string>
#include <vector>

#include "plotcraft/entities/axis.h"
#include "plotcraft/entities/legend.h"
#include "plotcraft/entities/plot2d.h"
#include "plotcraft/entities/rect.h"

namespace plotcraft {
namespace entities {

struct Axes {
  Rect viewport;

  std::string xlabel = {""};
  std::string ylabel = {""};
  std::string title = {""};

  std::vector<Axis> axis;
  std::vector<Plot2d> plots;

  double label_offset = {8.0};
  double title_offset = {1.0};

  Legend legend;
};

}  // namespace entities
}  // namespace plotcraft
