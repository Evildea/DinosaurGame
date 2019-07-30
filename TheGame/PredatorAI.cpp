#include "PredatorAI.h"
#include "AbstractObject.h"
#include "ObjectManager.h"
#include "Tile.h"

PredatorAI::PredatorAI()
{
	m_type = 'p';
	m_state = START;
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

	// Start State
	if (m_state == START)
	{
		targetX				= m_owner->getX();
		targetY				= m_owner->getY();

		// If thirst is less than 60%.
		if (m_owner->getThirst() < 60)
		{
			// Create a path to the closest Water Tile.
			targetTile = m_owner->getObjectManager()->getWaterTile(targetX, targetY);
			if (targetTile != nullptr)
			{
				if (!targetTile->getColide())
				{
					createPath(m_path, targetTile->getX(), targetTile->getY());
					m_state = SEEK_WATER;
					timer = 0.0f;
				}
			}
		}

		// If Hunger is less than 80%.
		if (m_owner->getHunger() < 80 && m_state == START)
		{
			// Either find a new Herbivore or Target the pre-existing Herbivore.
			Entity* targetHerbi;
			if (m_herbi == nullptr)
				targetHerbi = m_owner->getObjectManager()->getClosestEntity(HerbiControlledAI, targetX, targetY, dynamic_cast<Entity*>(m_owner));
			else
				targetHerbi = m_owner->getObjectManager()->getClosestEntity(HerbiControlledAI, m_herbi->getX(), m_herbi->getY(), dynamic_cast<Entity*>(m_owner));

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
					clampPosition(huntDirection.x, huntDirection.y);

					// Create a path to the closest Tile in the hunt direction.
					targetTile = m_owner->getObjectManager()->getTileAtPosition(huntDirection.x, huntDirection.y);
					if (targetTile != nullptr)
					{
						if (!targetTile->getColide())
						{
							createPath(m_path, targetTile->getX(), targetTile->getY());
							m_herbi = targetHerbi;
							m_state = HUNT_HERBI;
						}
					}
				}
			}
		}

		// If it feels like taking a nap.
		if (m_state == START && (rand() % 100) < 5 && m_owner->getHunger() > 80)
		{
			targetX = targetX + rand() % 1000 - rand() % 1000;
			targetY = targetY + rand() % 1000 - rand() % 1000;
			clampPosition(targetX, targetY);

			targetTile = m_owner->getObjectManager()->getTileAtPosition(targetX, targetY);

			if (targetTile != nullptr)
			{
				if (!targetTile->getColide())
				{
					createPath(m_path, targetTile->getX(), targetTile->getY());
					m_state = SLEEP;
				}
			}
		}

		// If all else fails pick a random target.
		if (m_state == START)
		{
			targetX = targetX + rand() % 1000 - rand() % 1000;
			targetY = targetY + rand() % 1000 - rand() % 1000;
			clampPosition(targetX, targetY);

			// Create a path to the randomly selected Tile.
			targetTile = m_owner->getObjectManager()->getTileAtPosition(targetX, targetY);
			if (targetTile != nullptr)
			{
				if (!targetTile->getColide())
				{
					createPath(m_path, targetTile->getX(), targetTile->getY());
					m_state = SEEK_RANDOM;
				}
			}
		}

	}


	// Seek Random Target state.
	if (m_state == SEEK_RANDOM)
	{
		if (m_path.size() == 1)
			m_state = START;
		else
			followPath(m_path, deltaTime);
	}

	// Sleep state.
	if (m_state == SLEEP)
	{
		timer += deltaTime;
		if (m_path.size() >= 1)
			followPath(m_path, deltaTime);

		if (timer > 10)
			m_state = START;
	}

	// Seek target state.
	if (m_state == HUNT_HERBI)
	{
		if (m_path.size() == 1)
			m_state = START;
		else
			followPath(m_path, deltaTime);

		// Check if the prey is still alive.
		if (m_herbi == nullptr)
			m_state = START;
		else
		{
			// Check if the prey is within range to attack.
			V2<float> dif = m_owner->getPosition() - m_herbi->getPosition();
			if (dif.getMagnitude() <= 75)
			{
				m_herbi->setHealth(m_herbi->getHealth() - 5);
				m_owner->setHunger(m_owner->getHunger() + 5);
			}
		}
	}

	// Seek Water state.
	if (m_state == SEEK_WATER)
	{
		if (m_path.size() == 1)
			m_state = DRINK;
		else
			followPath(m_path, deltaTime);
	}

	// Drink Water state.
	if (m_state == DRINK)
	{
		timer += deltaTime;
		followPath(m_path, deltaTime);

		if (timer > 10)
		{
			m_owner->setThirst(100);
			timer = 0.0f;
			m_state = START;
		}
	}

}
