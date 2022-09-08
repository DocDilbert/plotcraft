#pragma once

#include <string>

namespace plotcraft {
namespace use_cases {

struct TextExtent {
  double width;
  double height;
  double descent;
  double externalLeading;
};

class IMeasure {
 public:
  virtual TextExtent GetTextExtent(const std::string& text, const std::string& font_name, double size) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
