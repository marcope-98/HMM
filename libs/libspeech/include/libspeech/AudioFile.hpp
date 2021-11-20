#ifndef LIBSPEECH_AUDIOFILE_HPP
#define LIBSPEECH_AUDIOFILE_HPP
#include <cstdint>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <opencv2/core.hpp>    // cv::*
#include <opencv2/imgproc.hpp> // image manipulation
#include <opencv2/highgui.hpp>
#include "TCanvas.h"
#include "TGraph.h"

struct RIFF
{
    std::array<char, 4> chunkID;
    uint32_t chunkSize;
    std::array<char, 4> format;
};

struct FMT
{
    std::array<char, 4> subchunk1ID;
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
    std::array<char, 4> subchunk2ID;
    uint32_t subchunk2Size;
    //std::vector<int16_t> channel1;
    std::vector<double> channel1;
};

class AudioFile
{
private:
    std::string m_filename;
    RIFF m_RiffSubChunk;
    FMT m_FmtSubChunk;
    DATA m_DataSubChunk;

public:
    RIFF getRiff() const { return m_RiffSubChunk; };
    FMT getFmt() const { return m_FmtSubChunk; };
    DATA getData() const { return m_DataSubChunk; };
    std::string getFilename() const { return m_filename; };

    explicit AudioFile(const std::string &);
    void printsummary();
    void plot(cv::Mat *);
    void print(const std::array<char, 4> &);
    void ROOT_plot();
};

#endif
