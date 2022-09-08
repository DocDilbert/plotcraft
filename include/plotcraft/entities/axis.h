#pragma once

#include <string>

#include "plotcraft/entities/orientation.h"

namespace plotcraft {
namespace entities {

struct Axis {
  Orientation orientation;

  double tick_text_offset = {6.0};
  double label_offset = {30.0};
  double major_tick_len = {6.0};
};

}  // namespace entities
}  // namespace plotcraft
