#include "../include/utils.h"
#include "../include/header.h"

// Function to check if the format of the image is supported
bool isSupportedFormat(const std::string& filename) {
    // Get the extension of the file
    std::string extension = boost::filesystem::extension(filename);
    // Convert the extension to lowercase
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    // Check if the extension is png or bmp
    return (extension == ".png" || extension == ".bmp");
}


// Function to read the names of the images from a folder
bool readFileNamesFromFolder(const std::string& input_folder_name, std::vector<std::string>& names) {
    names.clear();
    if (!input_folder_name.empty()) {
        boost::filesystem::path p(input_folder_name);
        for (auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(p), {})) {
            std::string filename = entry.path().string();
            if (isSupportedFormat(filename)) {
                names.push_back(filename);
            }
        }
        std::sort(names.begin(), names.end());
        return true;
    } else {
        return false;
    }
}