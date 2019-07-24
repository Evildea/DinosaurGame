#include "T2.h"



T2::T2()
{
}


T2::~T2()
{
}

void T2::update(M3<float> a_transform, V2<float> a_target, float a_speed, float a_minDistance, float deltaTime)
{
	// Update the target position only if it's moving.
	if (a_target.x != 0 && a_target.y != 0)
	{
		V2<float> current = m_transform;
		V2<float> force, resultant_force;

		force = (a_target - current).getNormalised() * a_speed;
		resultant_force = force - m_velocity;

		m_velocity = m_velocity + resultant_force * deltaTime;
		m_transform = m_transform + m_velocity * deltaTime;

		// This ensures that the visual target can't get too close to its owner.
		// If it gets too close this will create a snapping head movement.
		// We don't want that to happen.

		float xdif = m_avoid.x - m_transform.x;
		float ydif = m_avoid.y - m_transform.y;
		float dif = sqrt(xdif * xdif + ydif * ydif);

		if (dif < a_minDistance)
		{
			M3<float> facing;
			facing.rotate(m_avoid, m_transform, false);
			facing.yAxis = facing.yAxis * a_minDistance;
			m_transform = m_avoid + facing.yAxis;
		}
	}
}

void T2::draw(aie::Renderer2D * a_renderer, float r, float g, float b)
{
	// This draws the target. It's only used for debugging purposes.
	if (g_DEBUGMODE == true)
	{
		a_renderer->setRenderColour(r, g, b);
		a_renderer->drawCircle(m_transform.x, m_transform.y, 5);
	}
}

V2<float> T2::getPosition()
{
	return m_transform;
}

void T2::setPosition(V2<float> a_position)
{
	m_transform = a_position;
}

void T2::updateAvoid(V2<float> a_avoid)
{
	m_avoid = a_avoid;
}
