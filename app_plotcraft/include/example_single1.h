#pragma once

#include "i_example.h"
#include "plotcraft/plotcraft.h"
#include "simplex_noise.h"

class ExampleSingle1 : public IExample {
 public:
  static std::string GetTitle() { return "ExampleSingle1"; }

  ExampleSingle1() {
    plot_craft_.Figure();

    std::vector<double> m_x;
    std::vector<double> m_y_1;

    const int steps = 50;
    auto simplex_noise = SimplexNoise();
    for (auto i = 0; i < steps; i++) {
      double x = static_cast<double>(i) / static_cast<double>(steps - 1) * 4.0;

      auto y1 = simplex_noise.fractal(1, x) + 1.0;
      m_x.push_back(x);
      m_y_1.push_back(y1);
    }
    plot_craft_.Plot(
        m_x, m_y_1, {{"label", "Simplex noise 1 octave"}, {"color", "blue"}, {"markerstyle", "x"}});
  }
  virtual ~ExampleSingle1(){};

  plotcraft::PlotCraft& GetPlotcraftRef() { return plot_craft_; }

 private:
  plotcraft::PlotCraft plot_craft_;
};
