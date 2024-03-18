#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>

namespace utils
{
	//Loads the specified image into a cv::Mat, throws cv::Exception if image is not found.
	cv::Mat LoadImage(std::string imagePath, cv::ImreadModes readMode);
	//Adds border padding to all sides of a 2D image.
	cv::Mat BorderPadding(const cv::Mat& inputImage, int paddingSize);
	//Remove border from a 2D image.
	cv::Mat RemoveBorder(const cv::Mat& inputImage, int borderSize);
}