#include "../include/libspeech/utils.hpp"

double sinc(const double &t) {
  if (std::abs(t) < 0.002) {
    return 1. - ((pow(t, 2.)) / 6.) * (1. - pow(t, 2.) / 20.);
  }
  return sin(t) / t;
}
