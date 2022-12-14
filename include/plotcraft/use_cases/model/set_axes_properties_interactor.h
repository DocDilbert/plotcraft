
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
#include "plotcraft/use_cases/model/i_set_axes_properties_data_access.h"
#include "plotcraft/use_cases/model/i_set_axes_properties_input.h"
#include "plotcraft/use_cases/model/i_set_axes_properties_output.h"

namespace plotcraft {
namespace use_cases {

using json = nlohmann::json;

class SetAxesPropertiesInteractor : public ISetAxesPropertiesInput {
 private:
  typedef std::map<std::string, std::string> Options;

 public:
  SetAxesPropertiesInteractor(ISetAxesPropertiesOutput& output,
                              ISetAxesPropertiesDataAccess& update_axes_viewport_repo_access)
      : output_(output), data_access_(update_axes_viewport_repo_access) {}

  void SetProperties(SetAxesPropertiesRequest request) override {
    auto ldata = json::parse(request.command);

    for (auto& data : ldata) {
      if (data["property"] == "xlim") {
        auto left = data["viewport_left"].get<double>();
        auto right = data["viewport_right"].get<double>();
        data_access_.SetHorizontalViewport(request.axes_id, left, right - left);
      } else if (data["property"] == "ylim") {
        auto bottom = data["viewport_bottom"].get<double>();
        auto top = data["viewport_top"].get<double>();
        data_access_.SetVerticalViewport(request.axes_id, bottom, top - bottom);
      } else if (data["property"] == "xlabel") {
        auto text = data["text"].get<std::string>();
        data_access_.SetXLabel(request.axes_id, text);
      } else if (data["property"] == "ylabel") {
        auto text = data["text"].get<std::string>();
        data_access_.SetYLabel(request.axes_id, text);
      } else if (data["property"] == "title") {
        auto text = data["text"].get<std::string>();
        data_access_.SetTitle(request.axes_id, text);
      } else if (data["property"] == "legend_options") {
        auto options = data["options"].get<Options>();
        // currently does nothing
      } else if (data["property"] == "legend_enable") {
        auto enable = data["enable"].get<bool>();
        data_access_.SetLegendEnable(request.axes_id, enable);
      } else if (data["property"] == "plot_labels") {
        auto labels = data["labels"].get<std::vector<std::string>>();
        data_access_.SetLegendLabels(request.axes_id, labels);
      } else {
        throw std::exception();
      }
    }
    SetAxesPropertiesResponse response;
    output_.IsViewportChange(response);
  }

 private:
  ISetAxesPropertiesOutput& output_;
  ISetAxesPropertiesDataAccess& data_access_;
};

}  // namespace use_cases
}  // namespace plotcraft
