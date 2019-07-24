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

	float distanceTravelled = m_owner->getVelocityLength() / (m_DINOSAURSPEED * 4);

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

	m_position.rotate(a_radians + m_offset);

}

void Legs::draw(aie::Renderer2D * a_renderer, V2<float> a_rotation)
{
	a_renderer->setRenderColour(1, 1, 1, 1);
	a_renderer->drawSpriteTransformed3x3(m_sprite, (float*)m_position, m_sprite->getWidth(), m_sprite->getHeight(), 0.4f);
}

void Legs::addSprite(ResourceManager * a_resourceManager, char a_textureGameName[])
{
	m_sprite = a_resourceManager->getTexture(a_textureGameName);
}

void Legs::addEntity(Entity * a_entity)
{
	m_owner = a_entity;
}