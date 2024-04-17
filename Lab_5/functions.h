#ifndef LAB_5_24_FUNCTIONS_H
#define LAB_5_24_FUNCTIONS_H
#include "header.h"
void ShowImage(const cv::Mat &image, const std::string &windowName);
cv::Mat bgr2gray(const cv::Mat& image);
cv::Mat detectMarkings(const cv::Mat img);
cv::Mat detectCircle(cv::Mat img);
cv::Mat Task2_LaneDetection(const cv::Mat img);
cv::Mat Sobel_gy(const cv::Mat img);
cv::Mat cannyEdge(cv::Mat img, int lowThreshold, int highThreshold, int kernel_size);
cv::Mat WhiteThreshod(cv::Mat img);
cv::Mat removePixel(cv::Mat imgCanny, int rmp);
cv::Mat addPixel(cv::Mat imgCanny, int rmp);
cv::Mat task1App1(const cv::Mat img);
cv::Mat KMeans(const cv::Mat src, int K);
cv::Mat task2App1(cv::Mat img);
cv::Mat Task3Segmentation(cv::Mat img);







#endif //LAB_5_24_FUNCTIONS_H