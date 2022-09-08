#pragma once

#include <memory>
#include <string>
#include <vector>

namespace plotcraft {
namespace use_cases {

struct CreatePlotRequest {
  const std::string &axes_id;
  const std::vector<double> &x;
  const std::vector<double> &y;
  bool autoscale = {true};
  const std::string &label;
  const std::string &color;
  const std::string &markerstyle;
};

class ICreatePlotInput {
 public:
  virtual void Create(CreatePlotRequest request) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
