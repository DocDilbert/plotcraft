#pragma once

#include "i_example.h"
#include "plotcraft/plotcraft.h"
#include "simplex_noise.h"

class ExampleSingle2 : public IExample {
 public:
  static std::string GetTitle() { return "ExampleSingle2"; }

  ExampleSingle2() {
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

    // plot_craft_.Xlim(-40, 0.0);
    // plot_craft_.Ylim(-1.3, 1.25);
    plot_craft_.YLabel("Amplitude");
    // plot_craft_.YLabel("XXX");
    plot_craft_.XLabel("x coordinate");
    plot_craft_.Title("Simplex noise");
    plot_craft_.Legend({"1 octave", "2 octaves", "4 octaves"});
  }
  virtual ~ExampleSingle2(){};

  plotcraft::PlotCraft& GetPlotcraftRef() { return plot_craft_; }

 private:
  plotcraft::PlotCraft plot_craft_;
};
