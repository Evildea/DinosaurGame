#pragma once

template <class T>
class V2
{
public:
	T x, y;

	V2() : x(0.0f), y(0.0f) {};
	V2(T x, T y) : x(x), y(y) {};
	~V2() {};

	// Equals operator.
	void operator=(const V2 rhs) { x = rhs.x, y = rhs.y; };

	// Addition operator.
	V2<T> operator+(const V2 rhs) const { return { x + rhs.x, y + rhs.y }; };

	// Addition and equals operator.
	void operator+=(const V2 rhs) { x += rhs.x, y += rhs.y; }

	// Subtraction operator.
	V2<T> operator-(const V2 rhs) const { return { x - rhs.x, y - rhs.y }; };

	// Multiplication operators.
	V2<T> operator*(const V2 rhs) const { return { x * rhs.x, y * rhs.y }; };
	V2<T> operator*(const float rhs) const { return { x * rhs, y * rhs }; };

	// Not equaled to operator.
	bool operator!=(const V2 rhs) { return x != rhs.x && y != rhs.y; }

	// This returns the magnitude or length of the Vector.
	T getMagnitude() const { return sqrt(x * x + y * y); };

	// This returns a vector that has been normalised.
	V2<T> getNormalised() const { return{ x / getMagnitude(), y / getMagnitude() }; };

};

