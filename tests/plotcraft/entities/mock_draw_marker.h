#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "plotcraft/entities/marker_style.h"
#include "plotcraft/entities/point.h"

class MockDrawMarker {
 public:
  MOCK_METHOD(void, Draw,
              (const plotcraft::entities::Point& marker_pos,
               plotcraft::entities::MarkerStyle markerstyle, double size),
              ());
};
