#include "HerbiAI.h"
#include "AbstractObject.h"
#include "ObjectManager.h"
#include "Tile.h"


HerbiAI::HerbiAI()
{
	m_type = 'h';
	m_state = SLEEP;
	timer = 0.0f;
}


HerbiAI::~HerbiAI()
{
}

void HerbiAI::update(float deltaTime, V2<int> a_cameraPosition)
{
	int targetX, targetY;
	Tile * targetTile;

	// Sleep State.
	if (m_state == SLEEP)
		m_state = PICKTARGET;


	// If the herbivore sees a predator nearby flee from it.
	if (m_state != FLEETARGET)
	{
		targetX = m_owner->getX();
		targetY = m_owner->getY();
		Entity* targetPredator = m_owner->getObjectManager()->getClosestEntity(PredatorControlledAI, targetX, targetY, dynamic_cast<Entity*>(m_owner));

		if (targetPredator != nullptr)
		{
			// Avoid any predators nearby.
			V2<float> distance = m_owner->getPosition() - targetPredator->getPosition();
			if (distance.getMagnitude() < m_HERBIVIEWDISTANCE)
			{
				// Set Flee direction to the oposite direction of the predator's velocity
				V2<float> fleeDirection = { (float)targetX - (targetPredator->getX() - targetPredator->getVelocity().x), (float)targetY - (targetPredator->getY() - targetPredator->getVelocity().x) };
				fleeDirection = fleeDirection.getNormalised() * 300;
				fleeDirection = fleeDirection + m_owner->getPosition();

				// Ensure the Flee direction is on the map.
				ClampCoordinates(fleeDirection.x, fleeDirection.y);

				// Create a path to the closest Tile in the Flee direction.
				targetTile = m_owner->getObjectManager()->getTileAtPosition(fleeDirection.x, fleeDirection.y);
				if (targetTile != nullptr)
				{
					if (!targetTile->getColide())
					{
						CreatePath(m_path, targetTile->getX(), targetTile->getY());
						m_state = FLEETARGET;
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

		// If hungry pick a random tree near the target.
		if (m_owner->getHunger() < 60 && pickedTarget == false)
		{
			targetX = m_owner->getX();
			targetY = m_owner->getY();
			ClampCoordinates(targetX, targetY);

			// Create a path to the closest Tile under a Tree.
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

	// Flee target state.
	if (m_state == FLEETARGET)
	{
		if (m_path.size() == 1)
			m_state = PICKTARGET;
		else
			FollowPath(m_path, deltaTime);
	}

	// Seek Water state.
	if (m_state == SEEKWATER)
	{
		if (m_path.size() == 1)
			m_state = DRINK;
		else
			FollowPath(m_path, deltaTime);
	}

	// Seek Tree state.
	if (m_state == SEEKTREE)
	{
		if (m_path.size() == 1)
			m_state = EAT;
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

	// Eat state.
	if (m_state == EAT)
	{
		timer += deltaTime;
		FollowPath(m_path, deltaTime);

		if (timer > 10)
		{
			m_owner->setHunger(100);
			timer = 0.0f;
			m_state = PICKTARGET;
		}
	}
}
