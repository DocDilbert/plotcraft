#include "plotcraft/plotcraft.h"

#include <fmt/core.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
//#include <spdlog/sinks/null_sink.h>
#include <spdlog/spdlog.h>

#include "plotcraft/controller/draw_controller.h"
#include "plotcraft/controller/fig_and_axes_controller.h"
#include "plotcraft/controller/plot_controller.h"
#include "plotcraft/controller/set_axes_properties_controller.h"
#include "plotcraft/data/repository.h"
#include "plotcraft/framework/id_generator.h"
#include "plotcraft/gateway/create_fig_and_axes_repo_gateway.h"
#include "plotcraft/gateway/create_plot_repo_gateway.h"
#include "plotcraft/gateway/draw_figure_repo_gateway.h"
#include "plotcraft/gateway/measure_gateway.h"
#include "plotcraft/gateway/set_axes_properties_repo_gateway.h"
#include "plotcraft/presenter/draw_presenter.h"
#include "plotcraft/presenter/fig_and_axis_presenter.h"
#include "plotcraft/presenter/i_draw_primitives.h"
#include "plotcraft/presenter/plot_presenter.h"
#include "plotcraft/presenter/set_axes_properties_presenter.h"
#include "plotcraft/use_cases/draw/draw_figure_interactor.h"
#include "plotcraft/use_cases/i_measure.h"
#include "plotcraft/use_cases/model/create_fig_and_axes_interactor.h"
#include "plotcraft/use_cases/model/create_plot_interactor.h"
#include "plotcraft/use_cases/model/set_axes_properties_interactor.h"

namespace plotcraft {

struct PlotCraft::PlotCraftImpl {
  plotcraft::data::Repository repo;
  plotcraft::db::IdGenerator id_generator;
};

PlotCraft::PlotCraft() : pimpl_(std::make_unique<PlotCraft::PlotCraftImpl>()) {}

PlotCraft::~PlotCraft() {}

void PlotCraft::Figure() {
  plotcraft::presenter::FigAndAxesPresenter fig_and_axes_presenter;

  auto create_figure_repo_gw = plotcraft::gateway::CreateFigAndAxesRepoGateway(pimpl_->repo);

  plotcraft::use_cases::CreateFigAndAxesInteractor fig_and_axes_interactor(
      fig_and_axes_presenter, create_figure_repo_gw, pimpl_->id_generator);

  plotcraft::controller::FigAndAxesController fig_and_axes_controller(fig_and_axes_interactor);

  fig_and_axes_controller.Figure();

  if (fig_and_axes_presenter.IsCreated()) {
    figure_id_ = fig_and_axes_presenter.GetFigureId();
    axes_id_ = fig_and_axes_presenter.GetAxesId();
    spdlog::info("Figure created with id '{}'. Axes created with id '{}'", figure_id_, axes_id_);
  }
}

void PlotCraft::Plot(const std::vector<double>& x, const std::vector<double>& y,
                     const std::map<std::string, std::string> options) {
  plotcraft::gateway::CreatePlotRepoGateway create_plot_repo_gw(pimpl_->repo);
  plotcraft::presenter::PlotPresenter plot_presenter;

  plotcraft::use_cases::CreatePlotInteractor plot_interactor(plot_presenter, create_plot_repo_gw,
                                                             pimpl_->id_generator);

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
  spdlog::info("Drawing of figure '{}' started", figure_id_);
  plotcraft::gateway::MeasureGateway measure_gw(measure);
  plotcraft::gateway::DrawFigureRepoGateway draw_figure_repo_gw(pimpl_->repo);
  plotcraft::presenter::DrawPresenter draw_presenter(draw_primitives);

  plotcraft::use_cases::DrawFigureInteractor draw_figure_interactor(
      draw_presenter, draw_figure_repo_gw, measure_gw);

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
  plotcraft::gateway::SetAxesPropertiesRepoGateway update_axes_properties_repo_gw(pimpl_->repo);

  plotcraft::presenter::SetAxesPropertiesPresenter update_axes_properties_presenter;

  plotcraft::use_cases::SetAxesPropertiesInteractor update_axes_properties_interactor(
      update_axes_properties_presenter, update_axes_properties_repo_gw);

  plotcraft::controller::SetAxesPropertiesController update_axes_properties_controller(
      update_axes_properties_interactor);

  update_axes_properties_controller.UpdateXRange(axes_id_, left, right);

  if (update_axes_properties_presenter.IsCreated()) {
    spdlog::info("Update axes view port - X ");
  }
}

void PlotCraft::Ylim(double bottom, double top) {
  plotcraft::gateway::SetAxesPropertiesRepoGateway update_axes_properties_repo_gw(pimpl_->repo);

  plotcraft::presenter::SetAxesPropertiesPresenter update_axes_properties_presenter;
  plotcraft::use_cases::SetAxesPropertiesInteractor update_axes_properties_interactor(
      update_axes_properties_presenter, update_axes_properties_repo_gw);

  plotcraft::controller::SetAxesPropertiesController update_axes_properties_controller(
      update_axes_properties_interactor);

  update_axes_properties_controller.UpdateYRange(axes_id_, bottom, top);

  if (update_axes_properties_presenter.IsCreated()) {
    spdlog::info("Update axes view port - Y");
  }
}

void PlotCraft::XLabel(const std::string& text) {
  plotcraft::gateway::SetAxesPropertiesRepoGateway update_axes_properties_repo_gw(pimpl_->repo);

  plotcraft::presenter::SetAxesPropertiesPresenter update_axes_properties_presenter;
  plotcraft::use_cases::SetAxesPropertiesInteractor update_axes_properties_interactor(
      update_axes_properties_presenter, update_axes_properties_repo_gw);

  plotcraft::controller::SetAxesPropertiesController update_axes_properties_controller(
      update_axes_properties_interactor);

  update_axes_properties_controller.SetXLabel(axes_id_, text);

  if (update_axes_properties_presenter.IsCreated()) {
    spdlog::info("Set x label");
  }
}

void PlotCraft::YLabel(const std::string& text) {
  plotcraft::gateway::SetAxesPropertiesRepoGateway update_axes_properties_repo_gw(pimpl_->repo);

  plotcraft::presenter::SetAxesPropertiesPresenter update_axes_properties_presenter;
  plotcraft::use_cases::SetAxesPropertiesInteractor update_axes_properties_interactor(
      update_axes_properties_presenter, update_axes_properties_repo_gw);

  plotcraft::controller::SetAxesPropertiesController update_axes_properties_controller(
      update_axes_properties_interactor);

  update_axes_properties_controller.SetYLabel(axes_id_, text);

  if (update_axes_properties_presenter.IsCreated()) {
    spdlog::info("Set y label");
  }
}

void PlotCraft::Title(const std::string& text) {
  plotcraft::gateway::SetAxesPropertiesRepoGateway update_axes_properties_repo_gw(pimpl_->repo);

  plotcraft::presenter::SetAxesPropertiesPresenter update_axes_properties_presenter;
  plotcraft::use_cases::SetAxesPropertiesInteractor update_axes_properties_interactor(
      update_axes_properties_presenter, update_axes_properties_repo_gw);

  plotcraft::controller::SetAxesPropertiesController update_axes_properties_controller(
      update_axes_properties_interactor);

  update_axes_properties_controller.SetTitle(axes_id_, text);

  if (update_axes_properties_presenter.IsCreated()) {
    spdlog::info("Set y label");
  }
}
}  // namespace plotcraft
