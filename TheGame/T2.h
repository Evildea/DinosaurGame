#pragma once
#include "Renderer2D.h"
#include "Global.h"
#include <math.h>
#include "V2.h"
#include "M3.h"

// The function of the T2 is to provide a target in 2D space to look towards or travel towards.
// This is primarily used to ensure that head of the dinosaur rotates smoothly towards its target.

class T2
{
private:
	V2<float> m_transform;
	V2<float> m_velocity;
	V2<float> m_avoid;

public:
	T2();
	~T2();

	void update(M3<float> a_transform, V2<float> a_target, float a_speed, float a_minDistance, float deltaTime);
	void draw(aie::Renderer2D * a_renderer, float r, float g, float b);
	V2<float> getPosition();
	void setPosition(V2<float> a_position);
	void updateAvoid(V2<float> a_avoid);
};

