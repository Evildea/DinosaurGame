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
	AbstractObject*		m_owner;
	std::vector<Tile*>	m_path;
	char				m_type;

public:
	AbstractAI();
	~AbstractAI();

	void setOwner(AbstractObject* a_owner) { m_owner = a_owner; };
	virtual void update(float deltaTime, V2<int> a_cameraPosition) = 0;
	void draw(aie::Renderer2D* a_renderer);

	bool CreatePath(std::vector<Tile*> &a_path, float a_targetX, float a_targetY);
	void FollowPath(std::vector<Tile*> &a_path, float deltaTime);
	
	char GetAIType();

};

