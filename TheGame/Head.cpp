#include "Head.h"
#include "ObjectManager.h"
#include "ResourceManager.h"

Head::Head()
{
	m_target = DBG_NEW T2;
}

Head::~Head()
{
	delete m_target;
}

void Head::update(M3<float> a_positionAndtransform, float a_radians, V2<float> a_target, float deltaTime)
{
	// Update the position and rotation of the head.
	m_position = a_positionAndtransform;

	// Offset the Head to its correct position on the body.
	m_offset = m_position.yAxis * 40;
	m_position.zAxis += m_offset;

	// Offset the eyeline to its correct position off the body.
	m_eyeOffset = m_position.yAxis * 115;

	// Reset the head's visual eyeline to in front of itself the first time it ever loads.
	m_target->setPosition(m_position.zAxis + m_offset);

	// Move the head's eyeline towards its visual target.
	m_target->update(a_positionAndtransform, a_target, 100000, 100, deltaTime);
	m_target->updateAvoid(a_positionAndtransform.zAxis);

	// Restrict the eyeline so it can't move more than 100 pixels from the base of the eyeline's starting point.
	V2<float> prePosition = m_position.zAxis + m_eyeOffset;
	V2<float> difference = m_target->getPosition() - prePosition;
	float dif = sqrt(difference.x * difference.x + difference.y * difference.y);
	if (dif > 100)
	{
		difference = difference.getNormalised() * 100;
		m_target->setPosition(prePosition + difference);
	}

	// Rotate the head towards it's eyeline.
	m_position.rotate(m_position.zAxis, m_target->getPosition(), false);

}

void Head::draw(aie::Renderer2D * a_renderer, V2<float> a_rotation)
{
	// Draw the head.
	a_renderer->setRenderColour(1, 1, 1, 1);
	a_renderer->drawSpriteTransformed3x3(m_sprite, (float*)m_position, 0, 0, .3);
	
	// Draw the target (if in debug mode).
	m_target->draw(a_renderer, 1, 0, 0);
}

void Head::addSprite(ResourceManager * a_resourceManager, char a_textureGameName[])
{
	m_sprite = a_resourceManager->getTexture(a_textureGameName);
}

void Head::addObjectManager(ObjectManager * a_objectManager)
{
	m_objectManager = a_objectManager;
}
