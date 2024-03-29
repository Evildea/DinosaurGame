#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
	// Delete all Tiles, Entities, Trees and Footsteps.
	for (Bones* i : m_bonesList)
		delete i;
	for (Entity* i : m_entityList)
		delete i;
	for (Tree* i : m_treeList)
		delete i;
	for (Tile* i : m_tileList)
		delete i;
}

void ObjectManager::update(float deltaTime, V2<int> a_cameraPosition)
{
	// Update all Tiles, Entities, Trees and Footsteps.
	for (Tile* i : m_tileList)
		i->update(deltaTime, a_cameraPosition);
	
	for (Entity* i : m_entityList)
	{
		if (i->getHealth() <= 5)
		{
			m_entityList.erase(std::find(m_entityList.begin(), m_entityList.end(), i));
			addBones("bones", i->getX(), i->getY());
			delete i;
		}
		else
			i->update(deltaTime, a_cameraPosition);
	}

	for (Tree* i : m_treeList)
		i->update(deltaTime, a_cameraPosition), i->setTransparency(1);

	for (Bones* i : m_bonesList)
		i->update(deltaTime, a_cameraPosition);

	// Update the transparency of the Trees based on the nearest dinosaur.
	for (Tree* i : m_treeList)
	{
		for (Entity* j : m_entityList)
		{
			float distance = sqrt(pow(j->getX() - i->getX(), 2) + pow(j->getY() - i->getY(), 2));
			if (distance < 100)
				i->setTransparency((1 - (50 / distance)) + .5);
		}
	}

}

void ObjectManager::draw(aie::Renderer2D * a_renderer)
{
	// Generate the Camera viewable area.
	float camX, camY, camX2, camY2;
	a_renderer->getCameraPos(camX, camY);
	camX -= 100;
	camY -= 100;
	camX2 = camX + 1500;
	camY2 = camY + 1000;

	// Draw all Tiles, Entities, Trees and Bones within the cameras viewing range.
	for (Tile* i : m_tileList)
		if (i->getPosition().x > camX && i->getPosition().y > camY && i->getPosition().x < camX2 && i->getPosition().y < camY2)
		i->draw(a_renderer);
	
	for (Entity* i : m_entityList)
		if (i->getPosition().x > camX && i->getPosition().y > camY && i->getPosition().x < camX2 && i->getPosition().y < camY2)
		i->draw(a_renderer);

	for (Tree* i : m_treeList)
		if (i->getPosition().x > camX && i->getPosition().y > camY && i->getPosition().x < camX2 && i->getPosition().y < camY2)
		i->draw(a_renderer);

	for (Bones* i : m_bonesList)
		if (i->getPosition().x > camX && i->getPosition().y > camY && i->getPosition().x < camX2 && i->getPosition().y < camY2)
		i->draw(a_renderer);
}

void ObjectManager::addResourceManager(ResourceManager * a_resourceManager)
{
	m_resourceManager = a_resourceManager;
}

void ObjectManager::addEntity(char a_spriteGameName[], char a_scarSpriteGameName[], BehaviourType a_dinosaurRole, float x, float y, float r, float g, float b, float r1, float g1, float b1)
{
	// Add a new Entity (dinosaur) to the game.
	m_entityList.push_back(DBG_NEW Entity);
	Entity* temp = m_entityList.back();

	temp->addSprite(m_resourceManager, a_spriteGameName);
	temp->addScarSprite(m_resourceManager, a_scarSpriteGameName);
	temp->setSpeciesType(a_dinosaurRole);
	temp->setPosition(x, y);
	temp->setTailColour(r, g, b);
	temp->setTailSpotColour(r1, g1, b1);
	temp->setObjectManager(this);
}

void ObjectManager::addTree(char a_spriteGameName[], float x, float y)
{
	// Add a new Tree to the game.
	m_treeList.push_back(DBG_NEW Tree);
	Tree* temp = m_treeList.back();

	temp->addSprite(m_resourceManager, a_spriteGameName);
	temp->setPosition(x, y);
}

void ObjectManager::addTile(CollisionType a_collision, char a_spriteGameName[], float x, float y)
{
	// Add a new Tile to the game.
	m_tileList.push_back(DBG_NEW Tile);
	Tile* temp = m_tileList.back();

	temp->addSprite(m_resourceManager, a_spriteGameName);
	temp->setPosition(x, y);
	temp->setCollisionType(a_collision);

	// If the new Tile is a water tile then add it to the water list.
	if (a_collision == WATER)
		m_waterTileList.push_back(temp);
}

