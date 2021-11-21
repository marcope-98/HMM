#include "../include/main.hpp"

int main(int argc, char **argv)
{ 
    Window test(Triangular, 64);
    
    //std::cout <<test.getdata()[16] << std::endl;
    /*
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
    */
   //Window testw;
   //std::vector<double> test = testw.rectangular(6);
   //std::for_each(test.begin(), test.end(), [](const double &t){std::cout << t <<"\n";});
/*
    SoundClip test("../data/male.wav");
    test.print();
    TApplication app("ROOT APPLICATION", &argc, argv);
    test.plot();
    app.Run();*/
    /*
    Window test(Hann, 64);
    
    TApplication app("ROOT APPLICATION", &argc, argv);
    test.plot();
    app.Run();*/
    return 0;
}


/*
TESTS FAILED:
BLACKMAN
BOHMAN
FLATTOP
NUTTALL
TRAINGULAR


*/