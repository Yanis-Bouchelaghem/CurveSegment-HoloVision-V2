#include "RandomWalk.h"

RandomWalk::RandomWalk(int height, int width)
	:
	height(height),
	width(width),
	rng(std::random_device()()),
	heightDistribution(0, height - 1),
	widthDistribution(0, width - 1)
{
}

std::vector<Vec2<int>> RandomWalk::GenerateCurveSegment(int length) const
{
	//Start at a random position in the image
	std::vector<Vec2<int>> curveSegment;
	Vec2<int> currentPosition{widthDistribution(rng), heightDistribution(rng) };
	curveSegment.emplace_back(currentPosition);

	for (int i = 1; i < length; ++i)
	{
		auto walkDirection = RandomWalk::Direction(directionDistribution(rng));
		currentPosition = Step(currentPosition, walkDirection);
		curveSegment.emplace_back(currentPosition);
	}

	return curveSegment;
}

int RandomWalk::GetHeight() const
{
	return height;
}

int RandomWalk::GetWidth() const
{
	return width;
}

Vec2<int> RandomWalk::Step(const Vec2<int>& currentPosition,Direction direction) const
{
	//Take a step in a random direction.
	auto walkDirection = RandomWalk::Direction(directionDistribution(rng));
	switch (walkDirection)
	{
	case RandomWalk::Direction::UP:
		return { currentPosition.x, std::max(0,currentPosition.y - 1) };
	case RandomWalk::Direction::RIGHT:
		return { std::min(width - 1, currentPosition.x + 1), currentPosition.y };
	case RandomWalk::Direction::BOTTOM:
		return { currentPosition.x, std::min(height - 1,currentPosition.y + 1) };
	case RandomWalk::Direction::LEFT:
		return { std::max(0, currentPosition.x - 1), currentPosition.y };
	}
}
