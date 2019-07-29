#include "PredatorAI.h"
#include "AbstractObject.h"
#include "ObjectManager.h"
#include "Tile.h"

PredatorAI::PredatorAI()
{
	m_type = 'p';
	m_state = SLEEP;
	timer = 0.0f;
	m_herbi = nullptr;
}


PredatorAI::~PredatorAI()
{
}

void PredatorAI::update(float deltaTime, V2<int> a_cameraPosition)
{
	int targetX, targetY;
	Tile * targetTile;

	// Sleep State.
	if (m_state == SLEEP)
		m_state = PICKTARGET;


	// If the predator is hungry and it sees a prey nearby hunt it.
	if (m_state != SEEKPREY && m_owner->getHunger() < 70 && m_owner->getThirst() > 30)
	{
		targetX = m_owner->getX();
		targetY = m_owner->getY();
		Entity* targetHerbi = m_owner->getObjectManager()->getClosestEntity(HerbiControlledAI, targetX, targetY, dynamic_cast<Entity*>(m_owner));

		if (targetHerbi != nullptr)
		{
			// Hunt any prey nearby.
			V2<float> distance = m_owner->getPosition() - targetHerbi->getPosition();
			if (distance.getMagnitude() < m_PREDATORVIEWDISTANCE)
			{
				// Set the hunt direction to the direction of the prey's velocity
				V2<float> huntDirection = { (targetHerbi->getX() - targetHerbi->getVelocity().x) - (float)targetX, (targetHerbi->getY() - targetHerbi->getVelocity().x) - (float)targetY };
				huntDirection = huntDirection.getNormalised() * 200;
				huntDirection = huntDirection + m_owner->getPosition();

				// Ensure that the hunt direction is on the map.
				ClampCoordinates(huntDirection.x, huntDirection.y);

				// Create a path to the closest Tile in the hunt direction.
				targetTile = m_owner->getObjectManager()->getTileAtPosition(huntDirection.x, huntDirection.y);
				if (targetTile != nullptr)
				{
					if (!targetTile->getColide())
					{
						CreatePath(m_path, targetTile->getX(), targetTile->getY());
						m_herbi = targetHerbi;
						m_state = SEEKPREY;
					}
				}
			}
		}
	}


	// Pick a Target state.
	while (m_state == PICKTARGET)
	{
		bool pickedTarget = false;
		timer = 0.0f;

		// If thirsty pick a water hole near the target.
		if (m_owner->getThirst() < 60 && pickedTarget == false)
		{
			targetX = m_owner->getX();
			targetY = m_owner->getY();
			ClampCoordinates(targetX, targetY);

			// Create a path to the closest Water Tile.
			targetTile = m_owner->getObjectManager()->getWaterTile(targetX, targetY);
			if (!targetTile->getColide())
			{
				CreatePath(m_path, targetTile->getX(), targetTile->getY());
				m_state = SEEKWATER;
				pickedTarget = true;
			}
		}

		// If all else fails pick a random target.
		if (pickedTarget == false)
		{
			targetX = (rand() % g_MAPWIDTH) * 100;
			targetY = (rand() % g_MAPHEIGHT) * 100;

			// Create a path to the randomly selected Tile.
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
		if (m_path.size() == 1)
			m_state = PICKTARGET;
		else
			FollowPath(m_path, deltaTime);

		if (m_owner->getThirst() < 30 || m_owner->getHunger() < 30)
			m_state = PICKTARGET;
	}

	// Seek target state.
	if (m_state == SEEKPREY)
	{
		if (m_path.size() == 1)
			m_state = PICKTARGET;
		else
			FollowPath(m_path, deltaTime);

		// Check if the prey is still alive.
		if (m_herbi == nullptr)
			m_state = PICKTARGET;

		else
		{
			// Check if the prey is within range to attack.
			V2<float> dif = m_owner->getPosition() - m_herbi->getPosition();
			if (dif.getMagnitude() <= 50)
			{
				m_herbi->setHealth(m_herbi->getHealth() - 1);
				m_owner->setHunger(m_owner->getHunger() + 1);
			}
		}
	}

	// Seek Water state.
	if (m_state == SEEKWATER)
	{
		if (m_path.size() == 1)
			m_state = DRINK;
		else
			FollowPath(m_path, deltaTime);
	}

	// Drink Water state.
	if (m_state == DRINK)
	{
		timer += deltaTime;
		FollowPath(m_path, deltaTime);

		if (timer > 10)
		{
			m_owner->setThirst(100);
			timer = 0.0f;
			m_state = PICKTARGET;
		}
	}

}
