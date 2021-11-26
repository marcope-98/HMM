#include "../include/libspeech/sigproc.hpp"

namespace sigproc
{

    unsigned int bitReverse(unsigned int x, const int &log2n)
    {
        int n = 0;
        int mask = 0x1;
        for (int i = 0; i < log2n; i++)
        {
            n <<= 1;
            n |= (x & 1);
            x >>= 1;
        }
        return n;
    }

    std::vector<double> framesig()
    {
        return {0};
    }

    std::vector<double> magspec()
    {
        return {0};
    }

    std::vector<double> powspec()
    {
        return {0};
    }

    std::vector<double> logpowspec()
    {
        return {0};
    }

    std::vector<double> preemphasis()
    {
        return {0};
    }

    template <class Iter_T>
    void fft(Iter_T a, Iter_T b, const int &log2n)
    {
        typedef typename std::iterator_traits<Iter_T>::value_type complex;
        const complex J(0, 1);
        int n = 1 << log2n;
        for (unsigned int i = 0; i < n; ++i)
        {
            b[bitReverse(i, log2n)] = a[i];
        }
        for (int s = 1; s <= log2n; ++s)
        {
            int m = 1 << s;
            int m2 = m >> 1;
            complex w(1, 0);
            complex wm = exp(-J * (M_PI / m2));
            for (int j = 0; j < m2; ++j)
            {
                for (int k = j; k < n; k += m)
                {
                    complex t = w * b[k + m2];
                    complex u = b[k];
                    b[k] = u + t;
                    b[k + m2] = u - t;
                }
                w *= wm;
            }
        }
    }

}