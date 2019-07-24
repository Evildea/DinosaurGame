#pragma once
#include "AbstractObject.h"
#include "Global.h"
#include <vector>

enum CollisionType { NONE, SOLID, WATER };

struct Edge;

class Tile :
	public AbstractObject
{
private:
	CollisionType		m_collisionType;
	short				m_gScore;
	Tile*				m_gParent;
	bool				m_PathActivate;

public:
	std::vector<Edge*>	m_edgeList;

	Tile();
	~Tile();

	virtual void customUpdate(float deltatime) {};
	virtual void customDraw(aie::Renderer2D* a_renderer);

	void addEdge(Tile * a_edgeTarget, short a_edgeCost);
	void setCollisionType(CollisionType a_collision);
	
	// Return whether this Tile is a solid Tile.
	bool getColide();

	void setGScore(short a_gScore, Tile* a_gParent);
	void setPathActive(bool a_active);
	short getGScore();
	Tile* getGParent();

};

struct Edge
{
	short m_edgeCost;
	Tile* m_edgeTarget;
};

