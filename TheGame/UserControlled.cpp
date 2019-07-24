#include "UserControlled.h"
#include "ObjectManager.h"
#include "UserControlled.h"
#include "AbstractObject.h"
#include "Tile.h"

UserControlled::UserControlled()
{
	m_type = 'u';
	m_targetSet = false;
}

UserControlled::~UserControlled()
{
}

void UserControlled::update(float deltaTime, V2<int> a_cameraPosition)
{
	aie::Input* input = aie::Input::getInstance();
	
	// Generate an initial path if there is none.
	while (!m_targetSet)
	{
		int randomX = (rand() % g_MAPWIDTH) * 100;
		int randomY = (rand() % g_MAPHEIGHT) * 100;
		Tile * targetTile;
		targetTile = m_owner->getObjectManager()->getTileAtPosition(randomX, randomY);

		if (!targetTile->getColide())
			m_targetSet = CreatePath(m_path, targetTile->getX(), targetTile->getY());
	}

	// Create a path from the dinosaur's current position to its target.
	if (input->wasMouseButtonReleased(aie::INPUT_MOUSE_BUTTON_RIGHT))
		m_targetSet = CreatePath(m_path, input->getMouseX() + a_cameraPosition.x, input->getMouseY() + a_cameraPosition.y);

	// Follow the path.
	if (m_targetSet)
		FollowPath(m_path, deltaTime);
	
}
