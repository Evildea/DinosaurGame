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
	aie::Texture*	m_sprite;	// This represents the sprite used by the legs.
	M3<float>		m_position;	// This represents the position of the legs in 2D space.
	float			m_offset;	// This represents the offset of the legs regards to the body.
	Entity*			m_owner;	// This represents the body that controls these legs.
	Walk			m_walkingRotation;

public:
	Legs();
	~Legs();

	void update(M3<float> a_positionAndtransform, float a_radians);
	void draw(aie::Renderer2D * a_renderer, V2<float> a_rotation);
	void addSprite(ResourceManager* a_resourceManager, char a_textureGameName[]);
	void addEntity(Entity* a_entity);

};

