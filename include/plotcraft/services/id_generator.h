
#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "plotcraft/use_cases/i_id_generator.h"

namespace plotcraft {
namespace services {

class IdGenerator : public use_cases::IIdGenerator {
 public:
  IdGenerator() {}

  std::string GetId(std::string tag) override {
    auto ret = tag + std::to_string(cnt_);
    cnt_++;
    return ret;
  }

 private:
  int cnt_ = {0};
};

}  // namespace services
}  // namespace plotcraft
