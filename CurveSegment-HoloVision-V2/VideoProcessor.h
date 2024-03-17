#pragma once
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <random>
#include "RandomWalk.h"

class VideoProcessor
{
public:
	VideoProcessor(const std::vector<cv::Mat>& video, const cv::Mat& hologramMask,
				   const RandomWalk& randomWalk);
	void GenerateImagesFromSegments(std::string outputFolder, int hologramTarget, int nonHologramTarget, int segmentLength) const;
private:
	
private:
	const std::vector<cv::Mat>& video;
	const cv::Mat& hologramMask;
	const RandomWalk& randomWalk;
};