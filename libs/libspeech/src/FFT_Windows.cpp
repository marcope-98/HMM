#include "../include/libspeech/FFT_Windows.hpp"
//later add samplerate for energy correction factor
Window::Window(const FFT_WINDOW &name, const int &samples)
{
    m_name = name;
    m_length = samples;
    select(m_name);
    m_amplitude = amplitude_correction_factor();
    m_energy = energy_correction_factor();
}

void Window::select(const FFT_WINDOW &name)
{
    switch (name)
    {
    case Barthann:
        barthann(&m_data);
        break;
    case Bartlett:
        bartlett(&m_data);
        break;
    case Blackman:
        blackman(&m_data);
        break;
    case Blackman_Harris:
        blackman_harris(&m_data);
        break;
    case Bohman:
        bohman(&m_data);
        break;
    case Chebyshev:
        chebyshev(&m_data);
        break;
    case Flattop:
        flattop(&m_data);
        break;
    case Gaussian:
        gaussian(&m_data);
        break;
    case Hamming:
        hamming(&m_data);
        break;
    case Hann:
        hann(&m_data);
        break;
    case Kaiser:
        kaiser(&m_data);
        break;
    case Nuttall:
        nuttall(&m_data);
        break;
    case Parzen:
        parzen(&m_data);
        break;
    case Rectangular:
        rectangular(&m_data);
        break;
    case Taylor:
        taylor(&m_data);
        break;
    case Triangular:
        triangular(&m_data);
        break;
    case Tukey:
        tukey(&m_data);
        break;
    };
}

void Window::barthann(std::vector<double> *result)
{
    (*result).resize(m_length);
    int N = m_length - 1;
    std::generate((*result).begin(), (*result).end(),
                  [n = -1., &N]() mutable
                  {
                      n++;
                      return 0.62 - 0.48 * (std::abs((n / N) - 0.5)) + 0.38 * cos(2 * M_PI * ((n / N) - 0.5));
                  });
}

void Window::bartlett(std::vector<double> *result)
{
    (*result).resize(m_length);
    int N = m_length - 1;
    double N_2 = double(N) / 2.;
    std::generate((*result).begin(), (*result).end(),
                  [n = -1., &N_2, &N]() mutable
                  {
                      n++;
                      if (n >= 0 && n <= N_2)
                          return n / N_2;
                      else if (n <= N && n >= N_2)
                          return 2 - (n / N_2);
                      else
                          return -1.;
                  });
}

void Window::blackman(std::vector<double> *result)
{
    double M = m_length % 2 == 0 ? double(m_length) / 2. : double(m_length + 1) / 2.;
    (*result).resize(M);
    double arg = 2 * M_PI / (double(m_length - 1));
    std::generate((*result).begin(), (*result).end(),
                  [&arg, n = -1.]() mutable
                  {
                      n++;
                      return 0.42 - 0.5 * cos(arg * n) + 0.08 * cos(2 * arg * n);
                  });
    (*result).insert((*result).end(), (*result).rbegin() + (m_length % 2), (*result).rend());
}

void Window::blackman_harris(std::vector<double> *result)
{
    (*result).resize(m_length);
    double arg = 2 * M_PI / double(m_length - 1);
    std::generate((*result).begin(), (*result).end(), [&arg, n = -1.]() mutable
                  {
                      n++;
                      return 0.35875 - 0.48829 * cos(n * arg) + 0.14128 * cos(2 * arg * n) - 0.01168 * cos(3 * arg * n);
                  });
    ;
}

void Window::bohman(std::vector<double> *result)
{
    (*result).resize(m_length);
    std::vector<double> x(m_length);
    double increment = 2. / double(m_length - 1);
    std::generate(x.begin(), x.end(), [n = -1. - increment, &increment]() mutable
                  {
                      n += increment;
                      return n;
                  });
    double arg = (1 / M_PI);
    std::transform(x.begin(), x.end(), (*result).begin(), [&arg](const double &t)
                   { return (1 - std::abs(t)) * cos(M_PI * std::abs(t)) + arg * sin(M_PI * std::abs(t)); });
    ;
}

