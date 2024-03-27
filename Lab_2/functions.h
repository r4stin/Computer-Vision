#ifndef LAB_2_24_FUNCTIONS_H
#define LAB_2_24_FUNCTIONS_H
#include "header.h"

cv::Mat ReadImage(const std::string &filename);
void ShowImage(const cv::Mat &image, const std::string &windowName);
cv::Mat C_gray(cv::Mat &image);
void histogram_plot(const cv::Mat& imgGray, int histSize);
cv::Mat histogram_equalization(const cv::Mat& imgGray);
#endif //LAB_2_24_FUNCTIONS_H
