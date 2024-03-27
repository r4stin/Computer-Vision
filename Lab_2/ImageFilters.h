#ifndef LAB_2_24_IMAGEFILTERS_H
#define LAB_2_24_IMAGEFILTERS_H
#include "header.h"

//cv::Mat Dilate_max(cv::Mat imgGray, int kernel);
//cv::Mat Erode_min(cv::Mat imgGray, int kernel);
//cv::Mat Median_filter(cv::Mat imgGray, int kernel);
cv::Mat maxFilter(const cv::Mat& input, cv::Mat& output,int kernelSize);
cv::Mat minFilter(const cv::Mat& input, cv::Mat& output, int kernelSize);
cv::Mat medianFilter(const cv::Mat& input, cv::Mat& output, int kernelSize);
cv::Mat Gaussian_Filter(const cv::Mat& input, cv::Mat& output, int kernelSize);


#endif // LAB_2_24_IMAGEFILTERS_H