#pragma once

#include <cmath>
#include <random>

namespace math {

inline double RandomDouble(double min, double max)
{
   static std::uniform_real_distribution<double> distribution(min, max);
   static std::mt19937 generator;
   return distribution(generator);
}

inline double RandomDouble()
{
   return RandomDouble(0.0, 1.0);
}

inline constexpr double DegreesToRadians(double degrees)
{
   return degrees * M_PI / 180;
}

inline constexpr double RadiansToDegrees(double radians)
{
   return radians * 180 / M_PI;
}

}   // namespace math