#pragma once

//A generic class for representing a 2D mathematical vector.
template<typename T>
class Vec2
{
public:
	Vec2(T x, T y)
		:
		x(x),
		y(y)
	{
	}
public:
	T x;
	T y;
};