void ObjectManager::addBones(char a_spriteGameName[], float x, float y)
{
	// Add a set of Footsteps to the game.
	m_bonesList.push_back(DBG_NEW Bones);
	Bones* temp = m_bonesList.back();

	temp->addSprite(m_resourceManager, a_spriteGameName);
	temp->setPosition(x, y);
}

void ObjectManager::addHead(char a_spriteGameName[])
{
	// Add a Head to the Entity.
	m_entityList.back()->getHead()->addSprite(m_resourceManager, a_spriteGameName);
}

void ObjectManager::addLegs(char a_spriteGameName[])
{
	// Add a pair of legs to the Entity.
	m_entityList.back()->getLegs()->addSprite(m_resourceManager, a_spriteGameName);
}

void ObjectManager::addFoliage(char a_spriteGameName[])
{
	// Add leaves to the Tree.
	m_treeList.back()->addFoliage(m_resourceManager, a_spriteGameName);
}

bool ObjectManager::setSelected(float x1, float y1, float x2, float y2)
{
	bool found = false;
	for (Entity* i : m_entityList)
	{
		// Set the object to selected if it is within the coordinates specified.
		if (i->getX() > x1 && i->getX() < x2 || i->getX() < x1 && i->getX() > x2)
		{
			if (i->getY() > y1 && i->getY() < y2 || i->getY() < y1 && i->getY() > y2)
				i->setMouseSelected(true), found = true;
		}
		else
			i->setMouseSelected(false);
	}
	return found;

}

void ObjectManager::linkTiles()
{
	for (Tile* i : m_tileList)
	{
		// Set the position to the (I)'s position.
		V2<float>	parentPosition = i->getPosition();
		Tile*		parentTile = i;

		if (parentTile->getColide() == false) {
			for (Tile * j : m_tileList)
			{
				if (j != parentTile)
				{
					// Set the child position to the (J)'s position.
					V2<float> childPosition = j->getPosition();

					// check one to the left of the current J.
					if (checkTileColide(j, parentPosition, childPosition.x - 100, childPosition.y))
						parentTile->addEdge(j, 100);

					// check one to the right of the current J.
					if (checkTileColide(j, parentPosition, childPosition.x + 100, childPosition.y))
						parentTile->addEdge(j, 100);

					// check one to the top of the current J.
					if (checkTileColide(j, parentPosition, childPosition.x, childPosition.y + 100))
						parentTile->addEdge(j, 100);

					// check one to the bottom of the current J.
					if (checkTileColide(j, parentPosition, childPosition.x, childPosition.y - 100))
						parentTile->addEdge(j, 100);

					// check one to the top left of the current J.
					if (checkTileColide(j, parentPosition, childPosition.x - 100, childPosition.y + 100))
						parentTile->addEdge(j, 150);

					// check one to the top right of the current J.
					if (checkTileColide(j, parentPosition, childPosition.x + 100, childPosition.y + 100))
						parentTile->addEdge(j, 150);

					// check one to the bottom left of the current J.
					if (checkTileColide(j, parentPosition, childPosition.x - 100, childPosition.y - 100))
						parentTile->addEdge(j, 150);

					// check one to the bottom right of the current J.
					if (checkTileColide(j, parentPosition, childPosition.x + 100, childPosition.y - 100))
						parentTile->addEdge(j, 150);

				}
			}
		}
	}
}

bool ObjectManager::checkTileColide(Tile * a_tile, V2<float> a_position, float x, float y)
{
	bool colide = a_tile->getColide();
	return (a_position.x == x && a_position.y == y && colide == false) ? true : false;
}

Tile * ObjectManager::getTileAtPosition(float x, float y)
{
	Tile * result = nullptr;
	for (Tile* i : m_tileList)
	{
		V2<float> pos = i->getPosition();

		if (pos.x > x - 50 && pos.x < x + 50)
		{
			if (pos.y > y - 50 && pos.y < y + 50)
				result = i;
		}
	}
	return result;
}

bool ObjectManager::tileCheck(Tile* a_target)
{
	if (a_target == nullptr)
		return true;
	return a_target->getColide();
}

Tile * ObjectManager::getWaterTile(float x, float y)
{
	V2<float> target;
	target.x = x; target.y = y;
	V2<float> predif = { 100000,10000 };
	
	Tile * result = nullptr;

	for (Tile* i : m_waterTileList)
	{
		V2<float> pos = i->getPosition();
		V2<float> dif = pos - target;

		if (dif.getMagnitude() < predif.getMagnitude())
		{
			result = i;
			predif = dif;
		}
	}
	return result;
}

