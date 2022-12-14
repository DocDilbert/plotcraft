#pragma once

#include <string>
#include <vector>

#include "plotcraft/entities/color.h"
#include "plotcraft/entities/marker_style.h"

namespace plotcraft {
namespace entities {

struct LegendEntry {
  std::string label = {""};
  Color color = {Color::kBlack};

  double marker_size = 5;
  MarkerStyle marker_style = {MarkerStyle::kNone};
};

struct Legend {
  bool enable = {false};
  std::vector<LegendEntry> entries;
};

}  // namespace entities
}  // namespace plotcraft
