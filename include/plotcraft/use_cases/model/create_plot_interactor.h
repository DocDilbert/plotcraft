
#pragma once

#include <spdlog/spdlog.h>

#include <memory>
#include <string>

#include "plotcraft/use_cases/i_id_generator.h"
#include "plotcraft/use_cases/model/i_create_plot_data_access.h"
#include "plotcraft/use_cases/model/i_create_plot_input.h"
#include "plotcraft/use_cases/model/i_create_plot_output.h"

namespace plotcraft {
namespace use_cases {

class CreatePlotInteractor : public ICreatePlotInput {
 public:
  CreatePlotInteractor(ICreatePlotOutput& output, ICreatePlotDataAccess& create_plot_repo_access,
                       IIdGenerator& id_gen)

      : output_(output), data_access_(create_plot_repo_access), id_gen_(id_gen) {}

  void Create(CreatePlotRequest request) override {
    auto plot_id = id_gen_.GetId("PLOT");

    if (request.autoscale) {
      auto max_x_it = max_element(std::begin(request.x), std::end(request.x));
      auto min_x_it = min_element(std::begin(request.x), std::end(request.x));
      auto max_y_it = max_element(std::begin(request.y), std::end(request.y));
      auto min_y_it = min_element(std::begin(request.y), std::end(request.y));

      auto max_x = *max_x_it;
      auto min_x = *min_x_it;
      auto max_y = *max_y_it;
      auto min_y = *min_y_it;

      double interval_x = max_x - min_x;
      double interval_y = max_y - min_y;
      min_x = min_x - interval_x * kMargin;
      max_x = max_x + interval_x * kMargin;
      min_y = min_y - interval_y * kMargin;
      max_y = max_y + interval_y * kMargin;

      auto viewport = data_access_.GetViewPort(request.axes_id);
      if (data_access_.GetPlotCount(request.axes_id) != 0) {
        auto vp_min_x = viewport.left;
        auto vp_max_x = viewport.width + viewport.left;
        auto vp_min_y = viewport.bottom;
        auto vp_max_y = viewport.height + viewport.bottom;

        max_x = std::max(max_x, vp_max_x);
        min_x = std::min(min_x, vp_min_x);
        max_y = std::max(max_y, vp_max_y);
        min_y = std::min(min_y, vp_min_y);
      }

      viewport.left = min_x;
      viewport.width = max_x - min_x;
      viewport.bottom = min_y;
      viewport.height = max_y - min_y;
      data_access_.UpdateViewPort(request.axes_id, viewport);
    }

    ICreatePlotDataAccess::PlotData plot_data = {.plot_id = plot_id,
                                                 .x = request.x,
                                                 .y = request.y,
                                                 .color = request.color,
                                                 .makerstyle = request.markerstyle};
    data_access_.AddPlotToAxes(request.axes_id, plot_data, request.label);

    CreatePlotResponse response = {.plot_id = plot_id};
    output_.IsPlotCreated(response);
  }

 private:
  static constexpr double kMargin = 0.05;

  ICreatePlotOutput& output_;
  ICreatePlotDataAccess& data_access_;
  IIdGenerator& id_gen_;
};

}  // namespace use_cases
}  // namespace plotcraft
