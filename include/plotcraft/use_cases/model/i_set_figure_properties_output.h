#pragma once

#include <string>

namespace plotcraft {
namespace use_cases {

struct SetFigurePropertiesResponse {
  std::string figure_id;  ///< Id of created figure
  std::string axes_id;    ///< Id of created axes
};

class ISetFigurePropertiesOutput {
 public:
  virtual void IsViewportChange(SetFigurePropertiesResponse response) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
