
#pragma once

#include <memory>
#include <string>

#include "plotcraft/entities/axes.h"
#include "plotcraft/entities/axis.h"
#include "plotcraft/entities/figure.h"
#include "plotcraft/entities/orientation.h"
#include "plotcraft/use_cases/i_id_generator.h"
#include "plotcraft/use_cases/model/i_create_fig_and_axes_data_access.h"
#include "plotcraft/use_cases/model/i_create_fig_and_axes_input.h"
#include "plotcraft/use_cases/model/i_create_fig_and_axes_output.h"

namespace plotcraft {
namespace use_cases {

class CreateFigAndAxesInteractor : public ICreateFigAndAxesInput {
 private:
 public:
  CreateFigAndAxesInteractor(ICreateFigAndAxesOutput& output,
                             ICreateFigAndAxesDataAccess& create_figure_repo_access,
                             IIdGenerator& id_gen)
      : output_(output), data_access_(create_figure_repo_access), id_gen_(id_gen) {}

  void Create(CreateFigAndAxesRequest request) override {
    // *******************************
    // CREATE MODEL
    // *******************************
    entities::Axis vertical = {.orientation = entities::Orientation::kVertical};

    entities::Axis horizontal = {.orientation = entities::Orientation::kHorizontal};

    entities::Axes axes = {.viewport = entities::Rect(0.0, 0.0, 1.0, 1.0),
                           .axis = {horizontal, vertical}};

    entities::Figure fig = {
        .margins = {.left = 10.0f, .top = 10.0f, .bottom = 10.0f, .right = 10.0f},
        .paddings = {.left = 100.0f, .top = 35.0f, .bottom = 70.0f, .right = 30.0f},
        .axes = {axes}};

    // *******************************
    // SEND MODEL
    // *******************************

    // ADD FIGURE
    ICreateFigAndAxesDataAccess::FigureData figure_data;
    figure_data.figure_id = id_gen_.GetId("FIGURE");
    figure_data.margins = {.left = fig.margins.left,
                           .top = fig.margins.top,
                           .bottom = fig.margins.bottom,
                           .right = fig.margins.right};
    figure_data.paddings = {.left = fig.paddings.left,
                            .top = fig.paddings.top,
                            .bottom = fig.paddings.bottom,
                            .right = fig.paddings.right};

    data_access_.AddFigure(figure_data);

    // ADD AXIS TO AXES
    std::vector<ICreateFigAndAxesDataAccess::AxisData> v_axis_data;
    for (auto& axis : axes.axis) {
      ICreateFigAndAxesDataAccess::AxisData axis_data;

      if (axis.orientation == entities::Orientation::kHorizontal) {
        axis_data.orientation = ICreateFigAndAxesDataAccess::Orientation::kHorizontal;
      } else {
        axis_data.orientation = ICreateFigAndAxesDataAccess::Orientation::kVertical;
      }

      v_axis_data.push_back(axis_data);
    }

    // ADD AXES
    ICreateFigAndAxesDataAccess::AxesData axes_data;
    axes_data.axes_id = id_gen_.GetId("AXES");
    axes_data.viewport_left = axes.viewport.left;
    axes_data.viewport_bottom = axes.viewport.bottom;
    axes_data.viewport_width = axes.viewport.width;
    axes_data.viewport_height = axes.viewport.height;
    axes_data.axis = v_axis_data;
    data_access_.AddAxesToFigure(figure_data.figure_id, axes_data);

    CreateFigAndAxesResponse response = {.figure_id = figure_data.figure_id,
                                         .axes_id = axes_data.axes_id};

    output_.IsCreated(response);
  }

 private:
  ICreateFigAndAxesOutput& output_;
  ICreateFigAndAxesDataAccess& data_access_;
  IIdGenerator& id_gen_;
};

}  // namespace use_cases
}  // namespace plotcraft
