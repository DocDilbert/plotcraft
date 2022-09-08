#pragma once

#include <string>

namespace plotcraft {
namespace use_cases {

struct CreateFigAndAxesResponse {
   std::string figure_id;  ///< Id of created figure
   std::string axes_id;    ///< Id of created axes
};

class ICreateFigAndAxesOutput {
  public:
   virtual void IsCreated(CreateFigAndAxesResponse response) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
