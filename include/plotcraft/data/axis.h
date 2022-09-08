#pragma once

#include <string>

namespace plotcraft {
namespace data {

enum class AxisOrientation { kVertical, kHorizontal };

struct Axis {
  AxisOrientation orientation;
  std::string xlabel = {};
};

}  // namespace data
}  // namespace plotcraft
