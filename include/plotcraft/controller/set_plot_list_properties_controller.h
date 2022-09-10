#pragma once

#include <memory>
#include <nlohmann/json.hpp>

#include "plotcraft/use_cases/model/i_set_plot_list_properties_input.h"

namespace plotcraft {
namespace controller {

using json = nlohmann::json;

class SetPlotListPropertiesController {
 private:
  typedef std::map<std::string, std::string> Options;

 public:
  SetPlotListPropertiesController(use_cases::ISetPlotListPropertiesInput& output)
      : output_(output) {}

  void SetPlotLabels(const std::string& axes_id, const std::vector<std::string>& labels) {
    use_cases::SetPlotListPropertiesRequest request = {.axes_id = axes_id};
    auto json_request = json();
    json_request["property"] = "plot_labels";
    json_request["labels"] = labels;
    request.command = json_request.dump();
    output_.Update(request);
  }

 private:
  use_cases::ISetPlotListPropertiesInput& output_;
};

}  // namespace controller
}  // namespace plotcraft
