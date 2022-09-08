
#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "mock_draw_primitives.h"

using ::testing::_;

class HelpersDrawPrimitives {
 public:
  static void ExpectNoCalls(MockDrawPrimitives& mock_draw_primitives) {
    EXPECT_CALL(mock_draw_primitives, SetPen(_, _)).Times(0);
    EXPECT_CALL(mock_draw_primitives, SetBrush(_)).Times(0);
    EXPECT_CALL(mock_draw_primitives, SetFont(_, _, _)).Times(0);
    EXPECT_CALL(mock_draw_primitives, DrawText(_, _, _, _)).Times(0);
    EXPECT_CALL(mock_draw_primitives, DrawRect(_, _, _, _)).Times(0);
    EXPECT_CALL(mock_draw_primitives, Clip(_, _, _, _)).Times(0);
    EXPECT_CALL(mock_draw_primitives, ResetClip()).Times(0);
    EXPECT_CALL(mock_draw_primitives, DrawLine(_, _, _, _)).Times(0);
  }
};
