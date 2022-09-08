#pragma once

#include <string>
#include <vector>

#include "plotcraft/data/margins.h"

namespace plotcraft {
namespace data {

/**
 * Holds all plot elements
 */
struct Figure {
  std::string figure_id;

  Margins margins = {};   // outer margin
  Margins paddings = {};  // inner margin

  std::vector<std::string> axes_ids;
};

}  // namespace data
}  // namespace plotcraft
