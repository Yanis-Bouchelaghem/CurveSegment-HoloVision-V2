#include "DatasetLoader.h"
#include <opencv2/highgui.hpp>
int main()
{
	DatasetLoader datasetLoader("dataset");
	{
		std::vector<std::vector<cv::Mat>> videos;
		for (int i = 0; i < datasetLoader.GetVideoCount(); ++i)
		{
			videos.push_back(datasetLoader.LoadVideo(i, cv::IMREAD_COLOR));
		}
	}
	cv::waitKey();
	return 0;
}