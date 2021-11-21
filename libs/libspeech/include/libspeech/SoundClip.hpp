#ifndef LIBSPEECH_SOUNDCLIP_HPP
#define LIBSPEECH_SOUNDCLIP_HPP
#include <string>
#include <vector>
#include <iostream>
#include "AudioFile.hpp"
#include "TCanvas.h"
#include "TGraph.h"

class SoundClip
{
private:
    std::string m_filename;
    int m_length;
    double m_samplerate;
    std::vector<double> m_time;
    std::vector<double> m_data;

public:
    explicit SoundClip(const std::string &);
    void print();
    void plot();
    void spectrogram(const double&, const double&, const int&);
};

#endif