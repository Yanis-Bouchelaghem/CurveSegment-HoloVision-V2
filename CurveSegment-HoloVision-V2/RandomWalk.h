#pragma once
#include <vector>
#include <random>
#include "vec2.h"

class RandomWalk
{
public:
	enum class Direction
	{
		UP,
		RIGHT,
		BOTTOM,
		LEFT
	};
public:
	RandomWalk(int height, int width);
	std::vector<Vec2<int>> GenerateCurveSegment(int length) const;
	int GetHeight() const;
	int GetWidth() const;
private:
	//Returns the given position after performing a step in the given direction.
	Vec2<int> Step(const Vec2<int>& currentPosition, Direction direction) const;
private:
	const int height;
	const int width;
	mutable std::mt19937 rng;
	mutable std::uniform_int_distribution<int> heightDistribution;
	mutable std::uniform_int_distribution<int> widthDistribution;
	mutable std::uniform_int_distribution<int> directionDistribution{0,3};
};