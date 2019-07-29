#include "Tail.h"
#include "Entity.h"

Tail::Tail()
{
	r = g = b = 1.0f;
	m_tailSpotDistance = m_TAILLENGTH * 0.1;
	for (int i = 0; i < m_TAILLENGTH; i++)
	{
		m_tailList[i].radius = (1 + i) / m_tailSpotDistance;
		if (m_tailList[i].radius > 8.0)
			m_tailList[i].radius = 8.0;
	}
}

Tail::~Tail()
{
}

void Tail::update(V2<float> a_position)
{
	// Update the tail's spinal position if the body of the dinosaur is moving.
	float distanceTravelled = m_owner->getDistanceTravelled();
	if (distanceTravelled > 3.0)
	{
		for (int i = 0; i < m_TAILLENGTH; i++)
		{
			if (m_tailList[i].x != m_tailList[i + 1].x && m_tailList[i].y != m_tailList[i + 1].y)
			{
				m_tailList[i].x = m_tailList[i + 1].x;
				m_tailList[i].y = m_tailList[i + 1].y;
			}
		}
		m_tailList[m_TAILLENGTH].x = a_position.x;
		m_tailList[m_TAILLENGTH].y = a_position.y;
	}
}

void Tail::draw(aie::Renderer2D * a_renderer, V2<float> a_rotation)
{
	// Rotate the tail starting position based on the body rotation.
	V2<float> tailPosition = a_rotation;
	tailPosition.x = -tailPosition.x;
	tailPosition.y = -tailPosition.y;

	// The tail spot represents the halfway point between the computed tail spots and the sprite.
	V2<float> tailSpot = tailPosition * (m_TAILLENGTH / 1.9);

	// The tail position represents the starting point of the computed tail spots.
	tailPosition = tailPosition * 35;

	// Draw the tail pieces (skeleton).
	a_renderer->setRenderColour(r, g, b);
	for (int i = 1; i < m_TAILLENGTH; i++)
		a_renderer->drawCircle(tailPosition.x + m_tailList[i].x, tailPosition.y + m_tailList[i].y, (m_tailList[i].radius <= 1.5) ? 1.5 : m_tailList[i].radius, 0.3 );

	// Draw the tail spots (skin).
	a_renderer->setRenderColour(r1, g1, b1);
	a_renderer->drawCircle(tailSpot.x + m_tailList[m_TAILLENGTH].x, tailSpot.y + m_tailList[m_TAILLENGTH].y, 2.1, 0.3);
	for (int i = 1; i < m_TAILLENGTH / m_tailSpotDistance; i++)
		a_renderer->drawCircle(tailPosition.x + m_tailList[i * m_tailSpotDistance].x, tailPosition.y + m_tailList[i * m_tailSpotDistance].y, (m_tailList[i * m_tailSpotDistance].radius / 4 >= 1.5) ? m_tailList[i * m_tailSpotDistance].radius / 4 : 1.5);

	// Reset the render colour.
	a_renderer->setRenderColour(1, 1, 1);
}

void Tail::setColour(float _r, float _g, float _b)
{
	r = _r / 255;
	g = _g / 255;
	b = _b / 255;
}

void Tail::setTailSpotColour(float _r, float _g, float _b)
{
	r1 = _r / 255;
	g1 = _g / 255;
	b1 = _b / 255;
}

void Tail::addEntity(Entity * a_entity)
{
	m_owner = a_entity;
}
