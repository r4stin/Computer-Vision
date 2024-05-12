#include "../include/header.h"
#include "../include/utils.h"
#include "../include/Panorama.h"

int main(int argc, char** argv ) {
//
    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " < Database Path > < Angle value (in degrees) > < Ratio >" << std::endl;
        return -1;

    }

    std::vector<std::string> images_names;
    if( !readFileNamesFromFolder ( argv[1], images_names ) )
    {
        std::cerr<<"Can't load images names, exiting"<<std::endl;
        return -1;
    }
    Panorama p;
    p.setImagesNames(images_names);
    p.projectImages(atoi(argv[2]));
    p.extractFeatures();
    std::cout << atof(argv[3]) << std::endl;
    p.exhaustiveMatching(atof(argv[3]));
    p.mergeImages();




    return 0;
}