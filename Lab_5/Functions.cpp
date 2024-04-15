#include "header.h"
#include "functions.h"

// Function to display the image
void ShowImage(const cv::Mat &image, const std::string& windowName) {
    cv::imshow(windowName, image);
}

cv::Mat bgr2gray(const cv::Mat& image) {
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    return grayImage;
}



cv::Mat removePixel(cv::Mat imgCanny, int rmp)
{
    cv::Mat labels;
    int num_components = cv::connectedComponents(imgCanny, labels);

    int min_size = rmp;
    for (int i = 1; i < num_components; i++) {
        cv::Mat component_mask = (labels == i);
        int area = cv::countNonZero(component_mask);
        if (area < min_size) {
            imgCanny.setTo(0, component_mask);
        }
    }
    return imgCanny;
}


cv::Mat cannyEdge(cv::Mat img, int lowThreshold, int highThreshold, int kernel_size)
{   cv::Mat canny;
    Canny(img, canny, lowThreshold, highThreshold, kernel_size);
    return canny;
}


cv::Mat SmoothBlur(cv::Mat img, int kernel_size)
{
    cv::Mat blur;
    cv::blur(img, blur, cv::Size(kernel_size, kernel_size));
    return blur;
}

cv::Mat task1App1(const cv::Mat img)
{
    // Convert to grayscale
    cv::Mat Gray = bgr2gray(img);
    // Apply Blur for smoothing
    cv::Mat blur = SmoothBlur(Gray, 3);
    // Apply log transformation
    cv::Mat img_log;
    cv::intensity_transform::logTransform(blur, img_log);
    // Apply bilateral filter
    cv::Mat bilateral_img;
    cv::bilateralFilter(img_log, bilateral_img, 5, 75, 75);
    // Apply canny edge detection
    cv::Mat canny = cannyEdge(bilateral_img, 50, 150, 3);
    // Apply dilation
    dilate(canny, canny, cv::Mat());

    cv::Mat result;
    // Remove small group of pixels
    result = removePixel(canny, 210);

    return result;
}

cv::Mat task1App2(const cv::Mat src) {

    cv::Mat blur = SmoothBlur(src, 21);

    cv::Mat p = cv::Mat::zeros(blur.cols*blur.rows, 5, CV_32F);
    cv::Mat bestLabels, centers, clustered;
    std::vector<cv::Mat> bgr;
    cv::split(blur, bgr);

    for(int i=0; i<blur.cols*blur.rows; i++) {
        p.at<float>(i,0) = (i/blur.cols) / blur.rows;
        p.at<float>(i,1) = (i%blur.cols) / blur.cols;
        p.at<float>(i,2) = bgr[0].data[i] / 255.0;
        p.at<float>(i,3) = bgr[1].data[i] / 255.0;
        p.at<float>(i,4) = bgr[2].data[i] / 255.0;
    }


    int K = 2;
    cv::kmeans(p, K, bestLabels,
               cv::TermCriteria( cv::TermCriteria::EPS+cv::TermCriteria::COUNT, 10, 1.0),
               3, cv::KMEANS_PP_CENTERS, centers);

    int colors[K];
    for(int i=0; i<K; i++) {
        if (i == 0) {
            colors[i] = 150;
        } else {
            colors[i] = 200;
        }
    }
    clustered = cv::Mat(blur.rows, blur.cols, CV_32F);
    for(int i=0; i<blur.cols*blur.rows; i++) {
        clustered.at<float>(i/blur.cols, i%blur.cols) = (float)(colors[bestLabels.at<int>(0,i)]);
    }

    clustered.convertTo(clustered, CV_8U);
    return clustered;


}


