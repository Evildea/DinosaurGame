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

	void operator=(const M3 rhs) { xAxis = rhs.xAxis, yAxis = rhs.yAxis, zAxis = rhs.zAxis; };
	M3<T> operator+(const M3 rhs) const { return { xAxis + rhs.xAxis, yAxis + rhs.yAxis, zAxis + rhs.zAxis }; };
	M3<T> operator+(const V2<T> rhs) const { return { xAxis, yAxis, zAxis + rhs }; };

	void rotate(V2<T> a_XYPosition, V2<T> a_targetXYPosition, bool a_relative)
	{
		radians = (a_relative == false) ? -atan2f(a_targetXYPosition.x - a_XYPosition.x, a_targetXYPosition.y - a_XYPosition.y) : -atan2f(a_XYPosition.x, a_XYPosition.y);
		xAxis = { cosf(radians), sinf(radians) };
		yAxis = { -sinf(radians), cosf(radians) };
	};
	void rotate(float a_radian)
	{
		xAxis = { cosf(a_radian), sinf(a_radian) };
		yAxis = { -sinf(a_radian), cosf(a_radian) };
	}

	float getRadians() { return radians; };

};

