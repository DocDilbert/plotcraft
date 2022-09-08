#pragma once
#include <spdlog/spdlog.h>

#include <cmath>
#include <vector>

namespace plotcraft {
namespace entities {

class Locators {
   public:
};

class LinearLocator {
   public:
    LinearLocator(unsigned num_ticks) : num_ticks_(num_ticks) {}

    std::vector<double> GetTickValues(double vmin, double vmax) {
        std::vector<double> ret;
        for (unsigned i = 0; i < num_ticks_; i++) {
            double val = (vmax - vmin) * static_cast<double>(i) /
                             static_cast<double>(num_ticks_ - 1) +
                         vmin;
            ret.push_back(val);
        }
        return ret;
    }

   private:
    unsigned num_ticks_;
};

class MaxNLocator {
   public:
    MaxNLocator(unsigned max_n) : max_n_(max_n) {}

    std::vector<double> GetTickValues(double vmin, double vmax) {
        const std::vector<double> nice_values = {10.0, 5.0, 2.5, 2.0, 1.0};
        std::vector<double> ret;
        double raw_steps = (vmax - vmin) / max_n_;

        for (auto it : nice_values) {
            // This equation rounds the log10 to the smaller number ...
            // The real step is between this value and this value multiplied by
            // 10
            double step =
                pow(10.0, static_cast<int>(std::floor(std::log10(raw_steps)))) *
                it;

            int lower_limit = static_cast<int>(vmin / step);
            int upper_limit = static_cast<int>(vmax / step);
            // spdlog::info("ll={} ul={}", lower_limit, upper_limit);
            ret.clear();

            for (int s = lower_limit; s <= upper_limit; s++) {
                double val = static_cast<double>(s) * step;
                ret.push_back(val);
            }
            if (ret.size() >= min_n_) {
                break;
            }
        }
        return ret;
    }

   private:
    unsigned max_n_;
    unsigned min_n_ = {4};
};
}  // namespace entities
}  // namespace plotcraft
