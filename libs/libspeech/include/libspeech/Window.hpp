#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <array>
#include "utils.hpp"
//#include "TGraph.h"

#define _USE_MATH_DEFINES

enum FFT_WINDOW
{
    Barthann,        // implemented
    Bartlett,        // implemented
    Blackman,        // implemented
    Blackman_Harris, // implemented
    Bohman,          // implemented
    Cosine,          // implemented
    ExactBlackman,   // implemented
    Flattop,         // implemented
    Gaussian,        // implemented
    Hamming,         // implemented
    Hann,            // implemented
    Lanczos,         // implemented
    Nuttall,         // implemented
    Parzen,          // implemented
    Rectangular,     // implemented
    Triangular,      // implemented
    Tukey,           // implemented
    Welch            // implemented
};

class Window
{
private:
    FFT_WINDOW m_name;
    double m_amplitude;
    double m_energy;
    int m_length;
    std::vector<double> m_data;

public:
    Window(const FFT_WINDOW &, const int &, const double& = 0.);
    double amplitude_correction_factor();
    double energy_correction_factor();
    void select(const FFT_WINDOW &, const double&);
    std::vector<double> getdata() const { return m_data; }

    void barthann(std::vector<double> *, const double&);
    void bartlett(std::vector<double> *, const double&);
    void blackman(std::vector<double> *, const double&);
    void blackman_harris(std::vector<double> *, const double&);
    void bohman(std::vector<double> *, const double&);
    void cosine(std::vector<double> *, const double&);
    void exactblackman(std::vector<double> *, const double&);
    void flattop(std::vector<double> *, const double&);
    void gaussian(std::vector<double> *, const double& = 2.5);
    void hamming(std::vector<double> *, const double&);
    void hann(std::vector<double> *, const double&);
    void lanczos(std::vector<double> *, const double&);
    void nuttall(std::vector<double> *, const double&);
    void parzen(std::vector<double> *, const double&);
    void rectangular(std::vector<double> *, const double&);
    void triangular(std::vector<double> *, const double&);
    void tukey(std::vector<double> *, const double&);
    void welch(std::vector<double> *, const double&);

    void plot();
};


#endif