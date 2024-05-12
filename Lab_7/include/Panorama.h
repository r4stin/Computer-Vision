#ifndef LAB_7_24_PANORAMA_H
#define LAB_7_24_PANORAMA_H
#include "header.h"
#include "../PanoramicUtils/header/panoramic_utils.h"

class Panorama {
    public:

    // Store the names of the images
    void setImagesNames(const std::vector<std::string> &images_names) { images_names_ = images_names; };
    // Project the images on the cylinder
    void projectImages(const int angle);
    // Extract the features of the images
    void extractFeatures();
    // Match the features of the images and find the homography matrix
    void exhaustiveMatching(const float ratio);
    // Merge the images to create the panorama
    void mergeImages();



private:
    std::vector<std::string> images_names_;
    std::vector<cv::Mat> Projected_Images_;
    std::vector< std::vector<cv::KeyPoint> > features_;
    std::vector< cv::Mat > descriptors_;
    std::vector<cv::DMatch> inlier_matches_;
    std::vector<cv::Mat> homographies_;
};



#endif //LAB_7_24_PANORAMA_H
