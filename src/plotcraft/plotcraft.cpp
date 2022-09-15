#include "plotcraft/plotcraft.h"

#include <fmt/core.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
//#include <spdlog/sinks/null_sink.h>
#include <spdlog/spdlog.h>

#include "plotcraft/controller/create_fig_and_axes_controller.h"
#include "plotcraft/controller/draw_controller.h"
#include "plotcraft/controller/plot_controller.h"
#include "plotcraft/controller/set_axes_properties_controller.h"
#include "plotcraft/controller/set_figure_properties_controller.h"
#include "plotcraft/data/create_fig_and_axes_data_adapter.h"
#include "plotcraft/data/create_plot_data_adapter.h"
#include "plotcraft/data/draw_figure_data_adapter.h"
#include "plotcraft/data/repository.h"
#include "plotcraft/data/set_axes_properties_data_adapter.h"
#include "plotcraft/data/set_figure_properties_data_adapter.h"
#include "plotcraft/framework/id_generator.h"
#include "plotcraft/gateway/measure_gateway.h"
#include "plotcraft/presenter/create_fig_and_axis_presenter.h"
#include "plotcraft/presenter/draw_presenter.h"
#include "plotcraft/presenter/i_draw_primitives.h"
#include "plotcraft/presenter/plot_presenter.h"
#include "plotcraft/presenter/set_axes_properties_presenter.h"
#include "plotcraft/presenter/set_figure_properties_presenter.h"
#include "plotcraft/use_cases/draw/draw_figure_interactor.h"
#include "plotcraft/use_cases/i_measure.h"
#include "plotcraft/use_cases/model/create_fig_and_axes_interactor.h"
#include "plotcraft/use_cases/model/create_plot_interactor.h"
#include "plotcraft/use_cases/model/set_axes_properties_interactor.h"
#include "plotcraft/use_cases/model/set_figure_properties_interactor.h"

