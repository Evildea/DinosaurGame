#include "Clamp.h"
#include <math.h>


Clamp::Clamp()
{
	float pie = 2 * cosf(0.0);
	float diameter = pie * 2;
}


Clamp::~Clamp()
{
}

float Clamp::clamp(float _minValue, float _maxValue, float _clampValue)
{
	float minValue = _minValue;
	float maxValue = _maxValue;
	float clampValue = _clampValue;

	if (minValue < -pie) { minValue += diameter; }
	if (minValue > pie) { minValue -= diameter; }
	if (maxValue < -pie) { maxValue += diameter; }
	if (maxValue > pie) { maxValue -= diameter; }

	clampValue = max(_minValue, min(_maxValue, _clampValue));

	return clampValue;
}

float Clamp::min(float valueX, float valueY)
{
	return (valueX < valueY) ? valueX : valueY;
}

float Clamp::max(float valueX, float valueY)
{
	return (valueX > valueY) ? valueX : valueY;
}
