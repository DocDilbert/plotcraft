#pragma once

#include <memory>
#include <string>
#include <vector>

namespace plotcraft {
namespace use_cases {

class ISetAxesPropertiesDataAccess {
 public:
  virtual void SetHorizontalViewport(const std::string& axes_id, double left, double width) = 0;
  virtual void SetVerticalViewport(const std::string& axes_id, double bottom, double height) = 0;
  virtual void SetXLabel(const std::string& axes_id, const std::string& text) = 0;
  virtual void SetYLabel(const std::string& axes_id, const std::string& text) = 0;
  virtual void SetTitle(const std::string& axes_id, const std::string& text) = 0;
  virtual void SetLegendEnable(const std::string& axes_id, bool enable) = 0;
  virtual void SetLegendLabels(const std::string& axes_id,
                               const std::vector<std::string>& entries) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
