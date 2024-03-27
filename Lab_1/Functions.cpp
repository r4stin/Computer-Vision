#include "header.h"
#include "functions.h"

cv::Mat ReadImage(const std::string &filename) {
    cv::Mat image = imread(filename, cv::IMREAD_COLOR);
    return image;

}
void ShowImage(const cv::Mat &image, const std::string& windowName) {
    cv::imshow(windowName, image);
}

int NumChannels(const cv::Mat &image) {
    return image.channels();
}

void WaiykeyChar(int key) {
    std::cout << "Waitkey output: " << char(key) << std::endl;
}

cv::Mat ChannelManipulation_Task3(cv::Mat &img, int channel) {
    for (int i = 0; i < img.rows; ++i)
    {
        for (int j = 0; j < img.cols; ++j)
        {
            img.at<cv::Vec3b> (i, j)[channel] = 0;

        }
    }
    return img;
}
void ChannelManipulation_Task4(cv::Mat &img) {

    std::vector<cv::Mat> channels;
    cv::split(img, channels);

    for (size_t i = 0; i < channels.size(); ++i) {
        std::string windowName = "Channel " + std::to_string(i+1);
        ShowImage(channels[i], windowName);
        cv::waitKey(0);
    }
}

cv::Mat CreateImage_task5(int row, int columns) {
    cv::Mat image(row, columns, CV_8UC1);
    return image;
}

cv::Mat VerticalGradient(cv::Mat &image) {
    for (int i = 0; i < image.rows; ++i)
    {
        for (int j = 0; j < image.cols; ++j)
        {
            image.at<uchar>(i, j) = (i * 255) / image.rows;
        }
    }
    return image;
}

cv::Mat HorizontalGradient(cv::Mat &image) {
    for (int i = 0; i < image.rows; ++i)
    {
        for (int j = 0; j < image.cols; ++j)
        {
            image.at<uchar>(i, j) = (j * 255) / image.rows;
        }
    }
    return image;
}

cv::Mat Chess20p(cv::Mat &image) {
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            if ((i / 20 + j / 20) % 2 == 0)
                image.at<uchar>(i, j) = 255;
            else
                image.at<uchar>(i, j) = 0;
        }
    }
    return image;
}

cv::Mat Chess50p(cv::Mat &image) {

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            if ((i / 50 + j / 50) % 2 == 0)
                image.at<uchar>(i, j) = 255;
            else
                image.at<uchar>(i, j) = 0;
        }
    }

    return image;
}
