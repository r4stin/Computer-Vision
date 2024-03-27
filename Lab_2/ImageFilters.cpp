#include "header.h"
#include "ImageFilters.h"


// Function to apply max filter
cv::Mat maxFilter(const cv::Mat& input, cv::Mat& output, int kernelSize) {
    if (kernelSize % 2 == 0) {
        std::cout << "Kernel size must be odd!" << std::endl;

    }else {
        int halfSize = kernelSize / 2;
        output = cv::Mat::zeros(input.size(), input.type());

        for (int y = halfSize; y < input.rows - halfSize; ++y) {
            for (int x = halfSize; x < input.cols - halfSize; ++x) {
                uchar maxVal = 0;
                for (int i = -halfSize; i <= halfSize; ++i) {
                    for (int j = -halfSize; j <= halfSize; ++j) {
                        maxVal = std::max(maxVal, input.at<uchar>(y + i, x + j));
                    }
                }
                output.at<uchar>(y, x) = maxVal;
            }
        }
        return output;
    }
}


// Function to apply min filter
cv::Mat minFilter(const cv::Mat& input, cv::Mat& output, int kernelSize) {
    if (kernelSize % 2 == 0) {
        std::cout << "Kernel size must be odd!" << std::endl;
    }else {

        int halfSize = kernelSize / 2;
        output = cv::Mat::zeros(input.size(), input.type());

        for (int y = halfSize; y < input.rows - halfSize; ++y) {
            for (int x = halfSize; x < input.cols - halfSize; ++x) {
                uchar minVal = 255;
                for (int i = -halfSize; i <= halfSize; ++i) {
                    for (int j = -halfSize; j <= halfSize; ++j) {
                        minVal = std::min(minVal, input.at<uchar>(y + i, x + j));
                    }
                }
                output.at<uchar>(y, x) = minVal;
            }
        }
        return output;
    }
}

// Function to apply median filter
cv::Mat medianFilter(const cv::Mat& input, cv::Mat& output, int kernelSize) {
    if (kernelSize % 2 == 0) {
        std::cerr << "Error: Kernel size must be odd." << std::endl;

    }else{
    int halfSize = kernelSize / 2;
    output = cv::Mat::zeros(input.size(), input.type());

    for (int y = halfSize; y < input.rows - halfSize; ++y) {
        for (int x = halfSize; x < input.cols - halfSize; ++x) {
            std::vector<uchar> values;
            for (int i = -halfSize; i <= halfSize; ++i) {
                for (int j = -halfSize; j <= halfSize; ++j) {
                    values.push_back(input.at<uchar>(y + i, x + j));
                }
            }
            std::sort(values.begin(), values.end());
            output.at<uchar>(y, x) = values[values.size() / 2]; // Median value
        }
    }
    return output;
    }
}

// Function to apply Gaussian filter
cv::Mat Gaussian_Filter(const cv::Mat& imgGray, cv::Mat& output, int kernel) {
    if (kernel % 2 == 0) {
        std::cout << "Kernel size must be odd!" << std::endl;
    } else {
        cv::GaussianBlur(imgGray, output, cv::Size(kernel, kernel), 0, 0);
        return output;
    }
}
