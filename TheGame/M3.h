#pragma once
#include "V2.h"
#include <math.h>

template <class T>
class M3
{
private:
	T data[9];
	float radians;

public:

	V2<T> xAxis;
	V2<T> yAxis;
	V2<T> zAxis;

	M3() { xAxis = { 1.0f,0.0f }, yAxis = { 0.0f,1.0f }, zAxis = { 0.0f,0.0f }; };
	M3(V2<T> xAxis, V2<T> yAxis, V2<T> zAxis) : xAxis(xAxis), yAxis(yAxis), zAxis(zAxis) {};
	~M3() {};

	// Operator to convert the Matrix3 into a float.
	operator float*()
	{
		data[0] = xAxis.x;
		data[1] = xAxis.y;
		data[2] = 0.0f;
		data[3] = yAxis.x;
		data[4] = yAxis.y;
		data[5] = 0.0f;
		data[6] = zAxis.x;
		data[7] = zAxis.y;
		data[8] = 1.0f;

		return data;
	};

	// Equals operator.
	void operator=(const M3 rhs) { xAxis = rhs.xAxis, yAxis = rhs.yAxis, zAxis = rhs.zAxis; };

	// Addition operator. Takes in Matrix3.
	M3<T> operator+(const M3 rhs) const { return { xAxis + rhs.xAxis, yAxis + rhs.yAxis, zAxis + rhs.zAxis }; };

	// Addition operator. Takes in a Vector2.
	M3<T> operator+(const V2<T> rhs) const { return { xAxis, yAxis, zAxis + rhs }; };

	// Transformation function. Takes in the current and target position then calculates the transform of the Matrix based on that.
	void rotate(V2<T> a_currentPosition, V2<T> a_targetPosition, bool a_relative)
	{
		radians = (a_relative == false) ? -atan2f(a_targetPosition.x - a_currentPosition.x, a_targetPosition.y - a_currentPosition.y) : -atan2f(a_currentPosition.x, a_currentPosition.y);
		xAxis = { cosf(radians), sinf(radians) };
		yAxis = { -sinf(radians), cosf(radians) };
	};

	// Transformation function. Takes in the radians and then calculates the transform based on that.
	void rotate(float a_radian)
	{
		xAxis = { cosf(a_radian), sinf(a_radian) };
		yAxis = { -sinf(a_radian), cosf(a_radian) };
	}

	// This returns the current rotation.
	float getRadians() { return radians; };

};

