#include "Legs.h"
#include "Entity.h"

Legs::Legs()
{
	m_offset = 0.0f;
	m_walkingRotation = LEFTWARD;
}

Legs::~Legs()
{
}

void Legs::update(M3<float> a_positionAndtransform, float a_radians)
{
	// Update the position and rotation of the legs.
	m_position = a_positionAndtransform;

	// Calculate the rotation speed based on the dinosaur's speed.
	float distanceTravelled = m_owner->getDistanceTravelled() / (m_DINOSAURSPEED * 8);

	// Swing the legs left or right to create the illusion of movement.
	if (m_walkingRotation == LEFTWARD)
	{
		m_offset -= distanceTravelled;
		if (m_offset < -0.4f)
			m_walkingRotation = RIGHTWARD;
	}

	if (m_walkingRotation == RIGHTWARD)
	{
		m_offset += distanceTravelled;
		if (m_offset > 0.4f)
			m_walkingRotation = LEFTWARD;
	}

	// Rotate the legs.
	m_position.rotate(a_radians + m_offset);

}

void Legs::draw(aie::Renderer2D * a_renderer, V2<float> a_rotation)
{
	a_renderer->setRenderColour(1, 1, 1, 1);
	a_renderer->drawSpriteTransformed3x3(m_sprite, (float*)m_position, m_sprite->getWidth(), m_sprite->getHeight(), 0.4f);
}

void Legs::addSprite(ResourceManager * a_resourceManager, char a_spriteGameName[])
{
	m_sprite = a_resourceManager->getSprite(a_spriteGameName);
}

void Legs::addEntity(Entity * a_entity)
{
	m_owner = a_entity;
}
