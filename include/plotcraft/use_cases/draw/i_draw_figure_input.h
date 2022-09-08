#pragma once

#include <string>

namespace plotcraft {
namespace use_cases {

struct DrawFigureRequest {
   const std::string& figure_id;

   double screen_left;
   double screen_bottom;
   double screen_width;
   double screen_height;
};

class IDrawFigureInput {
  public:
   virtual void Draw(DrawFigureRequest request) = 0;
};

}  // namespace use_cases
}  // namespace plotcraft
