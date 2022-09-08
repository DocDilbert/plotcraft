#pragma once

#include <string>
#include <vector>

#include "plotcraft/data/axis.h"
#include "plotcraft/data/plot2d.h"

namespace plotcraft {
namespace data {

struct Axes {
  std::string axes_id;

  double viewport_left;
  double viewport_bottom;
  double viewport_width;
  double viewport_height;

  std::vector<Axis> axis;

  std::vector<Plot2d> plots;

  std::string xlabel = {""};
  std::string ylabel = {""};
  std::string title = {""};
};

}  // namespace data
}  // namespace plotcraft
