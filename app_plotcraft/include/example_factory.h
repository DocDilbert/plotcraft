#pragma once
#include <spdlog/spdlog.h>

#include <memory>

#include "i_example.h"
#include "i_example_factory.h"

template <typename... Args>
class ExampleFactory : public IExampleFactory {
 private:
  template <typename... ARGS>
  class FactoryTemplate;

  template <typename T, typename... ARGS>
  class FactoryTemplate<T, ARGS...> {
   public:
    static constexpr int Count() { return 1 + FactoryTemplate<ARGS...>::Count(); }
    static std::shared_ptr<IExample> CreateReverse(int idx) {
      if (Count() - 1 == idx) {
        return std::make_shared<T>();
      } else {
        return FactoryTemplate<ARGS...>::CreateReverse(idx);
      }
    }
    static std::string GetTitleReverse(int idx) {
      if (Count() - 1 == idx) {
        return T::GetTitle();
      } else {
        return FactoryTemplate<ARGS...>::GetTitleReverse(idx);
      }
    }
  };

  template <typename T>
  class FactoryTemplate<T> {
   public:
    static constexpr int Count() { return 1; }
    static std::shared_ptr<IExample> CreateReverse(int idx) {
      if (Count() - 1 == idx) {
        return std::make_shared<T>();
      } else {
        return nullptr;
      }
    }

    static std::string GetTitleReverse(int idx) {
      if (Count() - 1 == idx) {
        return T::GetTitle();
      } else {
        return "";
      }
    }
  };

 public:
  int Count() override {
    auto cnt = FactoryTemplate<Args...>::Count();
    return cnt;
  }

  std::shared_ptr<IExample> Create(int idx) override {
    return FactoryTemplate<Args...>::CreateReverse(Count() - idx - 1);
  };

  std::string GetTitle(int idx) override {
    return FactoryTemplate<Args...>::GetTitleReverse(Count() - idx - 1);
  }
};
