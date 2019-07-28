#pragma once
#include "Renderer2D.h"
#include "Global.h"
#include "V2.h"

class Entity;

struct Spine
{
	float x, y;
	float radius;
};

class Tail
{
private:
	Spine m_tailList[m_TAILLENGTH + 1];
	float r, g, b, r1, g1, b1;
	int m_tailSplit;
	Entity*	m_owner; // This represents the body that controls these tail.

public:
	Tail();
	~Tail();

	void update(V2<float> a_position);
	void draw(aie::Renderer2D * a_renderer, V2<float> a_rotation);
	void setColour(float r, float g, float b);
	void setTailSpotColour(float r, float g, float b);
	void addEntity(Entity* a_entity);
};

