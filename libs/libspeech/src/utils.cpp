#include "../include/libspeech/utils.hpp"

constexpr double sinc(const double &t)
{
  if (std::abs(t) < 0.002)
  {
    return 1. - ((pow(t, 2.)) / 6.) * (1. - pow(t, 2.) / 20.);
  }
  return sin(t) / t;
}

int nextpow2(const int &t)
{
  int temp = std::ceil(log(t)/log(2));
  return pow(2, temp);
}
