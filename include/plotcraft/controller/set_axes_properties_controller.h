#pragma once

#include <memory>
#include <nlohmann/json.hpp>

#include "plotcraft/use_cases/model/i_set_axes_properties_input.h"

namespace plotcraft {
namespace controller {

using json = nlohmann::json;

class SetAxesPropertiesController {
 public:
  SetAxesPropertiesController(use_cases::ISetAxesPropertiesInput& output) : output_(output) {}

  void UpdateXRange(const std::string& axes_id, double left, double right) {
    use_cases::SetAxesPropertiesRequest request = {.axes_id = axes_id};
    auto json_request = json();
    json_request["property"] = "xlim";
    json_request["viewport_left"] = left;
    json_request["viewport_right"] = right;
    request.command = json_request.dump();

    output_.Update(request);
  };

  void UpdateYRange(const std::string& axes_id, double bottom, double top) {
    use_cases::SetAxesPropertiesRequest request = {.axes_id = axes_id};
    auto json_request = json();
    json_request["property"] = "ylim";
    json_request["viewport_bottom"] = bottom;
    json_request["viewport_top"] = top;
    request.command = json_request.dump();
    output_.Update(request);
  };

  void SetXLabel(const std::string& axes_id, const std::string& text) {
    use_cases::SetAxesPropertiesRequest request = {.axes_id = axes_id};
    auto json_request = json();
    json_request["property"] = "xlabel";
    json_request["text"] = text;
    request.command = json_request.dump();
    output_.Update(request);
  }

  void SetYLabel(const std::string& axes_id, const std::string& text) {
    use_cases::SetAxesPropertiesRequest request = {.axes_id = axes_id};
    auto json_request = json();
    json_request["property"] = "ylabel";
    json_request["text"] = text;
    request.command = json_request.dump();
    output_.Update(request);
  }

  void SetTitle(const std::string& axes_id, const std::string& text) {
    use_cases::SetAxesPropertiesRequest request = {.axes_id = axes_id};
    auto json_request = json();
    json_request["property"] = "title";
    json_request["text"] = text;
    request.command = json_request.dump();
    output_.Update(request);
  }

 private:
  use_cases::ISetAxesPropertiesInput& output_;
};

}  // namespace controller
}  // namespace plotcraft
