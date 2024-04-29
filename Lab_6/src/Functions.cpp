#include "../include/header.h"
#include "../include/functions.h"

void similarity(std::vector<cv::DMatch> good_matches){
    // Define Thresholds for similarity
    const int MIN_GOOD_MATCHES_SIMILAR = 120;
    const int MIN_GOOD_MATCHES_SEMI_SIMILAR = 70;

    if (good_matches.size() > MIN_GOOD_MATCHES_SIMILAR) {
        std::cout << "The two images have similar content." << std::endl;
    } else if (good_matches.size() > MIN_GOOD_MATCHES_SEMI_SIMILAR) {
        std::cout << "The two images have similar content processed by some strong transformation." << std::endl;
    } else {
        std::cout << "The two images have different content." << std::endl;
    }
}
void flannMatcher(cv::Mat img1, cv::Mat img2, std::vector<cv::KeyPoint> kp1, std::vector<cv::KeyPoint> kp2, cv::Mat des1, cv::Mat des2, std::string windowName) {

    // FLANN parameters
    cv::Ptr<cv::flann::IndexParams> indexParams = new cv::flann::KDTreeIndexParams(5);
    cv::Ptr<cv::flann::SearchParams> searchParams = new cv::flann::SearchParams(50);
    cv::FlannBasedMatcher flannMatcher(indexParams, searchParams);
    // Find matches using KNN
    std::vector<std::vector<cv::DMatch>> knnMatches;
    flannMatcher.knnMatch(des1, des2, knnMatches, 2);

    // Calculate good matches based on Lowe's ratio test
    std::vector<cv::DMatch> goodMatches;
    for (size_t i = 0; i < knnMatches.size(); ++i) {
        if (knnMatches[i][0].distance < 0.7 * knnMatches[i][1].distance) {
            goodMatches.push_back(knnMatches[i][0]);
        }
    }


    std::cout << "Good matches: " << goodMatches.size() << std::endl;
    // Calculate similarity
    similarity(goodMatches);


    // Draw matches
    cv::Mat imgMatches;
    cv::drawMatches(img1, kp1, img2, kp2, goodMatches, imgMatches,
                    cv::Scalar::all(-1), cv::Scalar::all(-1),
                    std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    // Display the matches
    cv::imshow(windowName, imgMatches);

}

void bruteforceMatcherKnn(cv::Mat img1, cv::Mat img2, std::vector<cv::KeyPoint> kp1, std::vector<cv::KeyPoint> kp2, cv::Mat descriptors1, cv::Mat descriptors2, int norm, std::string windowname){


                // Apply KNN matching using BFMatcher
                cv::BFMatcher matcher(norm);

                std::vector<std::vector<cv::DMatch>> knnMatches;
                matcher.knnMatch(descriptors1, descriptors2, knnMatches, 2);

                std::vector<cv::DMatch> good_matches;
                // Calculate good matches based on Lowe's ratio test
                double ratio = 0.7;
                for (int j = 0; j < knnMatches.size(); j++) {
                    if (knnMatches[j][0].distance < ratio * knnMatches[j][1].distance) {
                        good_matches.push_back(knnMatches[j][0]);
                    }
                }
                std::cout << "Good matches: " << good_matches.size() << std::endl;
                // Calculate similarity
                similarity(good_matches);

                // Draw matches
                cv::Mat imgMatches;
                cv::drawMatches(img1, kp1, img2, kp2, good_matches, imgMatches,
                                cv::Scalar::all(-1), cv::Scalar::all(-1),
                                std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    // Display the matches
    cv::imshow(windowname, imgMatches);
}



void bruteforceMatcher(cv::Mat img1, cv::Mat img2, std::vector<cv::KeyPoint> keypoints1_o, std::vector<cv::KeyPoint> keypoints2_o, cv::Mat descriptors1, cv::Mat descriptors2, std::string windowName) {
    // Apply brute force matching using BFMatcher
    cv::BFMatcher matcher(cv::NORM_HAMMING);
    std::vector<cv::DMatch> matches1;
    matcher.match(descriptors1, descriptors2, matches1);


    std::vector<cv::DMatch> good_matches;
    // Store the keypoints of matches from query and train image
    std::vector<cv::Point2f> points1, points2;
    for (int k = 0; k < matches1.size(); k++) {
        points1.push_back(keypoints1_o[matches1[k].queryIdx].pt);
        points2.push_back(keypoints2_o[matches1[k].trainIdx].pt);
    }
    // Find homography
    cv::Mat mask;
    cv::Mat H = cv::findHomography(points1, points2, cv::RANSAC, 8, mask);
    // Store good matches
    for (int k = 0; k < mask.rows; k++) {
        if (mask.at<uchar>(k, 0) == 1) {
            good_matches.push_back(matches1[k]);
        }
    }
    std::cout << "Good matches: " << good_matches.size() << std::endl;
    // Calculate similarity
    similarity(good_matches);

    // Draw matches
    cv::Mat imgMatches;
    cv::drawMatches(img1, keypoints1_o, img2, keypoints2_o, good_matches, imgMatches,
                    cv::Scalar::all(-1), cv::Scalar::all(-1),
                    std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    // Display the matches
    cv::imshow(windowName, imgMatches);

}



void siftDetector(cv::Mat img1, cv::Mat img2){

    // Apply SIFT detector
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create(3000);

    // Find the keypoints and descriptors with SIFT
    std::vector<cv::KeyPoint> kp1, kp2;
    cv::Mat des1, des2;
    sift->detectAndCompute(img1, cv::noArray(), kp1, des1);
    sift->detectAndCompute(img2, cv::noArray(), kp2, des2);

    // Find matches using Flann and brute force matching
    std::string windowName_flann = "Using SIFT - Flann Matching";
    std::cout << "Using SIFT - Flann Matching" << std::endl;
    flannMatcher(img1, img2, kp1, kp2, des1, des2, windowName_flann);
    std::cout << std::endl;
    std::cout << "Using SIFT - Brute Force Matching KNN" << std::endl;
    std::string windowName = "Using SIFT - Brute Force Matching KNN";
    bruteforceMatcherKnn(img1, img2, kp1, kp2, des1, des2, cv::NORM_L2, windowName);
    std::cout << std::endl;

}


void orbDetector(cv::Mat img1, cv::Mat img2){

        // Apply ORB detector
        cv::Ptr<cv::ORB> orb = cv::ORB::create(3000);

        // Find the keypoints and descriptors with ORB
        std::vector<cv::KeyPoint> kp1, kp2;
        cv::Mat des1, des2;
        orb->detectAndCompute(img1, cv::noArray(), kp1, des1);
        orb->detectAndCompute(img2, cv::noArray(), kp2, des2);
        // Find matches using Flann and brute force matching
        std::cout << "Using ORB - Brute Force Matching KNN" << std::endl;
        std::string windowName = "Using ORB - Brute Force Matching KNN";
        bruteforceMatcherKnn(img1, img2, kp1, kp2, des1, des2, cv::NORM_HAMMING, windowName);
        std::cout << std::endl;
        std::string windowName1 = "Using ORB - Brute Force Matching Matcher";
        std::cout << "Using ORB - Brute Force Matching Matcher" << std::endl;
            bruteforceMatcher(img1, img2, kp1, kp2, des1, des2, windowName1);
        std::cout << std::endl;

}

void surfDetector(cv::Mat img1, cv::Mat img2){

    // Apply SURF detector
    cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create();

    // Find the keypoints and descriptors with SURF
    std::vector<cv::KeyPoint> kp1, kp2;
    cv::Mat des1, des2;
    surf->detectAndCompute(img1, cv::noArray(), kp1, des1);
    surf->detectAndCompute(img2, cv::noArray(), kp2, des2);

    // Find matches using Flann and brute force matching
    std::string windowName_flann = "Using SURF - Flann Matching";
    std::cout << "Using SURF - Flann Matching" << std::endl;
    flannMatcher(img1, img2, kp1, kp2, des1, des2, windowName_flann);
    std::cout << std::endl;
    std::cout << "Using SURF - Brute Force Matching KNN" << std::endl;
    std::string windowName = "Using SURF - Brute Force Matching KNN";
    bruteforceMatcherKnn(img1, img2, kp1, kp2, des1, des2, cv::NORM_L2, windowName);
    std::cout << std::endl;

}
