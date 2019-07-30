#pragma once
#include "Renderer2D.h"
#include "Global.h"
#include <vector>
#include "V2.h"
#include "T2.h"

class AbstractObject;
class Tile;

class AbstractAI
{
protected:
	AbstractObject*		m_owner;	// This represents the dinosaur that owns this AI.
	std::vector<Tile*>	m_path;		// This represents the path used by this AI for pathfinding.
	char				m_type;		// This represents which AI type: i.e. 'p'redator, 'h'erbivore or 'u'ser-controlled.

public:
	AbstractAI();
	~AbstractAI();

	// This function sets the owner of this AI.
	void setOwner(AbstractObject* a_owner) { m_owner = a_owner; };

	// This function manages the AI Finite State Machine.
	virtual void update(float deltaTime, V2<int> a_cameraPosition) = 0;

	// These functions create paths for the AI or enable the AI to follow a path.
	bool createPath(std::vector<Tile*> &a_path, float a_targetX, float a_targetY);
	void followPath(std::vector<Tile*> &a_path, float deltaTime);

	// These functions clamp target positions to ensure they are on the map.
	void clampPosition(float &x, float &y);
	void clampPosition(int &x, int &y);
	
	// This function returns the AI type: i.e. 'p'redator, 'h'erbivore or 'u'ser-controlled.
	char getAIType();

};

