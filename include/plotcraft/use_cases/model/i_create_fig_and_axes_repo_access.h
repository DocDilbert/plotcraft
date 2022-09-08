#pragma once

#include <memory>
#include <string>
#include <vector>

namespace plotcraft {
namespace use_cases {

class ICreateFigAndAxesRepoAccess {
 public:
  enum class Orientation { kVertical, kHorizontal };

  struct MarginData {
    double left;
    double top;
    double bottom;
    double right;
  };

  struct FigureData {
    std::string figure_id;
    MarginData margins;
    MarginData paddings;
  };

  struct AxisData {
    Orientation orientation;
  };

  struct AxesData {
    std::string axes_id;
    double viewport_left;
    double viewport_bottom;
    double viewport_width;
    double viewport_height;

    std::vector<AxisData> axis;
  };

  virtual void AddFigure(const FigureData& data) = 0;

  virtual void AddAxesToFigure(const std::string& figure_id, const AxesData& data) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
