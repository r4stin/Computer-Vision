#ifndef LAB_4_24_FUNCTIONS_H
#define LAB_4_24_FUNCTIONS_H
#include "header.h"
cv::Mat ReadImage(const std::string &filename);
void ShowImage(const cv::Mat &image, const std::string &windowName);
cv::Mat bgr2gray(const cv::Mat& image);

#endif //LAB_4_24_FUNCTIONS_H
