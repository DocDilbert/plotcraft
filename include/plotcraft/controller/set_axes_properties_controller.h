#pragma once

#include <memory>
#include <nlohmann/json.hpp>

#include "plotcraft/use_cases/model/i_set_axes_properties_input.h"

namespace plotcraft {
namespace controller {

using json = nlohmann::json;

class SetAxesPropertiesController {
 private:
  typedef std::map<std::string, std::string> Options;

 public:
  SetAxesPropertiesController(use_cases::ISetAxesPropertiesInput& output) : output_(output) {}

  void UpdateXRange(const std::string& axes_id, double left, double right) {
    use_cases::SetAxesPropertiesRequest request = {.axes_id = axes_id};
    json json_request = {
        {{"property", "ylim"}, {"viewport_left", left}, {"viewport_right", right}}};
    request.command = json_request.dump();
    output_.Update(request);
  };

  void UpdateYRange(const std::string& axes_id, double bottom, double top) {
    use_cases::SetAxesPropertiesRequest request = {.axes_id = axes_id};
    json json_request = {
        {{"property", "ylim"}, {"viewport_bottom", bottom}, {"viewport_top", top}}};
    request.command = json_request.dump();
    output_.Update(request);
  };

  void SetXLabel(const std::string& axes_id, const std::string& text) {
    use_cases::SetAxesPropertiesRequest request = {.axes_id = axes_id};
    json json_request = {{{"property", "xlabel"}, {"text", text}}};
    request.command = json_request.dump();
    output_.Update(request);
  }

  void SetYLabel(const std::string& axes_id, const std::string& text) {
    use_cases::SetAxesPropertiesRequest request = {.axes_id = axes_id};
    json json_request = {{{"property", "ylabel"}, {"text", text}}};
    request.command = json_request.dump();
    output_.Update(request);
  }

  void SetTitle(const std::string& axes_id, const std::string& text) {
    use_cases::SetAxesPropertiesRequest request = {.axes_id = axes_id};
    json json_request = {{{"property", "title"}, {"text", text}}};
    request.command = json_request.dump();
    output_.Update(request);
  }

  void SetLegend(const std::string& axes_id, bool enable,
                 const std::vector<std::string> labels = {}, const Options options = {}) {
    use_cases::SetAxesPropertiesRequest request = {.axes_id = axes_id};
    json json_request = {
        {{"property", "legend_enable"}, {"enable", enable}},
        {{"property", "plot_labels"}, {"labels", labels}},
        {{"property", "legend_options"}, {"options", options}},
    };
    request.command = json_request.dump();
    output_.Update(request);
  }

 private:
  use_cases::ISetAxesPropertiesInput& output_;
};

}  // namespace controller
}  // namespace plotcraft
