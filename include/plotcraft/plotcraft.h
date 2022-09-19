#pragma once

#include <map>
#include <memory>
#include <vector>

#include "plotcraft/gateway/i_measure.h"
#include "plotcraft/platforms/wxwidgets/wx_plotcraft_panel.h"
#include "plotcraft/presenter/i_draw_primitives.h"

/// \brief namespace of plotcraft library
namespace plotcraft {

// wxWidgets convenience type
using wxPlotCraftPanel = platform::wxwidgets::wxPlotCraftPanel;

class PlotCraft {
 private:
  typedef std::map<std::string, std::string> Options;

 public:
  PlotCraft();
  virtual ~PlotCraft();

  void Figure();
  void Plot(const std::vector<double>& x, const std::vector<double>& y, const Options options = {});
  void Draw(plotcraft::presenter::IDrawPrimitives& draw_primitives,
            plotcraft::gateway::IMeasure& measure, int left, int bottom, int width, int height);
  void Xlim(double left, double right);
  void Ylim(double bottom, double top);
  void XLabel(const std::string text);
  void YLabel(const std::string text);
  void Title(const std::string text);
  void Legend();
  void Legend(const std::vector<std::string> labels, const Options options = {});
  void SaveFig(const std::string& filename);

 private:
  struct PlotCraftImpl;
  std::unique_ptr<PlotCraftImpl> pimpl_;

  std::string figure_id_;
  std::string axes_id_;
};

}  // namespace plotcraft
