#ifndef LIBSPEECH_SIGPROC_HPP
#define LIBSPEECH_SIGPROC_HPP
#include <vector>
#include <complex>
#include <cmath>
#include <iterator>

#define _USE_MATH_DEFINES
namespace sigproc
{
    std::vector<double> framesig();
    std::vector<double> magspec();
    std::vector<double> powspec();
    std::vector<double> logpowspec();
    std::vector<double> preemphasis();
    unsigned int bitReverse(unsigned int x, const int& log2n);
    template<class Iter_T> 
    void fft(Iter_T a, Iter_T b, const int &log2n); 
}

#endif