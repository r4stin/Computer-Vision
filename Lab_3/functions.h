#ifndef LAB_3_24_FUNCTIONS_H
#define LAB_3_24_FUNCTIONS_H
#include "header.h"
#define NEIGHBORHOOD 9

cv::Mat ReadImage(const std::string &filename);
void ShowImage(const cv::Mat &image, const std::string &windowName);
void OnMouse(int event, int x, int y, int flags, void *userdata);
void OnMouse_Task3(int event, int x, int y, int flags, void *userdata);
void OnMouse_Task4(int event, int x, int y, int flags, void *userdata);
void Mask(cv::Mat Image, cv::Scalar mean, int T);
void OnMouse_Task5(int event, int x, int y, int flags, void *userdata);
cv::Mat Mask_Task6(cv::Mat Image, cv::Scalar mean);
void OnMouse_Task6(int event, int x, int y, int flags, void *userdata);
#endif //LAB_3_24_FUNCTIONS_H
