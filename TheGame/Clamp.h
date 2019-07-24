#pragma once

// The function of the CLAMP is to clamp a radian between two values.
// This is primarily used to ensure that the head of the dinosaur can't rotate 180 backwards.

class Clamp
{
private:
	float pie, diameter;

public:
	Clamp();
	~Clamp();

	// This function clamps a radian between two offset values.
	float clamp(float minValue, float maxValue, float clampValue);

	// This function finds the minimum of two values.
	float min(float valueX, float valueY);

	// This function finds the maximum of two values.
	float max(float valueX, float valueY);

};

