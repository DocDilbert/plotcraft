
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
#include "plotcraft/use_cases/model/i_set_figure_properties_data_access.h"
#include "plotcraft/use_cases/model/i_set_figure_properties_input.h"
#include "plotcraft/use_cases/model/i_set_figure_properties_output.h"

namespace plotcraft {
namespace use_cases {

using json = nlohmann::json;

class SetFigurePropertiesInteractor : public ISetFigurePropertiesInput {
 private:
  typedef std::map<std::string, std::string> Options;

 public:
  SetFigurePropertiesInteractor(ISetFigurePropertiesOutput& output,
                                ISetFigurePropertiesDataAccess& update_axes_viewport_repo_access)
      : output_(output), data_access_(update_axes_viewport_repo_access) {}

  void SetProperties(SetFigurePropertiesRequest request) override {
    auto data = json::parse(request.command);
    throw std::exception();
    SetFigurePropertiesResponse response;
    output_.IsViewportChange(response);
  }

 private:
  ISetFigurePropertiesOutput& output_;
  ISetFigurePropertiesDataAccess& data_access_;
};

}  // namespace use_cases
}  // namespace plotcraft
