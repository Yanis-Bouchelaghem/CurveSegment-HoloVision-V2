#include "VideoProcessor.h"
#include <opencv2/highgui.hpp>
#include <filesystem>

VideoProcessor::VideoProcessor(const std::vector<cv::Mat>& video,
							   int videoIndex,
							   const cv::Mat& hologramMask,
							   const RandomWalk& randomWalk,
							   float segmentThreshold)
	:
	video(video),
	videoIndex(videoIndex),
	hologramMask(hologramMask),
	randomWalk(randomWalk),
	segmentThreshold(segmentThreshold)
{
	assert(video[0].rows == randomWalk.GetHeight()); //If assertion triggers : The dimensions of the frames does not match
	assert(video[0].cols == randomWalk.GetWidth());  //the dimensions given in the settings file.
}

void VideoProcessor::GenerateImagesFromSegments(std::string outputFolder, int hologramTarget, int nonHologramTarget, int segmentLength) const
{
	//Create the target folders if they do not exist
	std::filesystem::create_directory(outputFolder);
	std::filesystem::create_directory(outputFolder+"/segments");
	std::filesystem::create_directory(outputFolder+"/holo");
	std::filesystem::create_directory(outputFolder+"/non-holo");
	//As long as we haven't reached the target numbers, keep generating segments
	int hologramCount = 0;
	int nonHologramCount = 0;
	while (hologramCount < hologramTarget || nonHologramCount < nonHologramTarget)
	{
		//Generate a randomwalk
		std::vector<Vec2<int>> curveSegment = randomWalk.GenerateCurveSegment(segmentLength);
		//Determine whether it is intersecting with the hologram
		bool isIntersectingHologram = IsSegmentIntersectingHologram(curveSegment);
		//Generate the evolution image in the correctly labeled folder
		cv::Mat generatedImage = GenerateImageFromSegment(curveSegment);
		std::stringstream outputPath;
		if (isIntersectingHologram && hologramCount < hologramTarget)
		{ 

			outputPath << outputFolder << "/holo/vid" << videoIndex << "_seg" << hologramCount << ".png";
			cv::imwrite(outputPath.str(), generatedImage);
			//TODO : generate the curve on an image and save it in a different folder
			++hologramCount;
		}
		else if(nonHologramCount < nonHologramTarget)
		{

			outputPath << outputFolder << "/non-holo/vid" << videoIndex << "_seg" << hologramCount << ".png";
			cv::imwrite(outputPath.str(), generatedImage);
			++nonHologramCount;
		}

	}
}

bool VideoProcessor::IsSegmentIntersectingHologram(const std::vector<Vec2<int>>& curveSegment) const
{
	int intersectionCount = 0;
	for (const Vec2<int>& position : curveSegment)
	{
		if (hologramMask.at<uchar>(position.y, position.x) == 255)
			++intersectionCount;
	}

	return (float(intersectionCount) / curveSegment.size()) >= segmentThreshold;
}

cv::Mat VideoProcessor::GenerateImageFromSegment(const std::vector<Vec2<int>>& curveSegment) const
{
	//Generate image from curve segment (y = curve segment size, x = number of frames in the video)
	cv::Mat curveSegmentResult(curveSegment.size(), video.size(), CV_8UC3);
	for (int i = 0; i < curveSegment.size(); ++i)
	{
		Vec2 position = curveSegment[i];
		for (int frameIndex = 0; frameIndex < video.size(); ++frameIndex)
		{
			curveSegmentResult.at<cv::Vec3b>(i, frameIndex) = video[frameIndex].at<cv::Vec3b>(position.y, position.x);
		}
	}
	return curveSegmentResult;
}
