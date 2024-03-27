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

// Function to display the coordinates of the clicked area
void OnMouse(int event, int x, int y, int flags, void *userdata)
{
    cv::Mat src = *(cv::Mat *)userdata;
    cv::Mat dst = src.clone();

    if (event == cv::EVENT_LBUTTONDOWN || event == cv::EVENT_RBUTTONDOWN)
    {

        std::cout << " Clicked area coordinates (x,y): " << x << ", " << y << "\n";
        int blue = dst.at<cv::Vec3b>(y, x)[0];
        int green = dst.at<cv::Vec3b>(y, x)[1];
        int red = dst.at<cv::Vec3b>(y, x)[2];
        std::cout << "B: " << blue << " | G: " << green << " | R: " << red << "\n";
    }

}

// Function to display the coordinates of the clicked area and the mean value of the neighborhood
void OnMouse_Task3(int event, int x, int y, int flags, void *userdata)
{
    cv::Mat src = *(cv::Mat *)userdata;
    cv::Mat dst = src.clone();

    if (event == cv::EVENT_LBUTTONDOWN || event == cv::EVENT_RBUTTONDOWN)
    {

        std::cout << " Coordinates of the clicked area (x,y): " << x << ", " << y << std::endl;

        int blue = dst.at<cv::Vec3b>(y, x)[0];
        int green = dst.at<cv::Vec3b>(y, x)[1];
        int red = dst.at<cv::Vec3b>(y, x)[2];
        std::cout << "B: " << blue << " | G: " << green << " | R: " << red << std::endl;
        if ((y + NEIGHBORHOOD) > dst.rows || x + NEIGHBORHOOD > dst.cols)
            return;

        cv::Rect rect(x, y, NEIGHBORHOOD, NEIGHBORHOOD);
        cv::Scalar mean = cv::mean(dst(rect));
        std::cout << "Mean[ Blue: " << mean[0]  << "  Green: " << mean[1] <<"  Red: " << mean[2] << "  Grayscale: " << mean[3] << std::endl;

    }

}
// Function to create a mask
void Mask(cv::Mat Image, cv::Scalar mean, int T) {
    cv::Mat maskImg(Image.rows, Image.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    for (int y = 0; y < Image.rows; y++)
        for (int x = 0; x < Image.cols; x++)
            if (abs(Image.at<cv::Vec3b>(cv::Point(x, y))(0) - mean[0]) < T
                && abs(Image.at<cv::Vec3b>(cv::Point(x, y))(1) - mean[1]) < T
                && abs(Image.at<cv::Vec3b>(cv::Point(x, y))(2) - mean[2]) < T)
                maskImg.at<cv::Vec3b>(cv::Point(x, y)) = {255, 255, 255, 0};
    ShowImage(maskImg, "Mask");
}



// Function to display the coordinates of the clicked area and the mean value of the neighborhood for Task4
void OnMouse_Task4(int event, int x, int y, int flags, void *userdata)
{
    cv::Mat src = *(cv::Mat *)userdata;
    cv::Mat dst = src.clone();

    if (event == cv::EVENT_LBUTTONDOWN || event == cv::EVENT_RBUTTONDOWN)
    {

        std::cout << " Coordinates of the clicked area (x,y): (" << x << ", " << y << ")" << std::endl;

        int blue = dst.at<cv::Vec3b>(y, x)[0];
        int green = dst.at<cv::Vec3b>(y, x)[1];
        int red = dst.at<cv::Vec3b>(y, x)[2];
        std::cout << "B: " << blue << " | G: " << green << " | R: " << red << std::endl;
        if ((y + NEIGHBORHOOD) > dst.rows || x + NEIGHBORHOOD > dst.cols)
            return;

        cv::Rect rect(x, y, NEIGHBORHOOD, NEIGHBORHOOD);
        cv::Scalar mean = cv::mean(dst(rect));
        std::cout << "Mean[ Blue: " << mean[0]  << "  Green: " << mean[1] <<"  Red: " << mean[2] << "  Grayscale: " << mean[3] << " ]" << std::endl;
        Mask(dst, mean, 60);
    }

}

// Function to display the coordinates of the clicked area and the mean value of the neighborhood for Task5
void OnMouse_Task5(int event, int x, int y, int flags, void *userdata)
{
    cv::Mat src = *(cv::Mat *)userdata;
    cv::Mat dst = src.clone();

    if (event == cv::EVENT_LBUTTONDOWN || event == cv::EVENT_RBUTTONDOWN)
    {
        // Convert the image to HSV color space
        cv::Mat hsv;
        cv::cvtColor(dst, hsv, cv::COLOR_BGR2HSV);

        std::cout << " Coordinates of the clicked area (x,y): (" << x << ", " << y << ")" << std::endl;

        int blue = hsv.at<cv::Vec3b>(y, x)[0];
        int green = hsv.at<cv::Vec3b>(y, x)[1];
        int red = hsv.at<cv::Vec3b>(y, x)[2];
        std::cout << "B: " << blue << " | G: " << green << " | R: " << red << std::endl;
        if ((y + NEIGHBORHOOD) > hsv.rows || x + NEIGHBORHOOD > hsv.cols)
            return;

        cv::Rect rect(x, y, NEIGHBORHOOD, NEIGHBORHOOD);
        cv::Scalar mean = cv::mean(hsv(rect));
        std::cout << "Mean[ Blue: " << mean[0]  << "  Green: " << mean[1] <<"  Red: " << mean[2] << "  Grayscale: " << mean[3] << " ]" << std::endl;
        Mask(hsv, mean, 60);
    }

}

// Function to create a mask for Task6
cv::Mat Mask_Task6(cv::Mat Image, cv::Scalar mean) {

    int T = 60;
    cv::Vec<unsigned int, 3> color = {92, 37, 201, 0};
    cv::Mat maskImg(Image.rows, Image.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    for (int y = 0; y < Image.rows; y++)
        for (int x = 0; x < Image.cols; x++)
            if (abs(Image.at<cv::Vec3b>(cv::Point(x, y))(0) - mean[0]) < T
                && abs(Image.at<cv::Vec3b>(cv::Point(x, y))(1) - mean[1]) < T
                && abs(Image.at<cv::Vec3b>(cv::Point(x, y))(2) - mean[2]) < T)
            {
                maskImg.at<cv::Vec3b>(cv::Point(x, y)) = {255, 255, 255, 0};
                Image.at<cv::Vec3b>(cv::Point(x, y)) = color;
            }
    return maskImg;
}

// Function to display the coordinates of the clicked area and the mean value of the neighborhood for Task6
void OnMouse_Task6(int event, int x, int y, int flags, void *userdata) {

    cv::Mat src = *(cv::Mat *) userdata;
    cv::Mat dst = src.clone();

    if (event == cv::EVENT_LBUTTONDOWN || event == cv::EVENT_RBUTTONDOWN) {

        std::cout << " Coordinates of the clicked area (x,y): (" << x << ", " << y << ")" << std::endl;

        int blue = dst.at<cv::Vec3b>(y, x)[0];
        int green = dst.at<cv::Vec3b>(y, x)[1];
        int red = dst.at<cv::Vec3b>(y, x)[2];
        std::cout << "B: " << blue << " | G: " << green << " | R: " << red << std::endl;
        if ((y + NEIGHBORHOOD) > dst.rows || x + NEIGHBORHOOD > dst.cols)
            return;

        cv::Rect rect(x, y, NEIGHBORHOOD, NEIGHBORHOOD);
        cv::Scalar mean = cv::mean(dst(rect));
        std::cout << "Mean[ Blue: " << mean[0] << "  Green: " << mean[1] << "  Red: " << mean[2] << "  Grayscale: "
                  << mean[3] << " ]" << std::endl;
        ShowImage(Mask_Task6(dst, mean), "Mask");

        ShowImage(dst, "Image");

    }


}
