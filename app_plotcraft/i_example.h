#pragma once

#include "plotcraft/plotcraft.h"

class IExample {
 public:
  virtual ~IExample(){};
  virtual std::string GetTitle() = 0;
  virtual void Execute() = 0;
  virtual plotcraft::PlotCraft& GetPlotcraftRef() = 0;
};
