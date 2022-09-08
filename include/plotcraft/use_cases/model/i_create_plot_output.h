#pragma once

#include <string>

namespace plotcraft {
namespace use_cases {

struct CreatePlotResponse {
   std::string plot_id;  ///< Id of created plot
};

class ICreatePlotOutput {
  public:
   virtual void IsPlotCreated(const CreatePlotResponse& response) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
