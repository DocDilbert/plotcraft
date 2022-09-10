#pragma once

#include <string>

namespace plotcraft {
namespace use_cases {

struct SetPlotListPropertiesResponse {
  std::string figure_id;  ///< Id of created figure
  std::string axes_id;    ///< Id of created axes
};

class ISetPlotListPropertiesOutput {
 public:
  virtual void IsViewportChange(SetPlotListPropertiesResponse response) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
