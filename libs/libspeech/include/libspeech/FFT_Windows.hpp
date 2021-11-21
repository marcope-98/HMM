#ifndef FFT_WINDOWS_HPP
#define FFT_WINDOWS_HPP
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
//#include "TGraph.h"
#define _USE_MATH_DEFINES
enum FFT_WINDOW
{
    Barthann,
    Bartlett,
    Blackman,
    Blackman_Harris,
    Bohman,
    Chebyshev,
    Flattop,
    Gaussian,
    Hamming,
    Hann,
    Kaiser,
    Nuttall,
    Parzen,
    Rectangular,
    Taylor,
    Triangular,
    Tukey
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
    Window(const FFT_WINDOW&, const int&);
    double amplitude_correction_factor();
    double energy_correction_factor();
    void select(const FFT_WINDOW&);
    std::vector<double> getdata() const {return m_data;}

    void barthann(std::vector<double>*);
    void bartlett(std::vector<double>*);
    void blackman(std::vector<double>*);
    void blackman_harris(std::vector<double>*);
    void bohman(std::vector<double>*);
    void chebyshev(std::vector<double>*);
    void flattop(std::vector<double>*);
    void gaussian(std::vector<double>*);
    void hamming(std::vector<double>*);
    void hann(std::vector<double>*);
    void kaiser(std::vector<double>*);
    void nuttall(std::vector<double>*);
    void parzen(std::vector<double>*);
    void rectangular(std::vector<double>*);
    void taylor(std::vector<double>*);
    void triangular(std::vector<double>*);
    void tukey(std::vector<double>*);

    void plot();
    
};


#endif