#pragma once

#include "plotcraft/plotcraft.h"

class IExample {
 public:
  virtual ~IExample(){};
  virtual plotcraft::PlotCraft& GetPlotcraftRef() = 0;
};
