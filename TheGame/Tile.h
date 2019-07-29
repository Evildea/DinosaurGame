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
	CollisionType		m_collisionType;	// This represents whether the Tile is SOLID or NOT.
	short				m_gScore;			// This is used by Dijkstra's Algorithm.
	Tile*				m_gParent;			// This is used by Dijkstra's Algorithm.
	bool				m_isPathActive;		// This represents whether to highlight this object if debug mode is on.

public:
	std::vector<Edge*>	m_edgeList;			// This represents the various edges of the object.

	Tile();
	~Tile();

	// These are custom update and draw functions.
	virtual void customUpdate(float deltatime) {};
	virtual void customDraw(aie::Renderer2D* a_renderer);

	// These functions add an edge and set its collision type (SOLID or NOT).
	void addEdge(Tile * a_edgeTarget, short a_edgeCost);
	void setCollisionType(CollisionType a_collision);
	
	// This function returns whether this Tile is a SOLID or NOT.
	bool getColide();

	// These functions are set by Dijkstra's Algorithm.
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

