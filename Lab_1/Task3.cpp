#include "header.h"
#include "functions.h"


int main(int argc, char** argv) {

    if (argc < 2) {
        std::cout << "Image filename shall be provided!" << std::endl;
        return -1;
    }
    cv::Mat image = ReadImage(argv[1]);

    if (image.empty()) {
        std::cout << "Could not open or find the image!" << std::endl;
        return -1;
    }
    std::cout <<"Number of channels: " << NumChannels(image) << std::endl;
    if (NumChannels(image) == 3) {
        image = ChannelManipulation_Task3(image, atoi(argv[2]));
    }else{
        std::cout << "The image does not have 3 channels" << std::endl;
    }
    std::string windowName = "Channel " + std::to_string(atoi(argv[2])+1);
    ShowImage(image, windowName);
    int key = cv::waitKey(0);
    WaiykeyChar(key);






    return 0;
}
