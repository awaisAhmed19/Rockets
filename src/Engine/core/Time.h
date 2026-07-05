
#pragma once

#include "core.h"
#include <chrono>

namespace Engine {

using clock_t = std::chrono::steady_clock;
using time_point_t = clock_t::time_point;

struct timer {
  time_point_t start;
};

/* Initializes or resets the timer */
inline void timer_reset(timer *t) { t->start = clock_t::now(); }
/* Returns elapsed time in seconds */
inline f64 timer_seconds(const timer *t) {
  return std::chrono::duration<f64>(clock_t::now() - t->start).count();
}
/* Returns elapsed time in milliseconds */
inline f64 timer_milliseconds(const timer *t) {
  return std::chrono::duration<f64, std::milli>(clock_t::now() - t->start)
      .count();
}
/* Returns elapsed time in microseconds */
inline f64 timer_microseconds(const timer *t) {
  return std::chrono::duration<f64, std::micro>(clock_t::now() - t->start)
      .count();
}
/* Returns elapsed time in nanoseconds */
inline f64 timer_nanoseconds(const timer *t) {
  return std::chrono::duration<f64, std::nano>(clock_t::now() - t->start)
      .count();
}
} // namespace Engine
