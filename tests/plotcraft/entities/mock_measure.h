#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "plotcraft/entities/i_measure.h"

class MockMeasure : public plotcraft::entities::IMeasure {
 public:
  MOCK_METHOD(plotcraft::entities::TextExtent, GetTextExtent,
              (const std::string& text, const std::string& font_name, double size), (override));
};

