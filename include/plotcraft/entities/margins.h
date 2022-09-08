
#pragma once

#include <string>

#include "plotcraft/entities/rect.h"

namespace plotcraft {
namespace entities {

struct Margins {
    double left;
    double top;
    double bottom;
    double right;

    Rect DeflateRect(const Rect& rect) const {
        Rect ret(rect.left + left, rect.bottom + bottom,
                 rect.width - left - right, rect.height - bottom - top);
        return ret;
    }
};
}  // namespace entities
}  // namespace plotcraft
