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
				fleeDirection = fleeDirection.getNormalised() * 100;
				fleeDirection = fleeDirection + m_owner->getPosition();

				// Ensure the oposite direction is on the map.
				if (fleeDirection.x > g_MAPWIDTH * 100)
					fleeDirection.x = g_MAPWIDTH;
				if (fleeDirection.y > g_MAPHEIGHT * 100)
					fleeDirection.y = g_MAPHEIGHT;

				if (fleeDirection.x < 0)
					fleeDirection.x = 0;
				if (fleeDirection.y < 0)
					fleeDirection.y = 0;

				// Create a path to a Tile 300 pixels in the opposite direction to the predator.
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
		if (m_owner->getThirst() < 30 && pickedTarget == false)
		{
			targetX = m_owner->getX();
			targetY = m_owner->getY();

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
			targetX = m_owner->getX();
			targetY = m_owner->getY();

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

	// Flee target state.
	if (m_state == FLEETARGET)
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
