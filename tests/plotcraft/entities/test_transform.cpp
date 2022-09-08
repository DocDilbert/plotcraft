#include <gtest/gtest.h>

#include "plotcraft/entities/transform.h"

using namespace plotcraft::entities;

TEST(TestTransform, TestForwardIdentityTransformDoesNothing) {
    auto trafo = Transform::Identity();

    auto to_p = trafo.Forward(Point(0.5, 0.6));
    EXPECT_FLOAT_EQ(to_p.x, 0.5);
    EXPECT_FLOAT_EQ(to_p.y, 0.6);
}

TEST(TestTransform, TestForwardFromRectToRectLeftBottomEdgeCase) {
    Rect to(100, 110, 800, 640);
    Rect from(0.1, 0.1, 0.8, 0.8);

    auto trafo = Transform::FromRectToRect(to, from);

    auto to_p = trafo.Forward(Point(0.1, 0.1));
    EXPECT_FLOAT_EQ(to_p.x, 100.0);
    EXPECT_FLOAT_EQ(to_p.y, 110.0);
}

