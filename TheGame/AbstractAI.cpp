#include "AbstractAI.h"
#include "ObjectManager.h"
#include "UserControlled.h"
#include "AbstractObject.h"
#include "Tile.h"

AbstractAI::AbstractAI()
{
	m_owner = nullptr;
}


AbstractAI::~AbstractAI()
{
}

void AbstractAI::draw(aie::Renderer2D * a_renderer)
{
}

bool AbstractAI::CreatePath(std::vector<Tile*> &a_path, float a_targetX, float a_targetY)
{
	// Clear the current path.
	a_path.clear();

	// Generate a route from the current position to the target position.
	m_owner->getObjectManager()->CreateRoute(m_owner->getX(), m_owner->getY(), a_targetX, a_targetY, a_path);
	
	// Check if a valid path has been created.
	if (a_path.size() != 0)
		return true;
	else
		return false;
}

void AbstractAI::FollowPath(std::vector<Tile*> &a_path, float deltaTime)
{
	V2<float> TargetPosition;

	// Point the dinosaur towards the first target in the path.
	TargetPosition = a_path[0]->getPosition();
	float xdif = TargetPosition.x - m_owner->getX();
	float ydif = TargetPosition.y - m_owner->getY();
	float dif = sqrt(xdif * xdif + ydif * ydif);

	// If the dinosaur is within range of the first target, then point towards the second target.
	if (dif < 30 && a_path.size() > 1)
	{
		a_path.erase(a_path.begin());
		TargetPosition = a_path[0]->getPosition();
	}

	// Add a little wiggle to the movement of the dinosaur so it doesn't appear to be following a path exactly.
	TargetPosition.x = TargetPosition.x + rand() % 2 - rand() % 2;
	TargetPosition.y = TargetPosition.y + rand() % 2 - rand() % 2;

	// Turn the head of the dinosaur towards the next target in the path.
	if (a_path.size() > 2)
		m_owner->setTarget(a_path[1]->getPosition());
	else
		m_owner->setTarget(a_path[0]->getPosition());

	// Get the current position and velocity of the dinosaur.
	V2<float> current = m_owner->getPosition();
	V2<float> velocity = m_owner->getVelocity();

	// Calculate a seek force towards the target and distance from it.
	V2<float> force, resultantForce, desiredVelocity;
	desiredVelocity = TargetPosition - current;
	float distance = desiredVelocity.getMagnitude();

	// Apply the force amount based on how far the dinosaur is from its target.
	if (distance < m_DINOSAURSLOWINGRADIUS)
		force = desiredVelocity.getNormalised() * m_DINOSAURSPEED * (distance / m_DINOSAURSLOWINGRADIUS);
	else
		force = desiredVelocity.getNormalised() * m_DINOSAURSPEED;

	// Apply the overall resultant force.
	resultantForce = force - velocity;

	// Update the dinosaur's velocity.
	velocity = velocity + resultantForce * deltaTime;
	m_owner->setVelocity(velocity.x, velocity.y);
}

char AbstractAI::GetAIType()
{
	return m_type;
}
