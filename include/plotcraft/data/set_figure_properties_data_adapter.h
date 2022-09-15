#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "plotcraft/data/axis.h"
#include "plotcraft/data/figure.h"
#include "plotcraft/data/repository.h"
#include "plotcraft/use_cases/model/i_set_figure_properties_data_access.h"

namespace plotcraft {
namespace data {

class SetFigurePropertiesDataAdapter : public use_cases::ISetFigurePropertiesDataAccess {
 public:
  SetFigurePropertiesDataAdapter(data::Repository& repo) : repo_(repo) {}

 private:
  data::Repository& repo_;
};

}  // namespace data
}  // namespace plotcraft