// good luck implementing this
void Window::chebyshev(std::vector<double> *result)
{
}

void Window::flattop(std::vector<double> *result)
{
    (*result).resize(m_length);
    double arg = 2 * M_PI / (double(m_length)-1);
    std::generate((*result).begin(), (*result).end(), [n = -1., &arg]() mutable
                  {
                      n++;
                      return 0.21557895 - 0.41663158 * cos(arg * n) + 0.277263158 * cos(2 * arg * n) - 0.083578947 * cos(3 * arg * n) + 0.006947368 * cos(4 * arg * n);
                  });

    ;
}

// need to figure out how to pass alpha to this shit
void Window::gaussian(std::vector<double> *result)
{
}

void Window::hamming(std::vector<double> *result)
{

    (*result).resize(m_length);
    int N = m_length - 1;
    std::generate((*result).begin(), (*result).end(), [n = -1., &N]() mutable
                  {
                      n++;
                      return 0.54 - 0.46 * cos(2 * M_PI * n / N);
                  });
    ;
}

void Window::hann(std::vector<double> *result)
{
    (*result).resize(m_length);
    int N = m_length - 1;
    std::generate((*result).begin(), (*result).end(), [n = -1., &N]() mutable
                  {
                      n++;
                      return 0.5 * (1 - cos(2 * M_PI * n / N));
                  });
    ;
}

// need to think how to include shapefactor
void Window::kaiser(std::vector<double> *result)
{
}

// blackman-nuttall: TODO check if the denominator of arg should be N-1 or N
void Window::nuttall(std::vector<double> *result)
{
    (*result).resize(m_length);
    double arg = 2 * M_PI / double(m_length-1);
    std::generate((*result).begin(), (*result).end(), [n = -1., &arg]() mutable
                  {
                      n++;
                      return 0.3635819 - 0.4891775 * cos(arg * n) + 0.1365995 * cos(2 * arg * n) - 0.0106411 * cos(3 * arg * n);
                  });
    ;
}

void Window::parzen(std::vector<double> *result)
{
}

void Window::rectangular(std::vector<double> *result)
{
    (*result).resize(m_length);
    std::fill((*result).begin(), (*result).end(), 1.);
}

// need to think how to include cosine factor
void Window::taylor(std::vector<double> *result)
{
}

void Window::triangular(std::vector<double> *result)
{
    int size = (m_length + (m_length % 2)) / 2;
    (*result).resize(size);
    if (m_length % 2)
    {
        double arg = 2. / (double(m_length + 1));
        std::generate((*result).begin(), (*result).end(), [&arg, n = 0.]() mutable
                      {
                          n++;
                          return arg * n;
                      });
    }
    else
    {
        std::generate((*result).begin(), (*result).end(), [n = 0., this]() mutable
                      {
                          n++;
                          return ((2 * n) - 1) / m_length;
                      });
    }

    (*result).insert((*result).end(), (*result).rbegin() + (m_length % 2), (*result).rend());
}

void Window::tukey(std::vector<double> *result)
{
}

double Window::amplitude_correction_factor()
{
    return 2. / std::accumulate(m_data.begin(), m_data.end(), 0.);
}

double Window::energy_correction_factor()
{
    return 2. / std::inner_product(m_data.begin(), m_data.end(), m_data.begin(), 0.);
}

void Window::plot()
{
    std::cout << m_data.size() << std::endl;
    std::vector<double> x_axis(m_data.size());
    std::generate(x_axis.begin(), x_axis.end(), [n = 0]() mutable
                  { return ++n; });
    //TGraph graph(Int_t(m_data.size()), &x_axis[0], &m_data[0]);
    //graph.DrawClone("AL");
}