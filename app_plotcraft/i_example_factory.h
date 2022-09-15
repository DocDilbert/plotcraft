#pragma once

#include <memory>

#include "i_example.h"
#include "i_example_factory.h"

class IExampleFactory {
 public:
  virtual ~IExampleFactory(){};

  virtual int Count() = 0;
  virtual std::string GetTitle(int idx) = 0;
  virtual std::shared_ptr<IExample> Create(int idx) = 0;
};
