#pragma once

#include <memory>
#include <string>
#include <vector>

namespace plotcraft {
namespace use_cases {

struct SetFigurePropertiesRequest {
  const std::string& axes_id;
  std::string command;
};

class ISetFigurePropertiesInput {
 public:
  virtual void SetProperties(SetFigurePropertiesRequest request) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
