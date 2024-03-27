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
        ChannelManipulation_Task4(image);

    }else{
        std::cout << "The image does not have 3 channels" << std::endl;
    }


    return 0;
}