namespace plotcraft {

struct PlotCraft::PlotCraftImpl {
  plotcraft::data::Repository repo;
  plotcraft::db::IdGenerator id_generator;
};

PlotCraft::PlotCraft() : pimpl_(std::make_unique<PlotCraft::PlotCraftImpl>()) {}

PlotCraft::~PlotCraft() {}

void PlotCraft::Figure() {
  plotcraft::presenter::CreateFigAndAxesPresenter create_fig_and_axes_presenter;

  plotcraft::data::CreateFigAndAxesDataAdapter create_fig_and_axes_data_adapter(pimpl_->repo);

  plotcraft::use_cases::CreateFigAndAxesInteractor create_fig_and_axes_interactor(
      create_fig_and_axes_presenter, create_fig_and_axes_data_adapter, pimpl_->id_generator);

  plotcraft::controller::CreateFigAndAxesController create_fig_and_axes_controller(
      create_fig_and_axes_interactor);

  create_fig_and_axes_controller.Figure();

  if (create_fig_and_axes_presenter.IsCreated()) {
    figure_id_ = create_fig_and_axes_presenter.GetFigureId();
    axes_id_ = create_fig_and_axes_presenter.GetAxesId();
    spdlog::info("Figure created with id '{}'. Axes created with id '{}'", figure_id_, axes_id_);
  }
}

void PlotCraft::Plot(const std::vector<double>& x, const std::vector<double>& y,
                     const std::map<std::string, std::string> options) {
  plotcraft::data::CreatePlotDataAdapter create_plot_data_adapter(pimpl_->repo);
  plotcraft::presenter::PlotPresenter plot_presenter;

  plotcraft::use_cases::CreatePlotInteractor plot_interactor(
      plot_presenter, create_plot_data_adapter, pimpl_->id_generator);

  plotcraft::controller::PlotController plot_controller(plot_interactor);

  plot_controller.Plot(axes_id_, x, y, options);

  if (plot_presenter.IsCreated()) {
    auto plot_id = plot_presenter.GetPlotId();
    spdlog::info("Plot created with id '{}' and added to axes '{}'", plot_id, axes_id_);
  }
}

void PlotCraft::Draw(plotcraft::presenter::IDrawPrimitives& draw_primitives,
                     plotcraft::gateway::IMeasure& measure, int left, int bottom, int width,
                     int height) {
  spdlog::info("Drawing of figure '{}' started. width={}, height={}", figure_id_, width, height);
  plotcraft::gateway::MeasureGateway measure_gw(measure);
  plotcraft::data::DrawFigureDataAdapter draw_figure_data_adapter(pimpl_->repo);
  plotcraft::presenter::DrawPresenter draw_presenter(draw_primitives);

  plotcraft::use_cases::DrawFigureInteractor draw_figure_interactor(
      draw_presenter, draw_figure_data_adapter, measure_gw);

  plotcraft::controller::DrawController draw_controller(draw_figure_interactor);
  try {
    draw_controller.Draw(figure_id_, left, bottom, width, height);
  } catch (const std::exception& exc) {
    std::cout << "EXCEPTION " << exc.what() << std::endl;
    exit(-1);
  }

  spdlog::info("Drawing of figure '{}' finished. Draw Calls = {}", draw_presenter.GetFigureId(),
               draw_presenter.GetDrawCalls());
}

void PlotCraft::Xlim(double left, double right) {
  plotcraft::data::SetAxesPropertiesDataAdapter set_axes_properties_data_adapter(pimpl_->repo);

  plotcraft::presenter::SetAxesPropertiesPresenter set_axes_properties_presenter;

  plotcraft::use_cases::SetAxesPropertiesInteractor set_axes_properties_interactor(
      set_axes_properties_presenter, set_axes_properties_data_adapter);

  plotcraft::controller::SetAxesPropertiesController set_axes_properties_controller(
      set_axes_properties_interactor);

  set_axes_properties_controller.UpdateXRange(axes_id_, left, right);

  if (set_axes_properties_presenter.IsCreated()) {
    spdlog::info("UpdateXRange returned successfully");
  }
}

void PlotCraft::Ylim(double bottom, double top) {
  plotcraft::data::SetAxesPropertiesDataAdapter set_axes_properties_data_adapter(pimpl_->repo);

  plotcraft::presenter::SetAxesPropertiesPresenter set_axes_properties_presenter;
  plotcraft::use_cases::SetAxesPropertiesInteractor set_axes_properties_interactor(
      set_axes_properties_presenter, set_axes_properties_data_adapter);

  plotcraft::controller::SetAxesPropertiesController set_axes_properties_controller(
      set_axes_properties_interactor);

  set_axes_properties_controller.UpdateYRange(axes_id_, bottom, top);

  if (set_axes_properties_presenter.IsCreated()) {
    spdlog::info("UpdateYRange returned successfully");
  }
}

void PlotCraft::XLabel(const std::string text) {
  plotcraft::data::SetAxesPropertiesDataAdapter set_axes_properties_data_adapter(pimpl_->repo);

  plotcraft::presenter::SetAxesPropertiesPresenter set_axes_properties_presenter;
  plotcraft::use_cases::SetAxesPropertiesInteractor set_axes_properties_interactor(
      set_axes_properties_presenter, set_axes_properties_data_adapter);

  plotcraft::controller::SetAxesPropertiesController set_axes_properties_controller(
      set_axes_properties_interactor);

  set_axes_properties_controller.SetXLabel(axes_id_, text);

  if (set_axes_properties_presenter.IsCreated()) {
    spdlog::info("SetXLabel returned successfully");
  }
}

void PlotCraft::YLabel(const std::string text) {
  plotcraft::data::SetAxesPropertiesDataAdapter set_axes_properties_data_adapter(pimpl_->repo);

  plotcraft::presenter::SetAxesPropertiesPresenter set_axes_properties_presenter;
  plotcraft::use_cases::SetAxesPropertiesInteractor set_axes_properties_interactor(
      set_axes_properties_presenter, set_axes_properties_data_adapter);

  plotcraft::controller::SetAxesPropertiesController set_axes_properties_controller(
      set_axes_properties_interactor);

  set_axes_properties_controller.SetYLabel(axes_id_, text);

  if (set_axes_properties_presenter.IsCreated()) {
    spdlog::info("SetYLabel returned successfully");
  }
}

void PlotCraft::Title(const std::string text) {
  plotcraft::data::SetAxesPropertiesDataAdapter set_axes_properties_data_adapter(pimpl_->repo);

  plotcraft::presenter::SetAxesPropertiesPresenter set_axes_properties_presenter;
  plotcraft::use_cases::SetAxesPropertiesInteractor set_axes_properties_interactor(
      set_axes_properties_presenter, set_axes_properties_data_adapter);

  plotcraft::controller::SetAxesPropertiesController set_axes_properties_controller(
      set_axes_properties_interactor);

  set_axes_properties_controller.SetTitle(axes_id_, text);

  if (set_axes_properties_presenter.IsCreated()) {
    spdlog::info("SetTitle returned successfully");
  }
}

void PlotCraft::Legend() {
  // ---
  // Set axes properties use case
  plotcraft::data::SetAxesPropertiesDataAdapter set_axes_properties_data_adapter(pimpl_->repo);

  plotcraft::presenter::SetAxesPropertiesPresenter set_axes_properties_presenter;
  plotcraft::use_cases::SetAxesPropertiesInteractor set_axes_properties_interactor(
      set_axes_properties_presenter, set_axes_properties_data_adapter);

  plotcraft::controller::SetAxesPropertiesController set_axes_properties_controller(
      set_axes_properties_interactor);

  set_axes_properties_controller.SetLegend(axes_id_, true);

  if (set_axes_properties_presenter.IsCreated()) {
    spdlog::info("Legend returned successfully");
  }
}

void PlotCraft::Legend(const std::vector<std::string> labels, const Options options) {
  // ---
  // Set axes properties use case
  plotcraft::data::SetAxesPropertiesDataAdapter set_axes_properties_data_adapter(pimpl_->repo);

  plotcraft::presenter::SetAxesPropertiesPresenter set_axes_properties_presenter;
  plotcraft::use_cases::SetAxesPropertiesInteractor set_axes_properties_interactor(
      set_axes_properties_presenter, set_axes_properties_data_adapter);

  plotcraft::controller::SetAxesPropertiesController set_axes_properties_controller(
      set_axes_properties_interactor);

  set_axes_properties_controller.SetLegend(axes_id_, true, labels, options);

  if (set_axes_properties_presenter.IsCreated()) {
    spdlog::info("Legend returned successfully");
  }
}
}  // namespace plotcraft
