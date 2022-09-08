
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "gmock/gmock.h"
#include "helpers_draw_primitives.h"
#include "mock_draw_primitives.h"
#include "mock_measure.h"
#include "plotcraft/entities/draw_legend.h"

using ::testing::_;
using ::testing::NiceMock;

using namespace plotcraft::entities;

TEST(TestDrawLegend, DrawEmptyLegendExpectNoDrawCalls) {
  NiceMock<MockDrawPrimitives> mock_draw_primitives;
  NiceMock<MockMeasure> mock_measure;
  Rect rect(0.0, 0.0, 100.0, 100.0);
  DrawLegend draw_legend(mock_draw_primitives, rect, mock_measure);

  std::vector<LegendEntry> legend_entries = {};
  Legend legend = {.entries = legend_entries};
  HelpersDrawPrimitives::ExpectNoCalls(mock_draw_primitives);
  draw_legend.Draw(legend);
}

TEST(TestDrawLegend, DrawLegendWith2EntriesOneEmptyExpect1DrawTextCall) {
  NiceMock<MockDrawPrimitives> mock_draw_primitives;
  NiceMock<MockMeasure> mock_measure;
  Rect rect(0.0, 0.0, 100.0, 100.0);
  DrawLegend draw_legend(mock_draw_primitives, rect, mock_measure);

  std::vector<LegendEntry> legend_entries = {{.label = ""}, {.label = "TEST"}};
  Legend legend = {.entries = legend_entries};
  EXPECT_CALL(mock_draw_primitives, DrawText("TEST", _, _, _)).Times(1);
  draw_legend.Draw(legend);
}

class MockDrawMarker {
 public:
  MOCK_METHOD(void, Draw, (const Point& marker_pos, MarkerStyle markerstyle, double size), ());
};

TEST(TestDrawLegend, DrawLegendWith2EntryExpectDrawTwoMarkers) {
  NiceMock<MockDrawPrimitives> mock_draw_primitives;
  NiceMock<MockMeasure> mock_measure;
  Rect rect(0.0, 0.0, 100.0, 100.0);
  DrawLegend draw_legend(mock_draw_primitives, rect, mock_measure);

  std::vector<LegendEntry> legend_entries = {
      {.label = "TEST1"}, {.label = "TEST2", .marker_style = MarkerStyle::kSquare}};
  Legend legend = {.entries = legend_entries};
  MockDrawMarker mock_draw_marker;
  EXPECT_CALL(mock_draw_marker, Draw(_, _, _)).Times(2);
  draw_legend.Draw(legend, mock_draw_marker);
}
