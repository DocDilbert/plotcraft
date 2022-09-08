
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
#include "plotcraft/use_cases/model/i_set_axes_properties_input.h"
#include "plotcraft/use_cases/model/i_set_axes_properties_output.h"
#include "plotcraft/use_cases/model/i_set_axes_properties_repo_access.h"

namespace plotcraft {
namespace use_cases {

using json = nlohmann::json;

class SetAxesPropertiesInteractor : public ISetAxesPropertiesInput {
 private:
 public:
  SetAxesPropertiesInteractor(ISetAxesPropertiesOutput& output, ISetAxesPropertiesRepoAccess& update_axes_viewport_repo_access)
      : output_(output), update_axes_viewport_repo_access_(update_axes_viewport_repo_access) {}

  void Update(SetAxesPropertiesRequest request) override {
    auto data = json::parse(request.command);
    if (data["property"] == "xlim") {
      auto left = data["viewport_left"].get<double>();
      auto right = data["viewport_right"].get<double>();
      update_axes_viewport_repo_access_.SetHorizontalViewport(request.axes_id, left, right - left);
    } else if (data["property"] == "ylim") {
      auto bottom = data["viewport_bottom"].get<double>();
      auto top = data["viewport_top"].get<double>();
      update_axes_viewport_repo_access_.SetVerticalViewport(request.axes_id, bottom, top - bottom);
    } else if (data["property"] == "xlabel") {
      auto text = data["text"].get<std::string>();
      update_axes_viewport_repo_access_.SetXLabel(request.axes_id, text);
    } else if (data["property"] == "ylabel") {
      auto text = data["text"].get<std::string>();
      update_axes_viewport_repo_access_.SetYLabel(request.axes_id, text);
    } else if (data["property"] == "title") {
      auto text = data["text"].get<std::string>();
      update_axes_viewport_repo_access_.SetTitle(request.axes_id, text);
    } else {
      throw std::exception();
    }
    SetAxesPropertiesResponse response;
    output_.IsViewportChange(response);
  }

 private:
  ISetAxesPropertiesOutput& output_;
  ISetAxesPropertiesRepoAccess& update_axes_viewport_repo_access_;
};

}  // namespace use_cases
}  // namespace plotcraft
