#pragma once

#include <iostream>
#include <memory>

#include "plotcraft/use_cases/model/i_create_plot_output.h"

namespace plotcraft {
namespace presenter {

class CreatePlotPresenter : public use_cases::ICreatePlotOutput {
 public:
  CreatePlotPresenter() {}

  void IsPlotCreated(const use_cases::CreatePlotResponse& response) override {
    is_created_ = true;
    plot_id_ = response.plot_id;
  }

  bool IsCreated() { return is_created_; }

  const std::string& GetPlotId() { return plot_id_; }

 private:
  bool is_created_ = {false};
  std::string plot_id_ = {"invalid"};
};

}  // namespace presenter
}  // namespace plotcraft
