#ifndef LIBSPEECH_AUDIOFILE_HPP
#define LIBSPEECH_AUDIOFILE_HPP
#include <cstdint>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <opencv2/core.hpp> // cv::*
#include <opencv2/imgproc.hpp> // image manipulation
#include <opencv2/highgui.hpp>

struct RIFF
{
    std::string chunkID = "xxxx";
    uint32_t chunkSize;
    std::string format = "xxxx";
};

struct FMT
{
    std::string subchunk1ID = "xxxx";
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
};

struct DATA
{
    std::string subchunk2ID = "xxxx";
    uint32_t subchunk2Size;
    std::vector<int16_t> channel1;
};


class AudioFile
{
private:
    std::string m_filename;
    RIFF        m_RiffSubChunk;
    FMT         m_FmtSubChunk;
    DATA        m_DataSubChunk;

public:
    explicit AudioFile(const std::string &);
    void printsummary();
    void plot(cv::Mat*);
};

#endif