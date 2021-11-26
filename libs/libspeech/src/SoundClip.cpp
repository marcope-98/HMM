#include "../include/libspeech/SoundClip.hpp"

SoundClip::SoundClip(const std::string &filename)
{
    AudioFile a(filename);
    m_filename = a.getFilename();
    m_length = a.getData().subchunk2Size;
    m_samplerate = a.getFmt().sampleRate;

    double increment = 1 / m_samplerate;
    m_time.resize(int(m_length / 2));
    std::generate(m_time.begin(), m_time.end(),
                  [&increment, n = -increment]() mutable
                  { return n += increment; });
    m_data = a.getData().channel1;
}

void SoundClip::print()
{
    std::cout << m_filename << "\n";
    std::cout << m_length << "\n";
    std::cout << m_samplerate << "\n";
    //std::for_each(m_time.begin(),m_time.end(), [](const double& time){std::cout << time << " ";});
    //std::for_each(m_data.begin(),m_data.end(), [](const double& data){std::cout << data << " ";});
}

void SoundClip::plot()
{
    TGraph graph(Int_t(m_time.size()), &(m_time[0]), &(m_data[0]));
    graph.DrawClone("AICL");
}

void SoundClip::spectrogram(const double &wintime, const double &overlap, const int &nfft, const FFT_WINDOW &winfunc)
{
    Window window(winfunc, nfft);
    int winpts = std::ceil(wintime * m_samplerate);
    winpts += (winpts + 1) % 2;
    int steppts = std::ceil(overlap * wintime * m_samplerate);
    steppts += (steppts + 1) % 2;
    int real_nfft = nextpow2(winpts);
    std::vector<double> frames_w_window = sigproc::framesig(m_data, winpts, steppts, window);
}