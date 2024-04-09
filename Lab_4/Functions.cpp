#include "header.h"
#include "functions.h"
// Function to read the image
cv::Mat ReadImage(const std::string &filename) {
    cv::Mat image = imread(filename, cv::IMREAD_COLOR);
    return image;

}
// Function to display the image
void ShowImage(const cv::Mat &image, const std::string& windowName) {
    cv::imshow(windowName, image);
}

cv::Mat bgr2gray(const cv::Mat& image) {
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    return grayImage;
}
