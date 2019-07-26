#include "GameManager.h"

GameManager::GameManager()
{
	// Instantiate the managers that will control all aspects of the game.
	m_resourceManager	= new ResourceManager;
	m_inputManager		= new InputManager;
	m_objectManager		= new ObjectManager;

	// Inform the manager about eachother.
	m_objectManager->addResourceManager(m_resourceManager);
	m_inputManager->addObjectManager(m_objectManager);

	// Generate the textures.
	m_resourceManager->addTexture("../bin/textures/Bones.png", "bones");
	m_resourceManager->addTexture("../bin/textures/DinoBody.png", "pred");
	m_resourceManager->addTexture("../bin/textures/DinoBodyScar.png", "predscar");
	m_resourceManager->addTexture("../bin/textures/DinoHead.png", "predhead");
	m_resourceManager->addTexture("../bin/textures/DinoLegs.png", "predlegs");
	m_resourceManager->addTexture("../bin/textures/DinoBody2.png", "herbi");
	m_resourceManager->addTexture("../bin/textures/DinoBody2Scar.png", "herbiscar");
	m_resourceManager->addTexture("../bin/textures/DinoHead2.png", "herbihead");
	m_resourceManager->addTexture("../bin/textures/DinoLegs2.png", "herbilegs");
	m_resourceManager->addTexture("../bin/textures/Trunk.png", "trunk");
	m_resourceManager->addTexture("../bin/textures/Leaves.png", "leaves");
	m_resourceManager->addTexture("../bin/textures/Grass.png", "grass");
	m_resourceManager->addTexture("../bin/textures/Water.png", "water");
	m_resourceManager->addTexture("../bin/textures/Rock01.png", "rock01");
	m_resourceManager->addTexture("../bin/textures/Rock02.png", "rock02");
	m_resourceManager->addTexture("../bin/textures/Rock03.png", "rock03");


	// Randomly generate all map tiles.
	for (int i = 0; i < g_MAPWIDTH; i++)
	{
		for (int j = 0; j < g_MAPHEIGHT; j++)
		{
			int range01 = 100 - g_ROCKDENSITY;
			int range02 = range01 - g_ROCKDENSITY;
			int range03 = range02 - g_ROCKDENSITY;
			int range04 = range03 - g_WATERDENSITY;

			int random = rand() % 100;
			if (random <= range04)
				addTile(NONE, "grass", i * 100, j * 100);
			if (random > range04  && random <= range03)
				addTile(WATER, "water", i * 100, j * 100);
			if (random > range03  && random <= range02)
				addTile(SOLID, "rock01", i * 100, j * 100);
			if (random > range02 && random <= range01)
				addTile(SOLID, "rock02", i * 100, j * 100);
			if (random > range01)
				addTile(SOLID, "rock03", i * 100, j * 100);
		}
	}

	// Create links between tiles (The TILES act as NODES for path finding).
	m_objectManager->LinkTiles();

	// Randomly generates Trees.
	for (int i = 0; i < g_MAPWIDTH; i++)
	{
		for (int j = 0; j < g_MAPHEIGHT; j++)
		{
			int random = rand() % 100;
			if (random < g_TREEDENSITY)
				addTree("trunk", "leaves", (i * 100) + 30, (j * 100) + 30);
		}
	}

	// Randomly generate Predators on Tiles that aren't SOLID.
	Tile * currentTile;
	for (int i = 0; i < g_MAPWIDTH; i++)
	{
		for (int j = 0; j < g_MAPHEIGHT; j++)
		{
			int random = rand() % 100;
			if (random <= g_PREDATORDENSITY)
			{
				currentTile = m_objectManager->getTileAtPosition(i * 100, j * 100);
				if (!currentTile->getColide())
					addEntity("pred", "predhead", "predlegs", "predscar", i * 100, j * 100, 130, 134, 95, 95, 101, 82);
			}
		}
	}

	// Randomly generate Herbis on Tiles that aren't SOLID.
	for (int i = 0; i < g_MAPWIDTH; i++)
	{
		for (int j = 0; j < g_MAPHEIGHT; j++)
		{
			int random = rand() % 100;
			if (random <= g_HERBIDENSITY)
			{
				currentTile = m_objectManager->getTileAtPosition(i * 100, j * 100);
				if (!currentTile->getColide())
					addEntity("herbi", "herbihead", "herbilegs", "herbiscar", i * 100, j * 100, 84, 139, 145, 76, 98, 109);
			}
		}
	}
}

GameManager::~GameManager()
{
	delete m_resourceManager;
	delete m_inputManager;
	delete m_objectManager;
}

void GameManager::update(float deltaTime)
{
	m_inputManager->update();
	m_objectManager->update(deltaTime, m_inputManager->getCameraPosition());
}

void GameManager::draw(aie::Renderer2D* a_renderer)
{
	m_objectManager->draw(a_renderer);
	m_inputManager->draw(a_renderer);
}

void GameManager::addEntity(char a_PrimaryTexture[], char a_SecondaryTexture[], char a_ThirdTexture[], char a_scarTexture[], float x, float y, float r, float g, float b, float r1, float g1, float b1)
{

	m_objectManager->addEntity(a_PrimaryTexture, a_scarTexture, x, y, r, g, b, r1, g1, b1);
	m_objectManager->addHead(a_SecondaryTexture);
	m_objectManager->addLegs(a_ThirdTexture);
}

void GameManager::addTree(char a_PrimaryTexture[], char a_SecondaryTexture[], float x, float y)
{
	m_objectManager->addTree(a_PrimaryTexture, x, y);
	m_objectManager->addLeaves(a_SecondaryTexture);
}

void GameManager::addTile(CollisionType a_collision, char a_PrimaryTexture[], float x, float y)
{
	m_objectManager->addTile(a_collision, a_PrimaryTexture, x, y);
}