Tile * ObjectManager::getTree(float x, float y)
{
	V2<float> target;
	target.x = x; target.y = y;
	V2<float> predif = { 100000, 10000 };

	Tile * temp = nullptr;
	Tile * result = nullptr;

	for (Tree* i : m_treeList)
	{
		V2<float> pos = i->getPosition();
		V2<float> dif = pos - target;

		if (dif.getMagnitude() < predif.getMagnitude())
		{
			temp = getTileAtPosition(i->getX(), i->getY());
			if (!temp->getColide())
			{
				result = temp;
				predif = dif;

				// If a target tree is found within 300 pixels go to it instead of wasting resources
				// trying to source out a tree that is slightly closer.
				if (predif.getMagnitude() < 300.0f)
					break;
			}
		}
	}
	return result;
}

Entity * ObjectManager::getClosestEntity(BehaviourType a_dinosaurRole, float x, float y, Entity * a_self)
{

	V2<float> target;
	target.x = x; target.y = y;
	V2<float> predif = { 100000, 10000 };

	Entity * result = nullptr;

	for (Entity* i : m_entityList)
	{
		if (i != a_self && i->getBehaviourType() == a_dinosaurRole)
		{
			V2<float> pos = i->getPosition();
			V2<float> dif = pos - target;

			if (dif.getMagnitude() < predif.getMagnitude())
			{
				result = i;
				predif = dif;
			}
		}
	}
	return result;

}

void ObjectManager::createDijkstraRoute(float x1, float y1, float x2, float y2, std::vector<Tile*> &a_list)
{
	// Clear the current path.
	a_list.clear();

	// Calculate the StartTile and EndTile based on the X / Y inputs.
	Tile * startTile = getTileAtPosition(x1, y1);
	Tile * endTile = getTileAtPosition(x2, y2);

	// Check that the StartTile is a valid tile otherwise pick another tile around it.
	// This fixes a bug that appears when swapping between AI modes.
	if (tileCheck(startTile))
		startTile = getTileAtPosition(x1 - 100, y1);
	if (tileCheck(startTile))
		startTile = getTileAtPosition(x1 + 100, y1);
	if (tileCheck(startTile))
		startTile = getTileAtPosition(x1, y1 - 100);
	if (tileCheck(startTile))
		startTile = getTileAtPosition(x1, y1 + 100);

	// If the StartTile or EndTile is Solid don't try to build a path.
	if (tileCheck(endTile) || tileCheck(startTile))
		return;

	// Reset all Tiles.
	for (Tile* i : m_tileList)
	{
		i->setGScore(1000, nullptr);
		i->setPathActive(false);
	}

	// Configure the Start and End Tile.
	startTile->setGScore(0, nullptr);

	// Create our temporary lists for storing nodes we're visiting/visisted.
	std::vector<Tile*> openList;
	std::vector<Tile*> closeList;
	Tile* currentNode = nullptr;

	openList.push_back(startTile);

	while (!openList.empty())
	{

		std::sort(openList.begin(), openList.end(), [](Tile* lhs, Tile* rhs) {return lhs->getGScore() < rhs->getGScore(); });

		currentNode = openList[0];
		if (currentNode == endTile)
			break;

		openList.erase(std::find(openList.begin(), openList.end(), currentNode));
		closeList.push_back(currentNode);

		for (Edge * c : currentNode->m_edgeList)
		{
			if (!checkList(closeList, c->m_edgeTarget))
			{
				short gScore = currentNode->getGScore() + c->m_edgeCost;

				if (!checkList(openList, c->m_edgeTarget))
				{
					c->m_edgeTarget->setGScore(gScore, currentNode);
					openList.push_back(c->m_edgeTarget);
				}
				else if (gScore < c->m_edgeTarget->getGScore())
				{
					c->m_edgeTarget->setGScore(gScore, currentNode);
				}

			}

		}

	}

	// Create the path backwards from the end.
	currentNode = endTile;

	while (currentNode != startTile)
	{
		a_list.push_back(currentNode);
		currentNode->setPathActive(true);

		if (currentNode != currentNode->getGParent())
			currentNode = currentNode->getGParent();
		else
		{
			a_list.clear();
			break;
		}
	}
	a_list.push_back(startTile);
	startTile->setPathActive(true);

	// Reverse the path.
	std::reverse(a_list.begin(), a_list.end());
}

bool ObjectManager::checkList(std::vector<Tile*> a_list, Tile* a_target)
{
	for (Tile * j : a_list)
		if (j == a_target) { return true; };
	return false;
}

