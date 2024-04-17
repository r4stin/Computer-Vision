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

cv::Mat removePixel(cv::Mat img, int rmp)
{
    cv::Mat labels;
    int num_components = cv::connectedComponents(img, labels);

    int min_size = rmp;
    for (int i = 1; i < num_components; i++) {
        cv::Mat component_mask = (labels == i);
        int area = cv::countNonZero(component_mask);
        if (area < min_size) {
            img.setTo(0, component_mask);
        }
    }
    return img;
}

cv::Mat addPixel(cv::Mat img, int addp) {
    cv::Mat inverted;
    cv::bitwise_not(img, inverted);
    cv::Mat labels;
    int num_components = cv::connectedComponents(inverted, labels);
    int min_size = addp;
    for (int i = 1; i < num_components; i++) {
        cv::Mat component_mask = (labels == i);
        int area = cv::countNonZero(component_mask);
        if (area < min_size) {
            img.setTo(255, component_mask); // Set pixels to 255 instead of 0
        }
    }
    return img;

}

cv::Mat cannyEdge(cv::Mat img, int lowThreshold, int highThreshold, int kernel_size)
{   cv::Mat canny;
    Canny(img, canny, lowThreshold, highThreshold, kernel_size);
    return canny;
}

cv::Mat medianFilter(cv::Mat img)
{
    cv::medianBlur(img, img, 5);
    return img;
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
    // Remove small group of pixels
    cv::Mat result = removePixel(canny, 210);

    return result;
}

cv::Mat KMeans(const cv::Mat src, int K) {

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

    cv::kmeans(p, K, bestLabels,
               cv::TermCriteria( cv::TermCriteria::EPS+cv::TermCriteria::COUNT, 10, 1.0),
               3, cv::KMEANS_PP_CENTERS, centers);

    int colors[K];
    for(int i=0; i<K; i++) {
        colors[i] = 255/(i+1);
    }
    clustered = cv::Mat(blur.rows, blur.cols, CV_32F);
    for(int i=0; i<blur.cols*blur.rows; i++) {
        clustered.at<float>(i/blur.cols, i%blur.cols) = (float)(colors[bestLabels.at<int>(0,i)]);
    }

    clustered.convertTo(clustered, CV_8U);
    return clustered;


}


cv::Mat task2App1(cv::Mat img)
{
    // Convert to hsv
    cv::Mat img_hsv;
    cv::cvtColor(img, img_hsv, cv::COLOR_BGR2HSV);
    // Apply median filter
    cv::Mat imgblur = medianFilter(img_hsv);
    // Define the color ranges
    cv::Scalar asphalt_lowerb(5, 5, 70);
    cv::Scalar asphalt_upperb(170, 41, 170);
    cv::Scalar sky_lowerb(90, 80, 215);
    cv::Scalar sky_upperb(115, 170, 255);
    // Create masks for asphalt and sky
    cv::Mat asphalt_mask, sky_mask, elseMask;
    cv::inRange(imgblur, asphalt_lowerb, asphalt_upperb, asphalt_mask);
    cv::inRange(imgblur, sky_lowerb, sky_upperb, sky_mask);
    // Create a segmented image
    cv::Mat segmented_img(img.size(), img.type(), cv::Scalar(0, 0, 0));
    // Copy the original image to the segmented image using the masks
    img.copyTo(segmented_img, asphalt_mask);
    img.copyTo(segmented_img, sky_mask);
    // Create a mask for the rest of the image
    cv::bitwise_not( asphalt_mask | sky_mask, elseMask);
    // Add a pixel to everything else category
    elseMask = addPixel(elseMask, 2000);
    // Set the rest of the image to black
    segmented_img.setTo(cv::Scalar(0, 0, 0), elseMask);

    return segmented_img;
}


cv::Mat Task3Segmentation(cv::Mat img)
{
    // Convert to hsv
    cv::Mat hsv_img;
    cv::cvtColor(img, hsv_img, cv::COLOR_BGR2HSV);
    // Define the color range
    cv::Scalar lower_range = cv::Scalar(15, 60, 60);
    cv::Scalar upper_range = cv::Scalar(22, 255, 255);
    // Create a mask
    cv::Mat mask;
    cv::inRange(hsv_img, lower_range, upper_range, mask);
    // Remove small groups of pixels
    removePixel(mask, 10);
    // Apply the mask to the original image
    cv::Mat segmented_img;
    cv::bitwise_and(img, img, segmented_img, mask);

    return segmented_img;
}

