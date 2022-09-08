#pragma once

#include <string>

namespace plotcraft {
namespace use_cases {

struct SetAxesPropertiesResponse {
  std::string figure_id;  ///< Id of created figure
  std::string axes_id;    ///< Id of created axes
};

class ISetAxesPropertiesOutput {
 public:
  virtual void IsViewportChange(SetAxesPropertiesResponse response) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
