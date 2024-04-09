#include "header.h"
#include "functions.h"



int main() {
    // Load the image
    cv::Mat image = cv::imread("street_scene.png");
    if (image.empty()) {
        std::cerr << "Error: Unable to load image!" << std::endl;
        return -1;
    }

    // Detect the markings
    cv::Mat overlay = detectMarkings(image);
    // Show the result
    ShowImage(overlay, "Edges on Original Image");

    // Wait for a key press
    cv::waitKey(0);
    return 0;
}
