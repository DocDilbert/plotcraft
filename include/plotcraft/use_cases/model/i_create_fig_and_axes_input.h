#pragma once

#include <memory>
#include <string>

namespace plotcraft {
namespace use_cases {

struct CreateFigAndAxesRequest {
  std::shared_ptr<std::string> title;
};

class ICreateFigAndAxesInput {
 public:
  virtual void Create(CreateFigAndAxesRequest request) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
