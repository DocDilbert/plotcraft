#pragma once

#include <memory>

#include "plotcraft/use_cases/model/i_create_fig_and_axes_input.h"

namespace plotcraft {
namespace controller {

class CreateFigAndAxesController {
 public:
  CreateFigAndAxesController(use_cases::ICreateFigAndAxesInput& output) : output_(output) {}

  void Figure() {
    use_cases::CreateFigAndAxesRequest request = {};
    output_.Create(request);
  };

 private:
  use_cases::ICreateFigAndAxesInput& output_;
};

}  // namespace controller
}  // namespace plotcraft
