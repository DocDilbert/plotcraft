#pragma once

#include <spdlog/spdlog.h>

#include <algorithm>
#include <map>
#include <vector>

#include "plotcraft/data/axes.h"
#include "plotcraft/data/data2d.h"
#include "plotcraft/data/figure.h"

namespace plotcraft {
namespace data {

class Repository {
 public:
  Repository() {}

  void AddFigure(const std::string& figure_id, const Figure& figure) {
    figures_.insert({figure_id, figure});
  }

  const Figure& GetFigure(const std::string& figure_id) { return figures_[figure_id]; }

  void UpdateFigure(const std::string& figure_id, const Figure& figure) {
    auto itr = figures_.find(figure_id);

    if (itr != figures_.end()) {
      itr->second = figure;
    }
  }

  void AddAxes(const std::string& axes_id, const Axes& axes) { axes_.insert({axes_id, axes}); }

  void UpdateAxes(const std::string& axes_id, const Axes& axes) {
    auto itr = axes_.find(axes_id);
    if (itr != axes_.end()) {
      itr->second = axes;
    }
  }
  const Axes& GetAxes(const std::string& axes_id) { return axes_[axes_id]; }

  void AddData2d(const std::string& plot_id, const Data2d& plot) {
    data2d_.insert({plot_id, plot});
  }

  void UpdateData2d(const std::string& plot_id, const Data2d& plot) {
    auto itr = data2d_.find(plot_id);
    if (itr != data2d_.end()) {
      itr->second = plot;
    }
  }
  const Data2d& GetData2d(const std::string& plot_id) { return data2d_[plot_id]; }

 private:
  std::map<std::string, Figure> figures_;
  std::map<std::string, Axes> axes_;
  std::map<std::string, Data2d> data2d_;
};

}  // namespace data
}  // namespace plotcraft
