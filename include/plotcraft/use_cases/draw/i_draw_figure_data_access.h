#pragma once

#include <string>
#include <vector>

namespace plotcraft {
namespace use_cases {

class IDrawFigureDataAccesss {
 public:
  struct MarginData {
    double left;
    double top;
    double bottom;
    double right;
  };

  enum class Orientation { kVertical, kHorizontal };

  struct AxisData {
    Orientation orientation;
  };

  struct Plot2dData {
    const std::vector<double>& x;
    const std::vector<double>& y;
    const std::string& label;
    const std::string& color;
    const std::string& markerstyle;
  };

  struct AxesData {
    double viewport_left;
    double viewport_bottom;
    double viewport_width;
    double viewport_height;
    std::vector<AxisData> axis;
    std::vector<Plot2dData> plots;
    std::string xlabel;
    std::string ylabel;
    std::string title;
    bool legend_enable;
  };

  virtual std::vector<std::string> GetAxesIds(const std::string& figure_id) = 0;

  virtual MarginData GetMargins(const std::string& figure_id) = 0;
  virtual MarginData GetPaddings(const std::string& figure_id) = 0;
  virtual AxesData GetAxesData(const std::string& axes_id) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
