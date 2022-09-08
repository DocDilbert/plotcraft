#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "gmock/gmock.h"
#include "plotcraft/entities/locators.h"
using ::testing::DoubleEq;
using ::testing::ElementsAre;

using namespace plotcraft::entities;

TEST(TestMaxNLocator, TestGetTickValuesInterval0To05VectorWith6Elements) {
    MaxNLocator max_n_loc(9);

    auto res = max_n_loc.GetTickValues(0.0, 0.5);
    ASSERT_THAT(res, ElementsAre(DoubleEq(0.0), DoubleEq(0.1), DoubleEq(0.2),
                                 DoubleEq(0.3), DoubleEq(0.4), DoubleEq(0.5)));
}

TEST(TestMaxNLocator, TestGetTickValuesIntervalm005To055VectorWith6Elements) {
    MaxNLocator max_n_loc(9);

    auto res = max_n_loc.GetTickValues(-0.05, 0.55);
    ASSERT_THAT(res, ElementsAre(DoubleEq(0.0), DoubleEq(0.1), DoubleEq(0.2),
                                 DoubleEq(0.3), DoubleEq(0.4), DoubleEq(0.5)));
}

TEST(TestMaxNLocator, TestGetTickValuesInterval) {
    MaxNLocator max_n_loc(9);

    auto res = max_n_loc.GetTickValues(0.0, 1.3);
    ASSERT_THAT(res, ElementsAre(DoubleEq(0.0), DoubleEq(0.1), DoubleEq(0.2),
                                 DoubleEq(0.3), DoubleEq(0.4), DoubleEq(0.5)));
}
