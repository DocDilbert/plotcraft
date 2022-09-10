#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "plotcraft/data/axis.h"
#include "plotcraft/data/figure.h"
#include "plotcraft/data/repository.h"
#include "plotcraft/use_cases/model/i_set_plot_list_properties_data_access.h"

namespace plotcraft {
namespace data {

class SetPlotListPropertiesDataAdapter : public use_cases::ISetPlotListPropertiesDataAccess {
 public:
  SetPlotListPropertiesDataAdapter(data::Repository& repo) : repo_(repo) {}

  void SetPlotLabels(const std::string& axes_id, const std::vector<std::string>& entries) override {
    auto axes = repo_.GetAxes(axes_id);
    auto n_entries = entries.size();
    auto n_plots = axes.plots.size();

    auto n = std::min(n_plots, n_entries);
    for (size_t i = 0; i < n; i++) {
      auto& entry_str = entries[i];
      auto& plot = axes.plots[i];
      plot.label = entry_str;
    }
    repo_.UpdateAxes(axes_id, axes);
  }

 private:
  data::Repository& repo_;
};

}  // namespace data
}  // namespace plotcraft
