#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "plotcraft/data/figure.h"
#include "plotcraft/data/repository.h"
#include "plotcraft/use_cases/draw/i_draw_figure_repo_access.h"

namespace plotcraft {
namespace gateway {

class DrawFigureRepoGateway : public use_cases::IDrawFigureRepoAccesss {
 public:
  DrawFigureRepoGateway(data::Repository& repo) : repo_(repo) {}

  std::vector<std::string> GetAxesIds(const std::string& figure_id) override {
    const auto& figure = repo_.GetFigure(figure_id);
    return figure.axes_ids;
  }

  use_cases::IDrawFigureRepoAccesss::MarginData GetMargins(const std::string& figure_id) override {
    const auto& figure = repo_.GetFigure(figure_id);
    use_cases::IDrawFigureRepoAccesss::MarginData ret = {.left = figure.margins.left,
                                                         .top = figure.margins.top,
                                                         .bottom = figure.margins.bottom,
                                                         .right = figure.margins.right};
    return ret;
  }

  use_cases::IDrawFigureRepoAccesss::MarginData GetPaddings(const std::string& figure_id) override {
    const auto& figure = repo_.GetFigure(figure_id);
    use_cases::IDrawFigureRepoAccesss::MarginData ret = {.left = figure.paddings.left,
                                                         .top = figure.paddings.top,
                                                         .bottom = figure.paddings.bottom,
                                                         .right = figure.paddings.right};
    return ret;
  }

  use_cases::IDrawFigureRepoAccesss::AxesData GetAxesData(const std::string& axes_id) override {
    const auto& axes = repo_.GetAxes(axes_id);
    use_cases::IDrawFigureRepoAccesss::AxesData ret{.viewport_left = axes.viewport_left,
                                                    .viewport_bottom = axes.viewport_bottom,
                                                    .viewport_width = axes.viewport_width,
                                                    .viewport_height = axes.viewport_height,
                                                    .axis = {},
                                                    .plots = {},
                                                    .xlabel = axes.xlabel,
                                                    .ylabel = axes.ylabel,
                                                    .title = axes.title

    };

    for (auto& it : axes.axis) {
      auto ot = use_cases::IDrawFigureRepoAccesss::Orientation::kVertical;

      if (it.orientation == data::AxisOrientation::kHorizontal) {
        ot = use_cases::IDrawFigureRepoAccesss::Orientation::kHorizontal;
      }
      ret.axis.push_back(use_cases::IDrawFigureRepoAccesss::AxisData{.orientation = ot});
    }
    for (auto& it : axes.plots) {
      const auto& data2d = repo_.GetData2d(it.plot_data2d_id);

      use_cases::IDrawFigureRepoAccesss::Plot2dData data = {.x = data2d.x,
                                                            .y = data2d.y,
                                                            .label = it.label,
                                                            .color = it.color,
                                                            .markerstyle = it.markerstyle};

      ret.plots.push_back(data);
    }

    return ret;
  }

 private:
  data::Repository& repo_;
};

}  // namespace gateway
}  // namespace plotcraft
