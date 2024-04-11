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


cv::Mat Gaussian_Blur(cv::Mat img, int kernel_size)
{
    cv::Mat blur;
    cv::GaussianBlur(img, blur, cv::Size(kernel_size, kernel_size), 0, 0, cv::BORDER_DEFAULT);
    return blur;

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
    Sobel( img, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    return abs_grad_y;
}

cv::Mat cannyEdge(cv::Mat img, int lowThreshold, int highThreshold, int kernel_size)
{   cv::Mat canny;
    Canny(img, canny, lowThreshold, highThreshold, kernel_size);
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
    // Apply Gaussian blur
    cv::Mat blur = Gaussian_Blur(gray, 3);
    // Apply Sobel operator in the y direction
    cv::Mat abs_grad_y = Sobel_gy(blur);
    // Apply Canny edge detection
    cv::Mat edges = cannyEdge(gray, 100, 400, 3);
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
cv::Mat medianFilter(cv::Mat img)
{
    cv::medianBlur(img, img, 5);
    return img;
}

cv::Mat detectCircle(cv::Mat img){
    // Convert the image to grayscale
    cv::Mat gray = bgr2gray(img);
    // Apply median filter
    cv::Mat blur = medianFilter(gray);
    // Apply Hough Circle Transform
    std::vector<cv::Vec3f> circles;
    HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1,
                 20,
                 300, 20, 1, 30
    );

    std::cout << "Number of circles detected: " << circles.size() << std::endl;
    // Draw the circles
    for( size_t i = 0; i < circles.size(); i++ )
    {
        cv::Vec3i c = circles[i];
        cv::Point center = cv::Point(c[0], c[1]);
// circle center
        circle( img, center, 1, cv::Scalar(0,255,255), 4, cv::LINE_AA);
// circle outline
        int radius = c[2];
        circle( img, center, radius, cv::Scalar(0,255,255), 3, cv::LINE_AA);
    }

    return img;
}

// Sort in descending order of rho
bool compareByRho(const cv::Vec3f &a, const cv::Vec3f &b) {
    return a[0] > b[0];
}

cv::Mat SmoothBlur(cv::Mat img, int kernel_size)
{
    cv::Mat blur;
    cv::blur(img, blur, cv::Size(kernel_size, kernel_size));
    return blur;
}

std::vector<cv::Vec3f> detectLines(const cv::Mat& edges, double rho, double theta, int threshold) {
    std::vector<cv::Vec3f> lines;
    HoughLines(edges, lines, rho, theta, threshold, 0, 0);
    return lines;
}

cv::Mat Task2_LaneDetection(const cv::Mat img){
    cv::Mat gray = bgr2gray(img);
    // Apply blur
    cv::Mat blur = SmoothBlur(gray, 3);
    // Apply Canny edge detection
    cv::Mat edges = cannyEdge(blur, 50, 350, 3);
    // Detect lines using Hough Transform
    std::vector<cv::Vec3f> lines = detectLines(edges, 1, CV_PI/180, 130);
    // sort the lines by rho in descending order
    sort(lines.begin(), lines.end(), compareByRho); // Sort the lines by rho in descending order

    float previous_rho = 0;
    cv::Mat result = img.clone();
    std::vector<cv::Point> points;

    for (size_t i = 0; i < lines.size(); ++i) {

        float rho = lines[i][0];

        float theta = lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        // Condition to avoid drawing multiple lines for the same lane marking
        if (abs(abs(rho) - abs(previous_rho)) < 50) {
            continue;
        }

        else {
            previous_rho = rho;
            // Check if the line is in the range of 40-60 degrees
            if (theta > 0.69 && theta < 1.04) {
                std::cout << "Line " << i << ": rho = " << lines[i][0] << ", theta = " << lines[i][1] << ", vote = " << lines[i][2]<< std::endl;

                pt1.x = cvRound(x0 + 300 * (-b));
                pt1.y = cvRound(y0 + 300 * a);
                pt2.x = cvRound(x0 - 300 * (-b));
                pt2.y = cvRound(y0 - 300 * a);
                line(result, pt1, pt2, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
                // Store the points to fill the polygon
                points.push_back(cv::Point(pt1.x, pt1.y));
                points.push_back(cv::Point(pt2.x, pt2.y));

            }
            // Check if the line is in the range of 130-150 degrees
            else if (theta > 2.26 && theta < 2.65) {
                std::cout << "Line " << i << ": rho = " << lines[i][0] << ", theta = " << lines[i][1] << ", vote = " << lines[i][2]<< std::endl;
                pt1.x = cvRound(x0 + (-570 * (-b)));
                pt1.y = cvRound(y0 + (-570 * a));
                pt2.x = cvRound(x0 - 1000 * (-b));
                pt2.y = cvRound(y0 - 1000 * a);
                line(result, pt2, pt1, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
                points.push_back(cv::Point(pt1.x, pt1.y));
                points.push_back(cv::Point(pt2.x, pt2.y));
            }
        }
    }
    // Fill the polygon
    fillConvexPoly(result, points, cv::Scalar(0, 0, 255), cv::LINE_AA);


    return result;
}
