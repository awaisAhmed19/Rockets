#pragma once

#include "Core.h"
#include <chrono>

namespace Engine {

using Clock = std::chrono::steady_clock;
using TimePoint = Clock::time_point;

struct Timer {
  Timer() = default;

  void reset() { start = Clock::now(); }

  [[nodiscard]] f64 seconds() const {
    return std::chrono::duration<f64>(Clock::now() - start).count();
  }

  [[nodiscard]] f64 milliseconds() const {
    return std::chrono::duration<f64, std::milli>(Clock::now() - start).count();
  }

  [[nodiscard]] f64 microseconds() const {
    return std::chrono::duration<f64, std::micro>(Clock::now() - start).count();
  }

  [[nodiscard]] f64 nanoseconds() const {
    return std::chrono::duration<f64, std::nano>(Clock::now() - start).count();
  }

private:
  TimePoint start = Clock::now();
};

} // namespace Engine
