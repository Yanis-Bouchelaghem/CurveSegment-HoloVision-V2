#include "DatasetLoader.h"
#include <opencv2/highgui.hpp>
#include "RandomWalk.h"
#include "VideoProcessor.h"
#include "Utils.h"
#include "settings.h"
int main()
{
	using namespace settings;
	DatasetLoader datasetLoader("dataset");
	datasetLoader.TruncateFrameCountToMin();
	RandomWalk randomWalk(frameHeight, frameWidth);
	//TODO : Load mask, with the goal of testing the curve segment labelisation.
	cv::Mat passport_hologram_mask = utils::LoadImage("passport_hologram_mask.png", cv::IMREAD_GRAYSCALE);
	auto video = datasetLoader.LoadVideo(1, cv::IMREAD_COLOR);
	VideoProcessor videoProcessor(video, 1, passport_hologram_mask, randomWalk, settings::segmentThreshold, true);
	videoProcessor.GenerateImagesFromSegments("generatedImages", targetHoloCountPerVideo, targetNonHoloCountPerVideo, segmentLength);

	return 0;
}