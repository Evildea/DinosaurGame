#pragma once
#include "Renderer2D.h"
#include "Global.h"
#include "V2.h"

class Entity;

// This represents an individual segment of the dinosaur's tail.
struct Spine
{
	float x, y;
	float radius;
};

class Tail
{
private:
	Spine m_tailList[m_TAILLENGTH + 1];	// This represents each segment of the dinosaur's tail.
	float r, g, b, r1, g1, b1;			// This represents the colours of the tail and it's spot.
	int m_tailSpotDistance;				// This represents how far apart the tail spots should be.
	Entity*	m_owner;					// This represents the body that controls these tail.

public:
	Tail();
	~Tail();

	// This function updates the dinosaur's tail every frame.
	void update(V2<float> a_position);

	// This function draws the dinosaur's tail.
	void draw(aie::Renderer2D * a_renderer, V2<float> a_rotation);

	// This function sets the colour of the dinosaur's tail.
	void setColour(float r, float g, float b);

	// This function sets the colour of the spots on the dinosaur's tail.
	void setTailSpotColour(float r, float g, float b);

	// This functions tells the tail whose body they belong to.
	void addEntity(Entity* a_entity);
};

