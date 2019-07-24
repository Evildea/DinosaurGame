#include "PredatorAI.h"
#include "AbstractObject.h"
#include "ObjectManager.h"
#include "Tile.h"

PredatorAI::PredatorAI()
{
	m_type = 'p';
	m_state = SLEEP;
	timer = 0.0f;
}


PredatorAI::~PredatorAI()
{
}

void PredatorAI::update(float deltaTime, V2<int> a_cameraPosition)
{
	// Sleep State.
	if (m_state == SLEEP)
		m_state = PICKTARGET;

	// Pick a Target state.
	while (m_state == PICKTARGET)
	{
		Tile * targetTile;
		int targetX, targetY;
		bool pickedTarget = false;
		timer = 0.0f;

		// If thirsty pick a water hole near the target.
		if (m_owner->getThirst() < 30)
		{
			targetX = m_owner->getX() + (rand() % 3) * 100;
			targetY = m_owner->getY() + (rand() % 3) * 100;

			if (targetX > g_MAPWIDTH * 100)
				targetX = g_MAPWIDTH;
			if (targetY > g_MAPHEIGHT * 100)
				targetY = g_MAPHEIGHT;

			targetTile = m_owner->getObjectManager()->getWaterTile(targetX, targetY);
			if (!targetTile->getColide())
			{
				CreatePath(m_path, targetTile->getX(), targetTile->getY());
				m_state = SEEKWATER;
				pickedTarget = true;
			}
		}

		// If hungry pick a random tree near the target.
		if (m_owner->getHunger() < 30 && pickedTarget == false)
		{
			targetX = m_owner->getX() + (rand() % 3) * 100;
			targetY = m_owner->getY() + (rand() % 3) * 100;

			if (targetX > g_MAPWIDTH * 100)
				targetX = g_MAPWIDTH;
			if (targetY > g_MAPHEIGHT * 100)
				targetY = g_MAPHEIGHT;

			targetTile = m_owner->getObjectManager()->getTree(targetX, targetY);

			if (!targetTile->getColide())
			{
				CreatePath(m_path, targetTile->getX(), targetTile->getY());
				m_state = SEEKTREE;
				pickedTarget = true;
			}
		}

		// If all else fails pick a random target.
		if (pickedTarget == false)
		{
			targetX = (rand() % g_MAPWIDTH) * 100;
			targetY = (rand() % g_MAPHEIGHT) * 100;
			targetTile = m_owner->getObjectManager()->getTileAtPosition(targetX, targetY);
			if (!targetTile->getColide())
			{
				CreatePath(m_path, targetTile->getX(), targetTile->getY());
				m_state = SEEKRANDOMTARGET;
			}
		}
	}


	// Seek Random Target state.
	if (m_state == SEEKRANDOMTARGET)
	{
		if (m_path.size() != 0)
			FollowPath(m_path, deltaTime);
		else
			m_state = PICKTARGET;
	}

	// Seek Water state.
	if (m_state == SEEKWATER)
	{
		if (m_path.size() != 0)
			FollowPath(m_path, deltaTime);
		else
			m_state = DRINK;
	}

	// Seek Tree state.
	if (m_state == SEEKTREE)
	{
		if (m_path.size() != 0)
			FollowPath(m_path, deltaTime);
		else
			m_state = EAT;
	}

	// Drink Water state.
	if (m_state == DRINK)
	{
		m_owner->setVelocity(0, 0);
		timer += deltaTime;

		if (timer > 10)
		{
			m_owner->setThirst(100);
			timer = 0.0f;
			m_state = PICKTARGET;
		}
	}

	// Eat state.
	if (m_state == EAT)
	{
		m_owner->setVelocity(0, 0);
		timer += deltaTime;

		if (timer > 10)
		{
			m_owner->setHunger(100);
			timer = 0.0f;
			m_state = PICKTARGET;
		}
	}

	// Create a new Path if at the end of the Path.
	if (m_path.size() == 1)
		m_state = PICKTARGET;

}
