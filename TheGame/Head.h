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
	ObjectManager*	m_objectManager;	// This represents the objectManager and enables the head to access its functions.
	aie::Texture*	m_sprite;			// This represents the sprite used by the head.
	M3<float>		m_position;			// This represents the position of the head in 2D space.
	V2<float>		m_offset;			// This represents a physical offset of the head from the body.
	V2<float>		m_eyeOffset;		// This represents a physical offset of the eyeline from the body.
	T2*				m_target;			// This represents the visual target of the head's eyeline.

public:
	Head();
	~Head();

	// This function updates the dinosaur's head every frame.
	void update(M3<float> a_positionAndtransform, float a_radians, V2<float> a_target, float deltaTime);

	// This function draws the dinosaur's head.
	void draw(aie::Renderer2D * a_renderer, V2<float> a_rotation);

	// This function applies a sprite to the dinosaur's head.
	void addSprite(ResourceManager* a_resourceManager, char a_spriteGameName[]);

	// This function enables the dinosaur's head to access the objectManager.
	void addObjectManager(ObjectManager* a_objectManager);
};

