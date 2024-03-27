#include "header.h"
#include "functions.h"


int main(int argc, char** argv) {

    //Creates two images of size 256x256, one channel, 8-bit depth unsigned
    //char in order to create a vertical gradient and a horizontal gradient images.
    cv::Mat img = CreateImage_task5(256, 256);
    cv::Mat ver_img = VerticalGradient(img);
    ShowImage(ver_img, "Vertical Gradient");
    cv::Mat hor_img = HorizontalGradient(img);
    ShowImage(hor_img, "Horizontal Gradient");

    //Creates two images of size 300x300, one channel, 8-bit depth unsigned
    //char in order to create a chessboard pattern with 20p and 50p of the
    cv::Mat img2 = CreateImage_task5(300, 300);
    cv::Mat chess20p = Chess20p(img2);
    ShowImage(chess20p, "Chess 20p");
    cv::Mat chess50p = Chess50p(img2);
    ShowImage(chess50p, "Chess 50p");
    cv::waitKey(0);


    return 0;
}
