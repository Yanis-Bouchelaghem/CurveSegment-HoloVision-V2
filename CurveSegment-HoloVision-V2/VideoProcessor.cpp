#include "VideoProcessor.h"

VideoProcessor::VideoProcessor(const std::vector<cv::Mat>& video,
							   const cv::Mat& hologramMask,
							   const RandomWalk& randomWalk)
	:
	video(video),
	hologramMask(hologramMask),
	randomWalk(randomWalk)
{
}

void VideoProcessor::GenerateImagesFromSegments(std::string outputFolder, int hologramTarget, int nonHologramTarget, int segmentLength) const
{
	//As long as we haven't reached the target numbers, keep generating segments
	int hologramCount = 0;
	int nonHologramCount = 0;
	while (hologramCount < hologramTarget || nonHologramCount < nonHologramTarget)
	{
		//Generate a randomwalk
		randomWalk.GenerateCurveSegment(segmentLength);
		//Determine whether it is intersecting with the hologram
		//Generate the evolution image in the correctly labeled folder
	}
}
