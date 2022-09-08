#pragma once

#include <string>
#include <vector>

#include "plotcraft/entities/color.h"
#include "plotcraft/entities/marker_style.h"

namespace plotcraft {
namespace entities {

struct Plot2d {
  const std::vector<double>& x;
  const std::vector<double>& y;

  // options
  bool line_clipping = {false};
  bool native_clipping = {true};

  Color color = {Color::kBlue};

  double marker_size = 4;
  MarkerStyle marker_style = {MarkerStyle::kPlus};
  Color marker_edge_color = {Color::kRed};
  Color marker_face_color = {Color::kTransparent};
};

}  // namespace entities
}  // namespace plotcraft
