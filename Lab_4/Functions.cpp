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

cv::Mat Sobel_gy(const cv::Mat img)
{
    cv::Mat grad_y, abs_grad_y, blur;
    int scale = 1;
    int delta = 0.0;
    int ddepth = CV_16S;
    GaussianBlur(img, blur, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);

    Sobel( blur, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    return abs_grad_y;
}

cv::Mat cannyEdge(cv::Mat img)
{   cv::Mat canny;

    Canny(img, canny, 100, 400, 3);
    return canny;
}

cv::Mat WhiteThreshod(cv::Mat img)
{
    cv::Mat whiteMask;
    cv::threshold(img, whiteMask, 240, 255, cv::THRESH_BINARY);
    return whiteMask;
}

cv::Mat dilation(const cv::Mat img)
{
    cv::Mat dilated;
    dilate(img, dilated, cv::Mat(), cv::Point(-1, -1), 2);
    return dilated;
}

cv::Mat detectMarkings(const cv::Mat img)
{
    cv::Mat gray = bgr2gray(img);
    // Apply Sobel operator in the y direction
    cv::Mat abs_grad_y = Sobel_gy(gray);
    // Apply Canny edge detection
    cv::Mat edges = cannyEdge(gray);
    // Combine the results of Sobel and Canny
    cv::Mat sobel_canny = abs_grad_y & edges;
    // Apply white thresholding
    cv::Mat whiteMask = WhiteThreshod(gray);
    // Apply dilation to the white mask
    whiteMask = dilation(whiteMask);
    // Combine edge information and white mask
    cv::Mat detectedMarkings = sobel_canny & whiteMask;
    // Remove small connected components
    detectedMarkings = removePixel(detectedMarkings, 100);
    // Show the detected markings mask
    ShowImage(detectedMarkings, "Detected Markings Mask");
    cv::Mat overlay;
    img.copyTo(overlay);
    overlay.setTo(cv::Scalar(0, 0, 255), detectedMarkings);
    return overlay;
}
