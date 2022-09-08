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
  MarkerStyle marker_style = {MarkerStyle::kNone};
};

struct Legend {
  std::vector<LegendEntry> entries;
};

}  // namespace entities
}  // namespace plotcraft
