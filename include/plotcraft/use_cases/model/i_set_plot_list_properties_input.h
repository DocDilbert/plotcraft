#pragma once

#include <memory>
#include <string>
#include <vector>

namespace plotcraft {
namespace use_cases {

struct SetPlotListPropertiesRequest {
  const std::string& axes_id;
  std::string command;
};

class ISetPlotListPropertiesInput {
 public:
  virtual void Update(SetPlotListPropertiesRequest request) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
