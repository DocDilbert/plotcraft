#pragma once

#include <map>
#include <memory>
#include <vector>

#include "plotcraft/use_cases/model/i_create_plot_input.h"

namespace plotcraft {
namespace controller {

class CreatePlotController {
 public:
  CreatePlotController(use_cases::ICreatePlotInput& output) : output_(output) {}

  void Plot(const std::string& axes_id, const std::vector<double>& x, const std::vector<double>& y,
            const std::map<std::string, std::string> options) {
    std::string label = "";
    std::string color = "blue";
    std::string markerstyle = "";
    auto it = options.find("label");
    if (it != options.end()) {
      label = it->second;
    }
    it = options.find("color");
    if (it != options.end()) {
      color = it->second;
    }
    it = options.find("markerstyle");
    if (it != options.end()) {
      markerstyle = it->second;
    }
    use_cases::CreatePlotRequest request = {.axes_id = axes_id,
                                            .x = x,
                                            .y = y,
                                            .autoscale = true,
                                            .label = label,
                                            .color = color,
                                            .markerstyle = markerstyle};

    output_.Create(request);
  };

 private:
  use_cases::ICreatePlotInput& output_;
};

}  // namespace controller
}  // namespace plotcraft
