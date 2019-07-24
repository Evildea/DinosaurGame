#include "ObjectManager.h"
#include "AbstractObject.h"

AbstractObject::AbstractObject()
{
	m_behaviourManager	= new BehaviourManager;
	m_selectedStatus	= false;
	m_velocity			= { 0.0f,0.0f };
	m_depth				= 0.0f;
}


AbstractObject::~AbstractObject()
{
	delete m_behaviourManager;
}

void AbstractObject::update(float deltaTime, V2<int> a_cameraPosition)
{
	m_behaviourManager->update(deltaTime, a_cameraPosition);

	// Perform any custom updates
	customUpdate(deltaTime);
}

void AbstractObject::draw(aie::Renderer2D * a_renderer)
{
	// Draw the bounding box around the object if it's selected.
	if (m_selectedStatus)
	{
		a_renderer->setRenderColour(1, 0, 0, 0.5);
		a_renderer->drawBox(getX(), getY(), m_sprite->getWidth() + 10, m_sprite->getHeight() + 10, getT(), 0.5);
	}

	// Draw the sprite of the object translated and transformed accordingly.
	M3<float> t;
	t = m_transform + m_position;

	a_renderer->setRenderColour(1, 1, 1, 1);
	a_renderer->drawSpriteTransformed3x3(m_sprite, (float*)t, m_sprite->getWidth(), m_sprite->getHeight(), m_depth);

	// Draw any custom draw functions.
	customDraw(a_renderer);
}

void AbstractObject::addSprite(ResourceManager * a_resourceManager, char a_textureGameName[])
{
	m_sprite = a_resourceManager->getTexture(a_textureGameName);
}

void AbstractObject::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void AbstractObject::setVelocity(float x, float y)
{
	m_velocity = { x, y };
}

void AbstractObject::setTarget(V2<float> a_target)
{
	m_target = a_target;
}

V2<float> AbstractObject::getPosition()
{
	return m_position;
}

M3<float> AbstractObject::getTransform()
{
	return m_transform;
}

V2<float> AbstractObject::getVelocity()
{
	return m_velocity;
}

float AbstractObject::getX()
{
	return m_position.x;
}

float AbstractObject::getY()
{
	return m_position.y;
}

float AbstractObject::getT()
{
	return m_transform.getRadians();
}

void AbstractObject::setObjectManager(ObjectManager * a_objectManager)
{
	m_objectManager = a_objectManager;
}

ObjectManager * AbstractObject::getObjectManager()
{
	return m_objectManager;
}
