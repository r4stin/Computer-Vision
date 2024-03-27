#include "header.h"
#include "functions.h"


int main(int argc, char** argv) {

    if (argc < 2) {
        std::cout << "Image filename shall be provided!" << std::endl;
        return -1;

    }
    // Read the image file
    cv::Mat image = ReadImage(argv[1]);

    if (image.empty()) {
        std::cout << "Could not open or find the image!" << std::endl;
        return -1;
    }
    ShowImage(image, "Display window");
    // Convert the image to grayscale
    cv::Mat gray = C_gray(image);
    ShowImage(gray, "Gray window");
    // Save the grayscale image
    cv::imwrite("Garden_grayscale.jpg", gray);

    cv::waitKey(0);



    return 0;
}
