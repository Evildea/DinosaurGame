#pragma once
#include "ResourceManager.h"
#include "Renderer2D.h"
#include "Bones.h"
#include <algorithm>
#include "Entity.h"
#include "Tree.h"
#include "Tile.h"
#include <vector>
#include "V2.h"

class ObjectManager
{
private:
	std::vector<Entity*>	m_EntityList;		// List of Dinosaurs in the game.
	std::vector<Tree*>		m_TreeList;			// List of Trees in the game.
	std::vector<Bones*>		m_BonesList;		// List of Bones in the game.
	std::vector<Tile*>		m_TileList;			// List of Tiles in the game.
	std::vector<Tile*>		m_waterTileList;	// List of Water tiles in the game.
	ResourceManager*		m_resourceManager;	// Pointer to the ResourceManager so the ObjectManager can access resources.

public:
	ObjectManager();
	~ObjectManager();

	void update(float deltaTime, V2<int> a_cameraPosition);
	void draw(aie::Renderer2D* a_renderer);

	// This function provides the ObjectManager with access to the ResourceManager.
	void addResourceManager(ResourceManager * a_resourceManager);

	// These functions allow the GameManager to add different object types to the game.
	void addEntity(char a_textureGameName[], char a_scarTextureGameName[], BehaviourType a_dinosaurRole, float x, float y, float r, float g, float b, float r1, float g1, float b1);
	void addTree(char a_textureGameName[], float x, float y);
	void addTile(CollisionType a_collision, char a_textureGameName[], float x, float y);
	void addBones(char a_textureGameName[], float x, float y);

	// These functions allow the GameManager to add components to the different objects in the game.
	void addHead(char a_textureGameName[]);
	void addLegs(char a_textureGameName[]);
	void addLeaves(char a_textureGameName[]);

	// This function selects all objects within a specific area.
	bool setSelected(float x1, float y1, float x2, float y2);

	// These functions check Tile and Object collisions.
	Tile* getTileAtPosition(float x, float y);	// Returns the Tile at a specific location.
	Tile* getWaterTile(float x, float y);		// Returns the Water Tile at a specific location.
	Tile* getTree(float x, float y);			// Returns a Tree at a specific location.
	Entity* getClosestEntity(BehaviourType a_dinosaurRole, float x, float y, Entity* a_self);

	bool tileCheck(Tile* a_target);				// Returns True if a Tile is a NULLPTR or SOLID.

	// This function generates edge links between all the tiles. This is for Dijkstra's algorithm.
	void LinkTiles();

	// This function is used by LinkTiles to check if a link between two tiles should exist.
	bool checkTileColide(Tile * a_tile, V2<float> a_position, float x, float y);

	// These functions generate routes between tiles. This is Dijkstra's Algorithm.
	void CreateRoute(float x1, float y1, float x2, float y2, std::vector<Tile*> &a_list);
	bool checkList(std::vector<Tile*> a_list, Tile* a_target);

};
