#pragma once

#include <spdlog/spdlog.h>

#include <algorithm>
#include <string>
#include <vector>

#include "plotcraft/data/data2d.h"
#include "plotcraft/data/figure.h"
#include "plotcraft/data/plot2d.h"
#include "plotcraft/data/repository.h"
#include "plotcraft/use_cases/model/i_create_plot_repo_access.h"

namespace plotcraft {
namespace gateway {

class CreatePlotRepoGateway : public use_cases::ICreatePlotRepoAccess {
 public:
  CreatePlotRepoGateway(data::Repository& repo) : repo_(repo) {}

  unsigned GetPlotCount(const std::string& axes_id) override {
    const auto& axes = repo_.GetAxes(axes_id);
    return axes.plots.size();
  }

  ViewPortData GetViewPort(const std::string& axes_id) override {
    const auto& axes = repo_.GetAxes(axes_id);
    return ViewPortData{
        .left = axes.viewport_left,
        .bottom = axes.viewport_bottom,
        .width = axes.viewport_width,
        .height = axes.viewport_height,
    };
  }

  void UpdateViewPort(const std::string& axes_id, const ViewPortData& viewport) override {
    auto axes = repo_.GetAxes(axes_id);
    axes.viewport_left = viewport.left;
    axes.viewport_bottom = viewport.bottom;
    axes.viewport_width = viewport.width;
    axes.viewport_height = viewport.height;
    repo_.UpdateAxes(axes_id, axes);
  }

  void AddPlotToAxes(const std::string& axes_id, const PlotData& data,
                     const std::string& label) override {
    data::Data2d plot2d = {.data2d_id = data.plot_id, .x = data.x, .y = data.y};
    auto axes = repo_.GetAxes(axes_id);
    axes.plots.push_back(data::Plot2d{.plot_data2d_id = data.plot_id,
                                      .label = label,
                                      .color = data.color,
                                      .markerstyle = data.makerstyle});
    repo_.UpdateAxes(axes_id, axes);
    repo_.AddData2d(data.plot_id, plot2d);
  }

 private:
  data::Repository& repo_;
};

}  // namespace gateway
}  // namespace plotcraft
