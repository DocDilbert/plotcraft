#pragma once

#include <memory>
#include <nlohmann/json.hpp>

#include "plotcraft/use_cases/model/i_set_figure_properties_input.h"

namespace plotcraft {
namespace controller {

using json = nlohmann::json;

class SetFigurePropertiesController {
 private:
  typedef std::map<std::string, std::string> Options;

 public:
  SetFigurePropertiesController(use_cases::ISetFigurePropertiesInput& output) : output_(output) {}

 private:
  use_cases::ISetFigurePropertiesInput& output_;
};

}  // namespace controller
}  // namespace plotcraft
