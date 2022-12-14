#pragma once

#include <string>

namespace plotcraft {
namespace gateway {

struct TextExtent {
  double width;
  double height;
  double descent;
  double externalLeading;
};

class IMeasure {
 public:
  virtual TextExtent GetTextExtent(const std::string& text, const std::string& font_name,
                                   double size) = 0;
};

}  // namespace gateway
}  // namespace plotcraft
