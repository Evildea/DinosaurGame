#pragma once
#include "ResourceManager.h"
#include "Renderer2D.h"
#include "Texture.h"
#include "M3.h"

enum Walk {LEFTWARD, RIGHTWARD};
class Entity;

class Legs
{
private:
	aie::Texture*	m_sprite;			// This represents the sprite used by the legs.
	M3<float>		m_position;			// This represents the position of the legs in 2D space.
	float			m_offset;			// This represents the offset of the legs regards to the body.
	Entity*			m_owner;			// This represents the body that controls these legs.
	Walk			m_walkingRotation;	// This represents what way to swing the legs.

public:
	Legs();
	~Legs();

	// This function updates the dinosaur's legs every frame.
	void update(M3<float> a_positionAndtransform, float a_radians);

	// This function draws the dinosaur's legs.
	void draw(aie::Renderer2D * a_renderer, V2<float> a_rotation);

	// This function applies a sprite to the dinosaur's legs.
	void addSprite(ResourceManager* a_resourceManager, char a_spriteGameName[]);

	// This functions tells the legs whose body they belong to.
	void addEntity(Entity* a_entity);

};

