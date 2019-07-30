#include "HerbiAI.h"
#include "AbstractObject.h"
#include "ObjectManager.h"
#include "Tile.h"


HerbiAI::HerbiAI()
{
	m_type = 'h';
	m_state = START;
	timer = 0.0f;
}


HerbiAI::~HerbiAI()
{
}

void HerbiAI::update(float deltaTime, V2<int> a_cameraPosition)
{
	int targetX = m_owner->getX();
	int targetY = m_owner->getY();
	clampPosition(targetX, targetY);

	Tile * targetTile;

	// If the herbivore sees a predator nearby flee from it.
	if (m_state != FLEE)
	{
		Entity* targetPredator = m_owner->getObjectManager()->getClosestEntity(PredatorControlledAI, targetX, targetY, dynamic_cast<Entity*>(m_owner));
		if (targetPredator != nullptr)
		{
			// Avoid any predators nearby.
			V2<float> distance = m_owner->getPosition() - targetPredator->getPosition();
			if (distance.getMagnitude() < m_HERBIVIEWDISTANCE)
			{
				// Set Flee direction to the oposite direction of the predator's velocity
				V2<float> fleeDirection = { (float)targetX - (targetPredator->getX() - targetPredator->getVelocity().x), (float)targetY - (targetPredator->getY() - targetPredator->getVelocity().y) };
				fleeDirection = fleeDirection.getNormalised() * 300;
				fleeDirection = fleeDirection + m_owner->getPosition();

				// Create a path to the closest Tile in the Flee direction.
				FleeFrom(fleeDirection.x, fleeDirection.y);
				FleeFrom(fleeDirection.x - 100, fleeDirection.y);
				FleeFrom(fleeDirection.x + 100, fleeDirection.y);
				FleeFrom(fleeDirection.x, fleeDirection.y - 100);
				FleeFrom(fleeDirection.x, fleeDirection.y + 100);

			}
		}
	}

	// Sleep State.
	if (m_state == START)
	{
		// If thirsty pick a water hole near the target.
		if (m_owner->getThirst() < 60 && m_state == START)
		{
			// Create a path to the closest Water Tile.
			targetTile = m_owner->getObjectManager()->getWaterTile(targetX, targetY);
			if (!targetTile->getColide())
			{
				createPath(m_path, targetTile->getX(), targetTile->getY());
				m_state = SEEK_WATER;
				timer = 0.0f;
			}
		}

		// If hungry pick a random tree near the target.
		if (m_owner->getHunger() < 80 && m_state == START)
		{
			// Create a path to the closest Tile under a Tree.
			targetTile = m_owner->getObjectManager()->getTree(targetX, targetY);
			if (!targetTile->getColide())
			{
				createPath(m_path, targetTile->getX(), targetTile->getY());
				m_state = SEEK_TREE;
				timer = 0.0f;
			}
		}

		// If all else fails pick a random target.
		if (m_state == START)
		{
			targetX = (rand() % g_MAPWIDTH) * 100;
			targetY = (rand() % g_MAPHEIGHT) * 100;

			// Create a path to the randomly selected Tile.
			targetTile = m_owner->getObjectManager()->getTileAtPosition(targetX, targetY);
			if (!targetTile->getColide())
			{
				createPath(m_path, targetTile->getX(), targetTile->getY());
				m_state = SEEK_RANDOM;
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

		if (m_owner->getThirst() < 30 || m_owner->getHunger() < 30)
			m_state = START;
	}

	// Flee target state.
	if (m_state == FLEE)
	{
		if (m_path.size() == 1)
			m_state = START;
		else
			followPath(m_path, deltaTime);
	}

	// Seek Water state.
	if (m_state == SEEK_WATER)
	{
		if (m_path.size() == 1)
			m_state = DRINK;
		else
			followPath(m_path, deltaTime);
	}

	// Seek Tree state.
	if (m_state == SEEK_TREE)
	{
		if (m_path.size() == 1)
			m_state = EAT;
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

	// Eat state.
	if (m_state == EAT)
	{
		timer += deltaTime;
		followPath(m_path, deltaTime);

		if (timer > 10)
		{
			m_owner->setHunger(100);
			timer = 0.0f;
			m_state = START;
		}
	}
}

void HerbiAI::FleeFrom(float x, float y)
{
	if (m_state != FLEE)
	{
		clampPosition(x, y);
		Tile* targetTile = m_owner->getObjectManager()->getTileAtPosition(x, y);
		if (targetTile != nullptr)
		{
			if (!targetTile->getColide())
			{
				createPath(m_path, targetTile->getX(), targetTile->getY());
				m_state = FLEE;
			}
		}
	}
}
