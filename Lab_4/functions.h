#ifndef LAB_4_24_FUNCTIONS_H
#define LAB_4_24_FUNCTIONS_H
#include "header.h"
void ShowImage(const cv::Mat &image, const std::string &windowName);
cv::Mat bgr2gray(const cv::Mat& image);
cv::Mat detectMarkings(const cv::Mat img);
cv::Mat detectCircle(cv::Mat img);
cv::Mat Task2_LaneDetection(const cv::Mat img);

#endif //LAB_4_24_FUNCTIONS_H