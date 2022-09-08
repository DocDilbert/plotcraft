#pragma once

#include <string>

#include "plotcraft/entities/point.h"

namespace plotcraft {
namespace entities {

struct Line {
   public:
    Line() {}
    Line(double px0, double py0, double px1, double py1)
        : x0(px0), y0(py0), x1(px1), y1(py1) {}
    Line(const Point& p0, const Point& p1)
        : x0(p0.x), y0(p0.y), x1(p1.x), y1(p1.y) {}
    Line(const Line& line)
        : x0(line.x0), y0(line.y0), x1(line.x1), y1(line.y1) {}

    double x0;
    double y0;

    double x1;
    double y1;
};

}  // namespace entities
}  // namespace plotcraft
