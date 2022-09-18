#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "gmock/gmock.h"
#include "plotcraft/use_cases/draw/locators.h"

using ::testing::DoubleEq;
using ::testing::ElementsAre;

using namespace plotcraft::use_cases;

TEST(TestMaxNLocator, TestGetTickValuesInterval0To05VectorWith6Elements) {
  MaxNLocator max_n_loc(9);

  auto res = max_n_loc.GetTickValues(0.0, 0.5);
  ASSERT_THAT(res, ElementsAre(DoubleEq(0.0), DoubleEq(0.1), DoubleEq(0.2), DoubleEq(0.3),
                               DoubleEq(0.4), DoubleEq(0.5)));
}

TEST(TestMaxNLocator, TestGetTickValuesIntervalm005To055VectorWith6Elements) {
  MaxNLocator max_n_loc(9);

  auto res = max_n_loc.GetTickValues(-0.05, 0.55);
  ASSERT_THAT(res, ElementsAre(DoubleEq(0.0), DoubleEq(0.1), DoubleEq(0.2), DoubleEq(0.3),
                               DoubleEq(0.4), DoubleEq(0.5)));
}

TEST(TestMaxNLocator, TestGetTickValuesInterval0To01p3VectorWith6Elements) {
  MaxNLocator max_n_loc(9);

  auto res = max_n_loc.GetTickValues(0.0, 1.3);
  ASSERT_THAT(res, ElementsAre(DoubleEq(0.0), DoubleEq(0.25), DoubleEq(0.5), DoubleEq(0.75),
                               DoubleEq(1.0), DoubleEq(1.25)));
}

TEST(TestMaxNLocator, TestGetTickValuesInterval0p68To01p6VectorWith6Elements) {
  MaxNLocator max_n_loc(10);

  auto res = max_n_loc.GetTickValues(0.68, 1.6);
  ASSERT_THAT(
      res, ElementsAre(DoubleEq(0.7), DoubleEq(0.8), DoubleEq(0.9), DoubleEq(1.0), DoubleEq(1.1),
                       DoubleEq(1.2), DoubleEq(1.3), DoubleEq(1.4), DoubleEq(1.5), DoubleEq(1.6)));
}
