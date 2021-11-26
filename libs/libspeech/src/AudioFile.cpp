#include "../include/libspeech/AudioFile.hpp"

AudioFile::AudioFile(const std::string &filename)
{
    m_filename = filename;
    std::ifstream wavfile(filename, std::ios::in | std::ios::binary);
    wavfile.read(reinterpret_cast<char *>(&m_RiffSubChunk), 12);
    wavfile.read(reinterpret_cast<char *>(&m_FmtSubChunk), 24);
    wavfile.read(reinterpret_cast<char *>(&m_DataSubChunk), 8);

    char c[2];
    m_DataSubChunk.channel1.reserve(m_DataSubChunk.subchunk2Size);
    while (wavfile.read((char *)c, 2))
    {
        m_DataSubChunk.channel1.emplace_back(*(int16_t *)c);
    }
    wavfile.close();
}

void AudioFile::print(const std::array<char, 4> &arr)
{
    std::for_each(arr.begin(), arr.end(), [](const char &i)
                  { std::cout << i; });
    std::cout << "\n";
}

void AudioFile::printsummary()
{
    std::cout << "RIFF ChunkID: ";
    print(m_RiffSubChunk.chunkID);
    std::cout << "RIFF ChunkSize: " << m_RiffSubChunk.chunkSize << "\n";
    std::cout << "RIFF format: ";
    print(m_RiffSubChunk.format);
    std::cout << "\n";
    std::cout << "FMT ChunkID: ";
    print(m_FmtSubChunk.subchunk1ID);
    std::cout << "FMT ChunkSize: " << m_FmtSubChunk.subchunk1Size << "\n";
    std::cout << "FMT AudioFormat: " << m_FmtSubChunk.audioFormat << "\n";
    std::cout << "FMT numChannels: " << m_FmtSubChunk.numChannels << "\n";
    std::cout << "FMT sampleRate: " << m_FmtSubChunk.sampleRate << "\n";
    std::cout << "FMT byteRate: " << m_FmtSubChunk.byteRate << "\n";
    std::cout << "FMT blockAlign: " << m_FmtSubChunk.blockAlign << "\n";
    std::cout << "FMT bitsPerSample: " << m_FmtSubChunk.bitsPerSample << "\n";
    std::cout << "\n";
    std::cout << "DATA ChunkID: ";
    print(m_DataSubChunk.subchunk2ID);
    std::cout << "DATA ChunkSize: " << m_DataSubChunk.subchunk2Size << "\n";
}

void AudioFile::plot(cv::Mat *image)
{
    const double increment = 1 / double(m_FmtSubChunk.sampleRate);
    const double duration = m_DataSubChunk.subchunk2Size * increment / 2.;
    const int x = (*image).rows; // 720
    const int y = (*image).cols; // 1024
    const double scale = y / duration;
    std::vector<cv::Point> imagePoints;
    const int elem_max = *std::max_element(m_DataSubChunk.channel1.begin(), m_DataSubChunk.channel1.end());
    std::for_each(m_DataSubChunk.channel1.begin(), m_DataSubChunk.channel1.end(),
                  [i = 0., &increment, &elem_max, &x, &imagePoints, &scale](const int16_t &p) mutable
                  {
                      imagePoints.emplace_back(cv::Point(i * scale, p * 0.5 * x / elem_max + 0.5 * x));
                      i += increment;
                  });

    cv::polylines(*image, imagePoints, false, cv::Scalar(255, 0, 0, 0.0), 1, 8, 0);
    cv::flip(*image, *image, 0);
}

void AudioFile::ROOT_plot()
{
    const double increment = 1 / double(m_FmtSubChunk.sampleRate);
    std::vector<double> d_channel1;
    std::vector<double> time(m_DataSubChunk.channel1.size());
/*
    std::for_each(m_DataSubChunk.channel1.begin(), m_DataSubChunk.channel1.end(),
                  [&](const int16_t &t)
                  { d_channel1.emplace_back(double(t)); });
                  */
    std::generate(time.begin(), time.end(),
                  [&increment, n = -increment]() mutable
                  { return n += increment; });
    TGraph graph(Int_t(time.size()), &(time[0]), &(m_DataSubChunk.channel1[0]));

    graph.DrawClone("APE");
}
