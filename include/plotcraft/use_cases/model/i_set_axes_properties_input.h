#pragma once

#include <memory>
#include <string>
#include <vector>

namespace plotcraft {
namespace use_cases {

struct SetAxesPropertiesRequest {
  const std::string& axes_id;
  std::string command;
};

class ISetAxesPropertiesInput {
 public:
  virtual void Update(SetAxesPropertiesRequest request) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
