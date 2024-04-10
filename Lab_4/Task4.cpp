#include "header.h"
#include "functions.h"


int main(int argc, char** argv ) {

    if (argc < 2) {
        std::cout << "Image filename shall be provided!" << std::endl;
        return -1;

    }
    // Load the image
    cv::Mat image =  imread(argv[1], cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Error: Unable to load image!" << std::endl;
        return -1;
    }

    // Detect road sign
    cv::Mat result = detectCircle(image);
    ShowImage(result, "Detected Circles");
    cv::waitKey();
    return 0;
}