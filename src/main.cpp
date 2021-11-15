#include <iostream>
#include "libspeech/AudioFile.hpp"

int main()
{
    AudioFile a("../data/male.wav");
    a.printsummary();
    cv::Mat image(720, 1024, CV_8UC3, cv::Scalar(255, 255, 255));
    a.plot(&image);
    cv::imshow("output", image);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
