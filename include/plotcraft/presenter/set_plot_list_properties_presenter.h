#pragma once

#include <iostream>
#include <memory>

#include "plotcraft/use_cases/model/i_set_plot_list_properties_output.h"

namespace plotcraft {
namespace presenter {

class SetPlotListPropertiesPresenter : public use_cases::ISetPlotListPropertiesOutput {
 public:
  SetPlotListPropertiesPresenter() {}

  void IsViewportChange(use_cases::SetPlotListPropertiesResponse response) override {
    is_created_ = true;
    figure_id_ = response.figure_id;
    axes_id_ = response.axes_id;
  }

  bool IsCreated() { return is_created_; }

  const std::string& GetFigureId() { return figure_id_; }
  const std::string& GetAxesId() { return axes_id_; }

 private:
  bool is_created_ = {false};
  std::string figure_id_ = {"invalid"};
  std::string axes_id_ = {"invalid"};
};

}  // namespace presenter
}  // namespace plotcraft
