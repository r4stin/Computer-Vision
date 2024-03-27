#include "header.h"
#include "functions.h"
#include "ImageFilters.h"


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
//    ShowImage(image, "Display window");
    // Convert the image to grayscale
    cv::Mat gray = C_gray(image);
//    ShowImage(gray, "Gray window");
//    cv::imwrite("Garden_grayscale.jpg", gray);

    // Get the kernel size from the command line
    int kernel_size = atoi(argv[2]);


    cv::Mat median;
    // Apply the median filter
    medianFilter(gray, median, kernel_size);


    // Show the results
    ShowImage(image, "Source window");
    ShowImage(median, "Output window  "+ std::to_string(kernel_size)+"x"+ std::to_string(kernel_size));


    cv::waitKey(0);



    return 0;
}
