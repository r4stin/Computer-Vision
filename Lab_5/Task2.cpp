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

    cv::Mat app1 = task2App1(image);
    ShowImage(app1, "App1 Result");
    cv::Mat app2 = KMeans(image, 3);
    ShowImage(app2, "KMeans Result");


    // Wait for a key press
    cv::waitKey(0);
    return 0;
}


