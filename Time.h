// https://www.learncpp.com/cpp-tutorial/timing-your-code/
#pragma once

#include <chrono>

class Time
{
public:
  void reset() { m_start = Clock::now(); };
  double elapsed() { return std::chrono::duration_cast<Second>(Clock::now() - m_start).count(); };
  double delta() { return std::chrono::duration_cast<Second>(Clock::now() - m_last).count(); };
  void update() { m_last = Clock::now(); };

private:
  using Clock = std::chrono::high_resolution_clock;
  using Second = std::chrono::duration<double, std::ratio<1>>;

  std::chrono::time_point<Clock> m_start { Clock::now() };
  std::chrono::time_point<Clock> m_last { Clock::now() };
};
