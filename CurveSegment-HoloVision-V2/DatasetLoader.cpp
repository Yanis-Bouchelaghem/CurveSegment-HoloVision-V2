#include "DatasetLoader.h"
#include <opencv2/core.hpp>
#include <assert.h>
#include <filesystem>

Frame::Frame(std::string framePath)
	:
	absolutePath(cv::samples::findFile(framePath, false))
{
	assert(!absolutePath.empty()); //If assertion triggers : frame was not found.
}

Video::Video(std::string videoPath)
{
	std::vector<std::string> framePaths;
	for (auto& element : std::filesystem::directory_iterator(videoPath))
		if (element.is_regular_file() && element.path().extension() == ".jpg")
			framePaths.emplace_back(element.path().string());
	//Sort the images lexicographically using their names.
	std::sort(framePaths.begin(), framePaths.end());
	//Turn them into actual frame objects.
	frames.reserve(framePaths.size());
	for (std::string framePath : framePaths)
	{
		frames.emplace_back(framePath);
	}
}

int Video::GetFrameCount() const
{
	return frames.size();
}

DatasetLoader::DatasetLoader(std::string folderPath)

{
	std::vector<std::string> videosPaths;
	for (auto& element : std::filesystem::directory_iterator(folderPath))
		if (element.is_directory())
			videosPaths.push_back(element.path().string());
	//Sort the directories lexicographically.
	std::sort(videosPaths.begin(), videosPaths.end());
	//Turn them into actual video objects.
	videos.reserve(videosPaths.size());
	for (std::string directoryPath : videosPaths)
	{
		videos.emplace_back(directoryPath);
	}
	auto shortestLongestPair = std::minmax_element(videos.begin(),
												   videos.end(),
												   [](const Video& lhs, const Video& rhs){return lhs.GetFrameCount() < rhs.GetFrameCount();});
	minimumFrameCount = (*shortestLongestPair.first).GetFrameCount();
	maximumFrameCount = (*shortestLongestPair.second).GetFrameCount();
}


