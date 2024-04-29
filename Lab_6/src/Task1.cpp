#include "../include/header.h"
#include "../include/functions.h"



int main(int argc, char** argv ) {
//
    if (argc < 2) {
        std::cout << "Image filename shall be provided!" << std::endl;
        return -1;

    }
    //Load the image
    cv::Mat image1 =  imread(argv[1], cv::IMREAD_GRAYSCALE);
    cv::Mat image2 =  imread(argv[2], cv::IMREAD_GRAYSCALE);
    // Check for invalid input
    if (image1.empty() && image2.empty()) {
        std::cerr << "Error: Unable to load images!" << std::endl;
        return -1;
    }

    orbDetector(image1, image2);
    std::cout << "--------------------------------" << std::endl;

    siftDetector(image1, image2);
    std::cout << "--------------------------------" << std::endl;

    surfDetector(image1, image2);
    std::cout << "--------------------------------" << std::endl;
    cv::waitKey(0);

    return 0;
}