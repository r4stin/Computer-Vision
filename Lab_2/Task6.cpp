#include "header.h"
#include "functions.h"


int main(int argc, char** argv) {

    if (argc < 2) {
        std::cout << "Image filename shall be provided!" << std::endl;
        return -1;

    }
    // Read the image
    cv::Mat image = ReadImage(argv[1]);

    if (image.empty()) {
        std::cout << "Could not open or find the image!" << std::endl;
        return -1;
    }


    ShowImage(image, "Source window");
    // Convert the image to grayscale
    cv::Mat gray = C_gray(image);
    // Receive bin size from the user
    int histSize = atoi(argv[2]);
    // Equalize the histogram
    cv::Mat equalized = histogram_equalization(gray);
    // Show the equalized image
    ShowImage(equalized, "Equalized window");
    // Plot the histogram
    histogram_plot(equalized, histSize);
    cv::waitKey(0);



    return 0;
}
