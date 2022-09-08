#pragma once

#include <string>

namespace plotcraft {
namespace use_cases {

class IIdGenerator {
 public:
  virtual std::string GetId(std::string tag) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
