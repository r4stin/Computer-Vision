#include "header.h"
#include "functions.h"



int main(int argc, char** argv ) {

    if (argc < 2) {
        std::cout << "Image filename shall be provided!" << std::endl;
        return -1;

    }
     //Load the image
    cv::Mat image =  imread(argv[1], cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Error: Unable to load image!" << std::endl;
        return -1;
    }

    cv::Mat app1 = task1App1(image);
    ShowImage(app1, "App1 Result");
    cv::Mat app2 = task1App2(image);
    ShowImage(app2, "App2 Result");

    // Wait for a key press
    cv::waitKey(0);
    return 0;
}




//using namespace cv;
//using namespace std;
//
//int main() {
//    Mat src;
//
//    src = imread("Asphalt cracks/Asphalt-2.png");
//    imshow("original", src);
//
//    blur(src, src, Size(15,15));
//    imshow("blurred", src);
//
//    Mat p = Mat::zeros(src.cols*src.rows, 5, CV_32F);
//    Mat bestLabels, centers, clustered;
//    vector<Mat> bgr;
//    cv::split(src, bgr);
//    // i think there is a better way to split pixel bgr color
//    for(int i=0; i<src.cols*src.rows; i++) {
//        p.at<float>(i,0) = (i/src.cols) / src.rows;
//        p.at<float>(i,1) = (i%src.cols) / src.cols;
//        p.at<float>(i,2) = bgr[0].data[i] / 255.0;
//        p.at<float>(i,3) = bgr[1].data[i] / 255.0;
//        p.at<float>(i,4) = bgr[2].data[i] / 255.0;
//    }
//
//    ShowImage(p, "Original Image");
//
//    int K = 2;
//    cv::kmeans(p, K, bestLabels,
//               TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0),
//               3, KMEANS_PP_CENTERS, centers);
//
//    int colors[K];
//    for(int i=0; i<K; i++) {
//        colors[i] = 255/(i+1);
//    }
//    // i think there is a better way to do this mayebe some Mat::reshape?
//    clustered = Mat(src.rows, src.cols, CV_32F);
//    for(int i=0; i<src.cols*src.rows; i++) {
//        clustered.at<float>(i/src.cols, i%src.cols) = (float)(colors[bestLabels.at<int>(0,i)]);
////      cout << bestLabels.at<int>(0,i) << " " <<
////              colors[bestLabels.at<int>(0,i)] << " " <<
////              clustered.at<float>(i/src.cols, i%src.cols) << " " <<
////              endl;
//    }
//
//    clustered.convertTo(clustered, CV_8U);
//    imshow("clustered", clustered);
//
//    waitKey();
//    return 0;
//}