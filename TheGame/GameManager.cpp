#include "GameManager.h"

GameManager::GameManager()
{
	// Instantiate the managers that will control all aspects of the game.
	m_resourceManager	= DBG_NEW ResourceManager;
	m_inputManager		= DBG_NEW InputManager;
	m_objectManager		= DBG_NEW ObjectManager;

	// Inform the manager about eachother.
	m_objectManager->addResourceManager(m_resourceManager);
	m_inputManager->addObjectManager(m_objectManager);

	// Generate the textures.
	m_resourceManager->addSprite("../bin/textures/Bones.png",			"bones");
	m_resourceManager->addSprite("../bin/textures/DinoBody.png",		"pred");
	m_resourceManager->addSprite("../bin/textures/DinoBodyScar.png",	"predscar");
	m_resourceManager->addSprite("../bin/textures/DinoHead.png",		"predhead");
	m_resourceManager->addSprite("../bin/textures/DinoLegs.png",		"predlegs");
	m_resourceManager->addSprite("../bin/textures/DinoBody2.png",		"herbi");
	m_resourceManager->addSprite("../bin/textures/DinoBody2Scar.png",	"herbiscar");
	m_resourceManager->addSprite("../bin/textures/DinoHead2.png",		"herbihead");
	m_resourceManager->addSprite("../bin/textures/DinoLegs2.png",		"herbilegs");
	m_resourceManager->addSprite("../bin/textures/Trunk.png",			"trunk");
	m_resourceManager->addSprite("../bin/textures/Leaves.png",			"leaves");
	m_resourceManager->addSprite("../bin/textures/Grass.png",			"grass");
	m_resourceManager->addSprite("../bin/textures/Water.png",			"water");
	m_resourceManager->addSprite("../bin/textures/Rock01.png",			"rock01");
	m_resourceManager->addSprite("../bin/textures/Rock02.png",			"rock02");
	m_resourceManager->addSprite("../bin/textures/Rock03.png",			"rock03");


	// Randomly generate all map tiles.
	for (int i = 0; i < g_MAPWIDTH; i++)
	{
		for (int j = 0; j < g_MAPHEIGHT; j++)
		{
			int range01 = 1000 - g_ROCKDENSITY;
			int range02 = range01 - g_ROCKDENSITY;
			int range03 = range02 - g_ROCKDENSITY;
			int range04 = range03 - g_WATERDENSITY;

			int random = rand() % 1000;
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
			int random = rand() % 1000;
			if (random < g_TREEDENSITY)
				addTree("trunk", "leaves", (i * 100) + 30, (j * 100) + 30);
		}
	}

	// Randomly generate Predators on Tiles that aren't SOLID.
	Tile * currentTile;
	int count = 0;

	while (count < g_PREDATORCOUNT)
	{
		int randX = (rand() % g_MAPWIDTH) * 100;
		int randY = (rand() % g_MAPHEIGHT) * 100;

		currentTile = m_objectManager->getTileAtPosition(randX, randY);
		if (!currentTile->getColide())
		{
			addEntity("pred", "predhead", "predlegs", "predscar", PredatorControlledAI, randX, randY, 130, 134, 95, 95, 101, 82);
			count++;
		}
	}

	// Randomly generate Herbivores on Tiles that aren't SOLID.
	count = 0;
	while (count < g_HERBICOUNT)
	{
		int randX = (rand() % g_MAPWIDTH) * 100;
		int randY = (rand() % g_MAPHEIGHT) * 100;

		currentTile = m_objectManager->getTileAtPosition(randX, randY);
		if (!currentTile->getColide())
		{
			addEntity("herbi", "herbihead", "herbilegs", "herbiscar", HerbiControlledAI, randX, randY, 84, 139, 145, 76, 98, 109);
			count++;
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

void GameManager::addEntity(char a_PrimaryTexture[], char a_SecondaryTexture[], char a_ThirdTexture[], char a_scarTexture[], BehaviourType a_dinosaurRole, float x, float y, float r, float g, float b, float r1, float g1, float b1)
{

	m_objectManager->addEntity(a_PrimaryTexture, a_scarTexture, a_dinosaurRole, x, y, r, g, b, r1, g1, b1);
	m_objectManager->addHead(a_SecondaryTexture);
	m_objectManager->addLegs(a_ThirdTexture);
}

void GameManager::addTree(char a_PrimaryTexture[], char a_SecondaryTexture[], float x, float y)
{
	m_objectManager->addTree(a_PrimaryTexture, x, y);
	m_objectManager->addFoliage(a_SecondaryTexture);
}

void GameManager::addTile(CollisionType a_collision, char a_PrimaryTexture[], float x, float y)
{
	m_objectManager->addTile(a_collision, a_PrimaryTexture, x, y);
}


