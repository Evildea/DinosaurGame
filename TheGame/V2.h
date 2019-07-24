#pragma once

template <class T>
class V2
{
public:
	T x, y;

	V2() : x(0.0f), y(0.0f) {};
	V2(T x, T y) : x(x), y(y) {};
	~V2() {};

	void operator=(const V2 rhs) { x = rhs.x, y = rhs.y; };
	V2<T> operator+(const V2 rhs) const { return { x + rhs.x, y + rhs.y }; };
	void operator+=(const V2 rhs) { x += rhs.x, y += rhs.y; }
	V2<T> operator-(const V2 rhs) const { return { x - rhs.x, y - rhs.y }; };
	V2<T> operator*(const V2 rhs) const { return { x * rhs.x, y * rhs.y }; };
	V2<T> operator*(const float rhs) const { return { x * rhs, y * rhs }; };
	bool operator!=(const V2 rhs) { return x != rhs.x && y != rhs.y; }

	T getMagnitude() const { return sqrt(x * x + y * y); };
	V2<T> getNormalised() const { return{ x / getMagnitude(), y / getMagnitude() }; };

};

