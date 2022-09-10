#pragma once

#include <memory>
#include <string>
#include <vector>

namespace plotcraft {
namespace use_cases {

class ISetPlotListPropertiesDataAccess {
 public:
  virtual void SetPlotLabels(const std::string& axes_id,
                             const std::vector<std::string>& entries) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
