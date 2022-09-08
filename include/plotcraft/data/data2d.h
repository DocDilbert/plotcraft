#pragma once

#include <string>
#include <vector>

namespace plotcraft {
namespace data {

struct Data2d {
  std::string data2d_id;
  std::vector<double> x;
  std::vector<double> y;
};

}  // namespace data
}  // namespace plotcraft
