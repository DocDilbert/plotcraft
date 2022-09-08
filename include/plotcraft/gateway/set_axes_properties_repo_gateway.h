#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "plotcraft/data/axis.h"
#include "plotcraft/data/figure.h"
#include "plotcraft/data/repository.h"
#include "plotcraft/use_cases/model/i_set_axes_properties_repo_access.h"

namespace plotcraft {
namespace gateway {

class SetAxesPropertiesRepoGateway : public use_cases::ISetAxesPropertiesRepoAccess {
 public:
  SetAxesPropertiesRepoGateway(data::Repository& repo) : repo_(repo) {}

  void SetHorizontalViewport(const std::string& axes_id, double left, double width) override {
    auto axes = repo_.GetAxes(axes_id);
    axes.viewport_left = left;
    axes.viewport_width = width;
    repo_.UpdateAxes(axes_id, axes);
  }

  void SetVerticalViewport(const std::string& axes_id, double bottom, double height) override {
    auto axes = repo_.GetAxes(axes_id);
    axes.viewport_bottom = bottom;
    axes.viewport_height = height;
    repo_.UpdateAxes(axes_id, axes);
  }

  void SetXLabel(const std::string& axes_id, const std::string& text) override {
    auto axes = repo_.GetAxes(axes_id);
    axes.xlabel = text;
    repo_.UpdateAxes(axes_id, axes);
  }

  void SetYLabel(const std::string& axes_id, const std::string& text) override {
    auto axes = repo_.GetAxes(axes_id);
    axes.ylabel = text;
    repo_.UpdateAxes(axes_id, axes);
  }

  void SetTitle(const std::string& axes_id, const std::string& text) override {
    auto axes = repo_.GetAxes(axes_id);
    axes.title = text;
    repo_.UpdateAxes(axes_id, axes);
  }

 private:
  data::Repository& repo_;
};

}  // namespace gateway
}  // namespace plotcraft
