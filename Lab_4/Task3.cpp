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
    // Detect the markings with hough transform
    cv::Mat result = Task2_LaneDetection(image);

    // Show the result
    ShowImage(result, "Lane Detection");
    // Wait for a key press
    cv::waitKey(0);
    return 0;
}
