#pragma once
#include <string>
#include <vector>

class Frame
{
public:
	Frame(std::string framePath);
private:
	std::string absolutePath;
};

class Video
{
public:
	Video(std::string videoPath);
	int GetFrameCount() const;
private:
	std::vector<Frame> frames; 
};


class DatasetLoader
{
public:
	DatasetLoader(std::string folderPath);
private:
	std::vector<Video> videos;
	int maximumFrameCount;
	int minimumFrameCount;
};