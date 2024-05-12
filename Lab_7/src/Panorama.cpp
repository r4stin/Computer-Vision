#include "../include/Panorama.h"


void Panorama::projectImages(const int angle) {
    // Project the images on the cylinder
    std::vector<cv::Mat> result;
    for (int i = 0; i < images_names_.size(); i++) {
        cv::Mat image = cv::imread(images_names_[i]);
        cv::Mat tmp = cylindricalProj(image, angle);
        Projected_Images_.push_back(tmp);
    }}



void Panorama::extractFeatures() {
    features_.resize(images_names_.size());
    descriptors_.resize(images_names_.size());

    cv::Ptr<cv::SIFT> sift = cv::SIFT::create();
    std::cout << "Extracting features..." << std::endl;
    // extract the features of the images
    for (int i = 0; i < images_names_.size(); i++) {
        sift->detectAndCompute(Projected_Images_[i], cv::noArray(), features_[i], descriptors_[i]);
    }

}

void Panorama::exhaustiveMatching(const float ratio) {
    std::vector<std::vector<cv::DMatch>> matches;

    cv::Ptr<cv::BFMatcher> matcher = cv::BFMatcher::create(cv::NORM_L2);
    // match the features of the images
    for (int i = 0; i < images_names_.size() - 1; i++) {

        std::cout << "Matching image " << i + 1 << " with image " << i + 2 << std::endl;

        matcher->knnMatch(descriptors_[i], descriptors_[i + 1], matches, 2);
        // filter the matches
        std::vector<cv::DMatch> good_matches;
        for (int k = 0; k < matches.size(); k++) {
            if (matches[k][0].distance < ratio * matches[k][1].distance) {
                good_matches.push_back(matches[k][0]);
            }
        }
        std::cout << "Number of matches: " << good_matches.size() << std::endl;
        std::vector<cv::Point2f> points1, points2;
        for (int k = 0; k < good_matches.size(); k++) {
            points1.push_back(features_[i][good_matches[k].queryIdx].pt);
            points2.push_back(features_[i + 1][good_matches[k].trainIdx].pt);
        }

        // find the homography matrix
        cv::Mat mask_H;
        cv::Mat H = cv::findHomography(points1, points2, cv::RANSAC, 3, mask_H);
        // Find the inliers and extract the x and y translation
        std::vector<cv::Point2f> inlierP1, inlierP2;
        for (size_t i = 0; i < mask_H.rows; ++i) {
            if (mask_H.at<uchar>(i)) {
                inlierP1.push_back(points1[i]);
                inlierP2.push_back(points2[i]);
            }
        }
        // calculate the translation
        double total_x = 0.0, total_y = 0.0;
        for (size_t i = 0; i < inlierP2.size(); ++i) {
            double x = inlierP2[i].x - inlierP1[i].x;
            double y = inlierP2[i].y - inlierP1[i].y;
            total_x += x;
            total_y += y;
        }
        double dx = total_x / inlierP1.size();
        double dy = total_y / inlierP1.size();
        cv::Mat translationMatrix = (cv::Mat_<double>(3, 3) << 1, 0, dx, 0, 1, dy, 0, 0, 1);
        homographies_.push_back(translationMatrix);


    }
}

void Panorama::mergeImages() {
    int panoramaHeight = 0, panoramaWidth = 0;
    int padding = 5;
    // calculate the dimensions of the panorama
    for (const auto &image : Projected_Images_) {
        panoramaHeight = std::max(panoramaHeight, image.rows);
        panoramaWidth += image.cols;
    }

    for (int i = 0; i < homographies_.size(); i++) {

        panoramaWidth += homographies_[i].at<int>(0, 2) + padding;
    }


    // create the panorama
    cv::Mat mergedPanorama(panoramaHeight, panoramaWidth, CV_8UC1, cv::Scalar(0));

    // copy the first image to panaorama
    cv::Mat translatedImage;
    cv::warpPerspective(Projected_Images_[0], translatedImage, homographies_[0], cv::Size(panoramaWidth, panoramaHeight));
    translatedImage.copyTo(mergedPanorama(cv::Rect(0, 0, translatedImage.cols, translatedImage.rows)));

    int x = 0, yy = 0;
    for (int i = 1; i < Projected_Images_.size(); i++)
    {
        // handling the y coordinate of the image
        double y = (homographies_[i - 1].at<double>(1, 2) < 0) ?  homographies_[i - 1].at<double>(1, 2) : - homographies_[i - 1].at<double>(1, 2);
        // create the translated image
        cv::warpPerspective(Projected_Images_[i], translatedImage, homographies_[i - 1], cv::Size(Projected_Images_[i].cols , Projected_Images_[i].rows + y));
        // handling the x coordinate of the image
        x -= homographies_[i - 1].at<double>(0, 2) + padding;

        // copy the translated image to the panorama
        translatedImage.copyTo(mergedPanorama(cv::Rect(x, fabs(y), translatedImage.cols, translatedImage.rows)));

    }

    std::vector<cv::Point> nonBlackList;
    nonBlackList.reserve(mergedPanorama.rows*mergedPanorama.cols);

    // remove black pixels
    for(int j=0; j<mergedPanorama.rows; ++j)
        for(int i=0; i<mergedPanorama.cols; ++i)
        {
            // if not black: add to the list
            if(mergedPanorama.at<uchar>(j,i) != uchar(0))
            {
                nonBlackList.push_back(cv::Point(i,j));
            }
        }

    cv::Rect bb = cv::boundingRect(nonBlackList);
    mergedPanorama = mergedPanorama(bb);
    cv::imshow("Panorama", mergedPanorama);
    cv::waitKey(0);
}