
#pragma once

#include <spdlog/spdlog.h>

#include <exception>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

#include "plotcraft/entities/axes.h"
#include "plotcraft/entities/axis.h"
#include "plotcraft/entities/figure.h"
#include "plotcraft/entities/orientation.h"
#include "plotcraft/use_cases/i_id_generator.h"
#include "plotcraft/use_cases/model/i_set_plot_list_properties_data_access.h"
#include "plotcraft/use_cases/model/i_set_plot_list_properties_input.h"
#include "plotcraft/use_cases/model/i_set_plot_list_properties_output.h"

namespace plotcraft {
namespace use_cases {

using json = nlohmann::json;

class SetPlotListPropertiesInteractor : public ISetPlotListPropertiesInput {
 private:
  typedef std::map<std::string, std::string> Options;

 public:
  SetPlotListPropertiesInteractor(
      ISetPlotListPropertiesOutput& output,
      ISetPlotListPropertiesDataAccess& update_axes_viewport_repo_access)
      : output_(output), data_access_(update_axes_viewport_repo_access) {}

  void Update(SetPlotListPropertiesRequest request) override {
    auto data = json::parse(request.command);
    if (data["property"] == "plot_labels") {
      auto labels = data["labels"].get<std::vector<std::string>>();
      data_access_.SetPlotLabels(request.axes_id, labels);
    } else {
      throw std::exception();
    }
    SetPlotListPropertiesResponse response;
    output_.IsViewportChange(response);
  }

 private:
  ISetPlotListPropertiesOutput& output_;
  ISetPlotListPropertiesDataAccess& data_access_;
};

}  // namespace use_cases
}  // namespace plotcraft
