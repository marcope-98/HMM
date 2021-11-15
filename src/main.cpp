#include <iostream>
#include "libspeech/AudioFile.hpp"
//#include "TCanvas.h"
#include "TApplication.h"

int main(int argc, char** argv)
{
    AudioFile a("../data/male.wav");
    a.printsummary();
    //    cv::Mat image(720, 1024, CV_8UC3, cv::Scalar(255, 255, 255));
    //    a.plot(&image);
    //    cv::imshow("output", image);
    //    cv::waitKey(0);
    //    cv::destroyAllWindows();
    TApplication app("ROOT Application", &argc, argv);
    a.ROOT_plot();
    app.Run();
    return 0;
}
