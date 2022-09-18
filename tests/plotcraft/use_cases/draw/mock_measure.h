#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "plotcraft/use_cases/draw/i_measure.h"

class MockMeasure : public plotcraft::use_cases::IMeasure {
 public:
  MOCK_METHOD(plotcraft::use_cases::TextExtent, GetTextExtent,
              (const std::string& text, const std::string& font_name, double size), (override));
};

