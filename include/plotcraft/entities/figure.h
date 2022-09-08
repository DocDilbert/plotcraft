#pragma once

#include <string>
#include <vector>

#include "plotcraft/entities/axes.h"
#include "plotcraft/entities/margins.h"

namespace plotcraft {
namespace entities {

/**
 * Holds all plot elements
 */
struct Figure {
    Margins margins = {};   // outer margin
    Margins paddings = {};  // inner margin

    std::vector<Axes> axes;
};
}  // namespace entities
}  // namespace plotcraft
