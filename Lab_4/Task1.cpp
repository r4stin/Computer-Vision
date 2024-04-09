#include "header.h"
#include "functions.h"


cv::Mat src, src_gray;
cv::Mat dst, detected_edges;
int lowThreshold = 0;
int highThreshold = 0;
int max_lowThreshold = 100;
int max_highThreshold = 500;
const int ratio = 3;
int kernel_size = 0;
int kernel_sizes[] = {3, 5, 7};
const char* window_name = "Edge Map";
static void CannyThreshold(int, void*)
{
    blur( src_gray, detected_edges, cv::Size(3,3) );
    Canny( detected_edges, detected_edges, lowThreshold, highThreshold, kernel_sizes[kernel_size] );
    dst = cv::Scalar::all(0);
    src.copyTo( dst, detected_edges);
//    imshow( window_name, dst );
    ShowImage(dst, window_name);
}
int main( int argc, char** argv )
{

    if (argc < 2) {
        std::cout << "Image filename shall be provided!" << std::endl;
        return -1;

    }
    // Read the image file
    src = imread(argv[1], cv::IMREAD_COLOR);

    if( src.empty() )
    {
        std::cout << "Could not open or find the image!\n" << std::endl;
        std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
        return -1;
    }
    namedWindow( window_name, cv::WINDOW_AUTOSIZE );
    src_gray = bgr2gray(src);
    cv::createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
    cv::createTrackbar( "Max Threshold:", window_name, &highThreshold, max_highThreshold, CannyThreshold );
    cv::createTrackbar( "Kernel size", window_name, &kernel_size, 2, CannyThreshold );
    CannyThreshold(0, 0);
    cv::waitKey(0);
    return 0;
}