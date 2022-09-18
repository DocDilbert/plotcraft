#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "plotcraft/data/figure.h"
#include "plotcraft/data/repository.h"
#include "plotcraft/gateway/i_measure.h"
#include "plotcraft/use_cases/draw/i_measure.h"

namespace plotcraft {
namespace gateway {

class MeasureGateway : public use_cases::IMeasure {
 public:
  MeasureGateway(gateway::IMeasure& measure) : measure_(measure) {}

  use_cases::TextExtent GetTextExtent(const std::string& text, const std::string& font_name,
                                      double size) override {
    auto uc_text_extent = measure_.GetTextExtent(text, font_name, size);

    use_cases::TextExtent text_extent{.width = uc_text_extent.width,
                                      .height = uc_text_extent.height,
                                      .descent = uc_text_extent.descent,
                                      .externalLeading = uc_text_extent.externalLeading};
    return text_extent;
  }

 private:
  gateway::IMeasure& measure_;
};

}  // namespace gateway
}  // namespace plotcraft

