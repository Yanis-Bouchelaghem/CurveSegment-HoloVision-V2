#pragma once
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <random>
#include "RandomWalk.h"

class VideoProcessor
{
public:
	VideoProcessor(const std::vector<cv::Mat>& video, int videoIndex, const cv::Mat& hologramMask,
				   const RandomWalk& randomWalk, float segmentThreshold, bool visualizeSegments = false);
	void GenerateImagesFromSegments(std::string outputFolder, int hologramTarget, int nonHologramTarget, int segmentLength) const;
private:
	bool IsSegmentIntersectingHologram(const std::vector<Vec2<int>>& curveSegment) const;
	cv::Mat GenerateImageFromSegment(const std::vector<Vec2<int>>& curveSegment) const;
	cv::Mat DrawSegmentOnFirstFrame(const std::vector<Vec2<int>>& curveSegment) const;
private:
	const std::vector<cv::Mat>& video;
	const int videoIndex;
	const cv::Mat& hologramMask;
	const float segmentThreshold;
	const RandomWalk& randomWalk;
	const bool visualizeSegments;
};