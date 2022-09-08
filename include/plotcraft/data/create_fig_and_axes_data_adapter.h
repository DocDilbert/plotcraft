#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "plotcraft/data/repository.h"
#include "plotcraft/use_cases/model/i_create_fig_and_axes_data_access.h"

namespace plotcraft {
namespace data {

class CreateFigAndAxesDataAdapter : public use_cases::ICreateFigAndAxesDataAccess {
 public:
  CreateFigAndAxesDataAdapter(data::Repository& repo) : repo_(repo) {}

  virtual void AddAxesToFigure(
      const std::string& figure_id,
      const use_cases::ICreateFigAndAxesDataAccess::AxesData& data) override {
    auto figure = repo_.GetFigure(figure_id);

    data::Axes axes = {
        .axes_id = data.axes_id,
        .viewport_left = data.viewport_left,
        .viewport_bottom = data.viewport_bottom,
        .viewport_width = data.viewport_width,
        .viewport_height = data.viewport_height,

    };

    for (auto& it : data.axis) {
      auto ot = data::AxisOrientation::kVertical;
      if (it.orientation == use_cases::ICreateFigAndAxesDataAccess::Orientation::kHorizontal) {
        ot = data::AxisOrientation::kHorizontal;
      }

      axes.axis.push_back(data::Axis{.orientation = ot});
    };

    figure.axes_ids.push_back(data.axes_id);
    repo_.UpdateFigure(figure_id, figure);
    repo_.AddAxes(data.axes_id, axes);
  }

  virtual void AddFigure(const use_cases::ICreateFigAndAxesDataAccess::FigureData& data) override {
    //
    data::Figure figure = {.figure_id = data.figure_id,
                           .margins =
                               {
                                   .left = data.margins.left,
                                   .top = data.margins.top,
                                   .bottom = data.margins.bottom,
                                   .right = data.margins.right,

                               },
                           .paddings =
                               {
                                   .left = data.paddings.left,
                                   .top = data.paddings.top,
                                   .bottom = data.paddings.bottom,
                                   .right = data.paddings.right,
                               },
                           .axes_ids = std::vector<std::string>()

    };
    repo_.AddFigure(data.figure_id, figure);
  }

 private:
  data::Repository& repo_;
};

}  // namespace data
}  // namespace plotcraft
