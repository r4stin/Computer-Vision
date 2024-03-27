#ifndef LAB_1_24_FUNCTIONS_H
#define LAB_1_24_FUNCTIONS_H
#include "header.h"

cv::Mat ReadImage(const std::string &filename);
void ShowImage(const cv::Mat &image, const std::string &windowName);
int NumChannels(const cv::Mat &image);
void WaiykeyChar(int key);
cv::Mat ChannelManipulation_Task3(cv::Mat &image, int channel);
void ChannelManipulation_Task4(cv::Mat &image);
cv::Mat CreateImage_task5(int width, int height);
cv::Mat VerticalGradient(cv::Mat &image);
cv::Mat HorizontalGradient(cv::Mat &image);
cv::Mat Chess20p(cv::Mat &image);
cv::Mat Chess50p(cv::Mat &image);
#endif //LAB_1_24_FUNCTIONS_H
