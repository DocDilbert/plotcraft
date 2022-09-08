#pragma once

#include <memory>
#include <string>

namespace plotcraft {
namespace use_cases {

class ICreatePlotDataAccess {
 public:
  struct PlotData {
    std::string &plot_id;
    const std::vector<double> &x;
    const std::vector<double> &y;
    const std::string &color;
    const std::string &makerstyle;
  };

  struct ViewPortData {
    double left;
    double bottom;
    double width;
    double height;
  };

  virtual unsigned GetPlotCount(const std::string &axes_id) = 0;
  virtual ViewPortData GetViewPort(const std::string &axes_id) = 0;
  virtual void UpdateViewPort(const std::string &axes_id, const ViewPortData &viewport) = 0;
  virtual void AddPlotToAxes(const std::string &axes_id, const PlotData &data,
                             const std::string &label) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
