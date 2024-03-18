#include "utils.h"

cv::Mat utils::LoadImage(std::string imagePath, cv::ImreadModes readMode)
{
    std::string absolutePath = cv::samples::findFile(imagePath, true);
    return cv::imread(absolutePath, readMode);
}

cv::Mat utils::BorderPadding(const cv::Mat& inputImage, int paddingSize)
{
    assert(inputImage.dims == 2); //If assertion triggers : Input is not a 2D image.
    //Create an empty image with enough space for the border.
    cv::Mat imagePadded(inputImage.rows + 2 * paddingSize, inputImage.cols + 2 * paddingSize, inputImage.depth());
    // form a border in-place
    cv::copyMakeBorder(inputImage, imagePadded, paddingSize, paddingSize,
        paddingSize, paddingSize, cv::BORDER_REPLICATE);
    return imagePadded;
}

cv::Mat utils::RemoveBorder(const cv::Mat& inputImage, int borderSize)
{
    return inputImage(cv::Rect{ borderSize,borderSize, inputImage.cols - 2 * borderSize, inputImage.rows - 2 * borderSize });
}

