#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "M3.h"
#include "T2.h"

class ObjectManager;
class ResourceManager;

class Head
{
private:
	ObjectManager*	m_objectManager;
	aie::Texture*	m_sprite;			// This represents the sprite used by the head.
	M3<float>		m_position;			// This represents the position of the head in 2D space.
	V2<float>		m_offset;			// This represents a physical offset of the head from the body.
	V2<float>		m_eyeOffset;		// This represents a physical offset of the eyeline from the body.
	T2*				m_target;			// This represents the visual target of the head's eyeline.

public:
	Head();
	~Head();

	void update(M3<float> a_positionAndtransform, float a_radians, V2<float> a_target, float deltaTime);
	void draw(aie::Renderer2D * a_renderer, V2<float> a_rotation);
	void addSprite(ResourceManager* a_resourceManager, char a_textureGameName[]);
	void addObjectManager(ObjectManager* a_objectManager);
};

