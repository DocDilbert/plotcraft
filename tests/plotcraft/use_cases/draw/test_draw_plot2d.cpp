
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "gmock/gmock.h"
#include "helpers_draw_primitives.h"
#include "mock_draw_marker.h"
#include "mock_draw_primitives.h"
#include "plotcraft/use_cases/draw/draw_plot2d.h"

using ::testing::_;
using ::testing::DoubleEq;
using ::testing::NiceMock;

using namespace plotcraft::entities;
using namespace plotcraft::use_cases;

TEST(TestDrawPlot2d, DrawEmptyVectorsExpectNoDrawCalls) {
  NiceMock<MockDrawPrimitives> mock_draw_primitives;
  Rect content_region(0.0, 0.0, 100.0, 100.0);
  Rect viewport(0.0, 0.0, 1.0, 1.0);

  DrawPlot2d draw_plot(mock_draw_primitives, content_region, viewport);
  std::vector<double> x = {};
  std::vector<double> y = {};
  Plot2d plot = {.x = x, .y = y};

  HelpersDrawPrimitives::ExpectNoCalls(mock_draw_primitives);
  draw_plot.Draw(plot);
}

TEST(TestDrawPlot2d, Draw2PointsExpectOneLine) {
  NiceMock<MockDrawPrimitives> mock_draw_primitives;
  Rect content_region(0.0, 0.0, 100.0, 100.0);
  Rect viewport(0.0, 0.0, 1.0, 1.0);

  DrawPlot2d draw_plot(mock_draw_primitives, content_region, viewport);
  std::vector<double> x = {0.0, 1.0};
  std::vector<double> y = {0.0, 1.0};
  Plot2d plot = {.x = x, .y = y, .marker_style = MarkerStyle::kNone};

  NiceMock<MockDrawMarker> mock_draw_marker;

  EXPECT_CALL(mock_draw_primitives,
              DrawLine(DoubleEq(0.0), DoubleEq(0.0), DoubleEq(100.0), DoubleEq(100.0)))
      .Times(1);
  draw_plot.Draw(plot, mock_draw_marker);
}

TEST(TestDrawPlot2d, DrawX1PointY2PoinrExpectNoLine) {
  NiceMock<MockDrawPrimitives> mock_draw_primitives;
  Rect content_region(0.0, 0.0, 100.0, 100.0);
  Rect viewport(0.0, 0.0, 1.0, 1.0);

  DrawPlot2d draw_plot(mock_draw_primitives, content_region, viewport);
  std::vector<double> x = {0.0};
  std::vector<double> y = {0.0, 1.0};
  Plot2d plot = {.x = x, .y = y, .marker_style = MarkerStyle::kNone};

  NiceMock<MockDrawMarker> mock_draw_marker;

  EXPECT_CALL(mock_draw_primitives, DrawLine(_, _, _, _)).Times(0);
  draw_plot.Draw(plot, mock_draw_marker);
}

TEST(TestDrawPlot2d, DrawX2PointY3PointsExpectOneLine) {
  NiceMock<MockDrawPrimitives> mock_draw_primitives;
  Rect content_region(0.0, 0.0, 100.0, 100.0);
  Rect viewport(0.0, 0.0, 1.0, 1.0);

  DrawPlot2d draw_plot(mock_draw_primitives, content_region, viewport);
  std::vector<double> x = {0.0, 1.0};
  std::vector<double> y = {0.0, 1.0, 2.0};
  Plot2d plot = {.x = x, .y = y, .marker_style = MarkerStyle::kNone};

  NiceMock<MockDrawMarker> mock_draw_marker;

  EXPECT_CALL(mock_draw_primitives,
              DrawLine(DoubleEq(0.0), DoubleEq(0.0), DoubleEq(100.0), DoubleEq(100.0)))
      .Times(1);
  draw_plot.Draw(plot, mock_draw_marker);
}
