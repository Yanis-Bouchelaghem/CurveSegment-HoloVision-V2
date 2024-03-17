#pragma once
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

class Frame
{
public:
	Frame() = default;
	Frame(std::string framePath);
	cv::Mat LoadFrame(cv::ImreadModes readMode) const;
private:
	std::string absolutePath;
};

class Video
{
public:
	Video(std::string videoPath);
	std::vector<cv::Mat> LoadVideo(cv::ImreadModes readMode) const;
	int GetFrameCount() const;
	void TruncateFrameCount(int count);
private:
	std::vector<Frame> frames; 
};


class DatasetLoader
{
public:
	DatasetLoader(std::string folderPath);
	int GetVideoCount() const;
	std::vector<cv::Mat> LoadVideo(int index, cv::ImreadModes readMode) const;
	void TruncateFrameCountToMin();
private:
	std::vector<Video> videos;
	int maximumFrameCount;
	int minimumFrameCount;
};