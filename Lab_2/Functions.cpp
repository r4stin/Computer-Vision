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

// Function to convert the image to grayscale
cv::Mat C_gray(cv::Mat &image) {
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    return gray;
}

// Function responsible to plot the histogram
void histogram_plot(const cv::Mat& imgGray, int histSize){
    std::vector<cv::Mat> image;
    cv::split( imgGray, image );
    float range[] = { 0, 256 };
    const float* histRange[] = { range };
    bool uniform = true, accumulate = false;
    cv::Mat b_hist, g_hist, r_hist;
    cv::calcHist( &image[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate );
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

    cv::normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
              cv::Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
              cv::Scalar( 0, 0, 255), 2, 8, 0  );

    }
    cv::imshow("Histogram", histImage);

}

// Histogram equalization function
cv::Mat histogram_equalization(const cv::Mat& imgGray) {
    cv::Mat imgEqualized;
    cv::equalizeHist(imgGray, imgEqualized);
    return imgEqualized;
}