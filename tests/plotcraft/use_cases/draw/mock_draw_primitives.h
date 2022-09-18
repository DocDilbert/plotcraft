#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "plotcraft/use_cases/draw/i_draw_primitives.h"

class MockDrawPrimitives : public plotcraft::use_cases::IDrawPrimitives {
 public:
  MOCK_METHOD(void, SetPen, (plotcraft::entities::Color color, double width), (override));
  MOCK_METHOD(void, SetBrush, (plotcraft::entities::Color color), (override));
  MOCK_METHOD(void, SetFont, (plotcraft::entities::Color color, std::string font_name, double size),
              (override));
  MOCK_METHOD(void, DrawText, (std::string text, double x, double y, double angle), (override));
  MOCK_METHOD(void, DrawRect, (double left, double bottom, double width, double height),
              (override));
  MOCK_METHOD(void, Clip, (double left, double bottom, double width, double height), (override));
  MOCK_METHOD(void, ResetClip, (), (override));
  MOCK_METHOD(void, DrawLine, (double x0, double y0, double x1, double y1), (override));
};

