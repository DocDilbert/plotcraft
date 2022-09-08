#pragma once

#include <functional>
#include <iostream>

#include "plotcraft/entities/line.h"
#include "plotcraft/entities/rect.h"

// Defining region codes
const int INSIDE = 0;  // 0000
const int LEFT = 1;    // 0001
const int RIGHT = 2;   // 0010
const int BOTTOM = 4;  // 0100
const int TOP = 8;     // 1000

// Function to compute region code for a point(x, y)
inline int computeCode(const plotcraft::entities::Rect& rect, double x, double y) {
  // initialized as being inside
  int code = INSIDE;
  const double& x_min = rect.GetLeft();
  const double& x_max = rect.GetRight();
  const double& y_min = rect.GetBottom();
  const double& y_max = rect.GetTop();

  if (x < x_min)  // to the left of rectangle
    code |= LEFT;
  else if (x > x_max)  // to the right of rectangle
    code |= RIGHT;
  if (y < y_min)  // below the rectangle
    code |= BOTTOM;
  else if (y > y_max)  // above the rectangle
    code |= TOP;

  return code;
}

// Implementing Cohen-Sutherland algorithm
// Clipping a line from P1 = (x1, y1) to P2 = (x2, y2)
inline void cohenSutherlandClip(const plotcraft::entities::Rect& rect, const plotcraft::entities::Line& line,
                                std::function<void(const plotcraft::entities::Line&)> fun) {
  const double& x_min = rect.GetLeft();
  const double& x_max = rect.GetRight();
  const double& y_min = rect.GetBottom();
  const double& y_max = rect.GetTop();

  double x0 = line.x0;
  double y0 = line.y0;
  double x1 = line.x1;
  double y1 = line.y1;

  // Compute region codes for P1, P2
  int code1 = computeCode(rect, x0, y0);
  int code2 = computeCode(rect, x1, y1);

  // Initialize line as outside the rectangular window
  bool accept = false;

  while (true) {
    if ((code1 == 0) && (code2 == 0)) {
      // If both endpoints lie within rectangle
      accept = true;
      break;
    } else if (code1 & code2) {
      // If both endpoints are outside rectangle,
      // in same region
      break;
    } else {
      // Some segment of line lies within the
      // rectangle
      int code_out;
      double x, y;

      // At least one endpoint is outside the
      // rectangle, pick it.
      if (code1 != 0)
        code_out = code1;
      else
        code_out = code2;

      // Find intersection point;
      // using formulas y = y0 + slope * (x - x0),
      // x = x0 + (1 / slope) * (y - y0)
      if (code_out & TOP) {
        // point is above the clip rectangle
        x = x0 + (x1 - x0) * (y_max - y0) / (y1 - y0);
        y = y_max;
      } else if (code_out & BOTTOM) {
        // point is below the rectangle
        x = x0 + (x1 - x0) * (y_min - y0) / (y1 - y0);
        y = y_min;
      } else if (code_out & RIGHT) {
        // point is to the right of rectangle
        y = y0 + (y1 - y0) * (x_max - x0) / (x1 - x0);
        x = x_max;
      } else if (code_out & LEFT) {
        // point is to the left of rectangle
        y = y0 + (y1 - y0) * (x_min - x0) / (x1 - x0);
        x = x_min;
      }

      // Now intersection point x, y is found
      // We replace point outside rectangle
      // by intersection point
      if (code_out == code1) {
        x0 = x;
        y0 = y;
        code1 = computeCode(rect, x0, y0);
      } else {
        x1 = x;
        y1 = y;
        code2 = computeCode(rect, x1, y1);
      }
    }
  }
  if (accept) {
    fun(plotcraft::entities::Line(x0, y0, x1, y1));
  } else {
    // rejected
  }
}
