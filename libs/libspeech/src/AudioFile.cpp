#include "../include/libspeech/AudioFile.hpp"
#include <gsl/span>
#include <cmath>
AudioFile::AudioFile(const std::string &filename)
{
    m_filename = filename;
    std::ifstream wavfile(filename, std::ios::binary);

    char temp[4];
    // RIFF subchunk
    wavfile.read((char *)temp, 4);
    std::move(std::begin(temp), std::end(temp), m_RiffSubChunk.chunkID.begin());

    wavfile.read((char *)temp, 4);
    m_RiffSubChunk.chunkSize = *(uint32_t *)temp;

    wavfile.read((char *)temp, 4);
    std::move(std::begin(temp), std::end(temp), m_RiffSubChunk.format.begin());

    // FMT subchunk
    wavfile.read((char *)temp, 4);
    std::move(std::begin(temp), std::end(temp), m_FmtSubChunk.subchunk1ID.begin());

    wavfile.read((char *)temp, 4);
    m_FmtSubChunk.subchunk1Size = *(uint32_t *)temp;

    wavfile.read((char *)temp, 2);
    m_FmtSubChunk.audioFormat = *(uint16_t *)temp;

    wavfile.read((char *)temp, 2);
    m_FmtSubChunk.numChannels = *(uint16_t *)temp;

    wavfile.read((char *)temp, 4);
    m_FmtSubChunk.sampleRate = *(uint32_t *)temp;

    wavfile.read((char *)temp, 4);
    m_FmtSubChunk.byteRate = *(uint32_t *)temp;

    wavfile.read((char *)temp, 2);
    m_FmtSubChunk.blockAlign = *(uint16_t *)temp;

    wavfile.read((char *)temp, 2);
    m_FmtSubChunk.bitsPerSample = *(uint16_t *)temp;

    // DATA subchunk
    wavfile.read((char *)temp, 4);
    std::move(std::begin(temp), std::end(temp), m_DataSubChunk.subchunk2ID.begin());

    wavfile.read((char *)temp, 4);
    m_DataSubChunk.subchunk2Size = *(uint32_t *)temp;
    char c[2];
    m_DataSubChunk.channel1.reserve(m_DataSubChunk.subchunk2Size);
    while (wavfile.read((char*)c,2))
    {
        m_DataSubChunk.channel1.emplace_back(*(uint16_t*) c);
    }

    wavfile.close();
}

void AudioFile::printsummary()
{
    std::cout << "RIFF ChunkID: " << m_RiffSubChunk.chunkID << "\n";
    std::cout << "RIFF ChunkSize: " << m_RiffSubChunk.chunkSize << "\n";
    std::cout << "RIFF format: " << m_RiffSubChunk.format << "\n";
    std::cout << "\n";
    std::cout << "FMT ChunkID: " << m_FmtSubChunk.subchunk1ID << "\n";
    std::cout << "FMT ChunkSize: " << m_FmtSubChunk.subchunk1Size << "\n";
    std::cout << "FMT AudioFormat: " << m_FmtSubChunk.audioFormat << "\n";
    std::cout << "FMT numChannels: " << m_FmtSubChunk.numChannels << "\n";
    std::cout << "FMT sampleRate: " << m_FmtSubChunk.sampleRate << "\n";
    std::cout << "FMT byteRate: " << m_FmtSubChunk.byteRate << "\n";
    std::cout << "FMT blockAlign: " << m_FmtSubChunk.blockAlign << "\n";
    std::cout << "FMT bitsPerSample: " << m_FmtSubChunk.bitsPerSample << "\n";
    std::cout << "\n";
    std::cout << "DATA ChunkID: " << m_DataSubChunk.subchunk2ID << "\n";
    std::cout << "DATA ChunkSize: " << m_DataSubChunk.subchunk2Size << "\n";
}

void AudioFile::plot(cv::Mat* image)
{
    double increment = 1/double(m_FmtSubChunk.sampleRate);
    std::vector<cv::Point> imagePoints;
    const int elem_max = *std::max_element(m_DataSubChunk.channel1.begin(), m_DataSubChunk.channel1.end());
    std::for_each(m_DataSubChunk.channel1.begin(), m_DataSubChunk.channel1.end(),
    [i = 0., &increment, &elem_max, &imagePoints](const int16_t& p) mutable
    {
        
        imagePoints.emplace_back(cv::Point(i*500,p*350/elem_max +360));
        i+=increment;
    });

    cv::polylines(*image, imagePoints, false, cv::Scalar(255, 0, 0, 0.0), 1, 8, 0);
    cv::flip(*image, *image, 0);
}