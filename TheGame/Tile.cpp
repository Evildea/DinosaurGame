#include "Tile.h"



Tile::Tile()
{
	m_depth = 0.5f;
	m_PathActivate = false;
}


Tile::~Tile()
{
	for (Edge* i : m_edgeList)
		delete i;
}



void Tile::customDraw(aie::Renderer2D * a_renderer)
{
	// Draw this only if debug mode is activated.
	if (g_DEBUGMODE)
	{
		// Draw a center circle.
		if (m_PathActivate)
			a_renderer->setRenderColour(1, 0, 0);
		else
			a_renderer->setRenderColour(1, 1, 1);
		a_renderer->drawCircle(m_position.x, m_position.y, 5);

		// Draw the Edges.
		for (Edge * i : m_edgeList)
		{
			if (i->m_edgeTarget == m_gParent && m_PathActivate)
			{
				a_renderer->setRenderColour(1, 0, 0);
				a_renderer->drawLine(m_position.x, m_position.y, i->m_edgeTarget->getPosition().x, i->m_edgeTarget->getPosition().y);
			}
		}
	}
}

void Tile::addEdge(Tile * a_edgeTarget, short a_edgeCost)
{
	m_edgeList.push_back(new Edge);
	m_edgeList.back()->m_edgeTarget = a_edgeTarget;
	m_edgeList.back()->m_edgeCost = a_edgeCost;

}

void Tile::setCollisionType(CollisionType a_collision)
{
	m_collisionType = a_collision;
}

bool Tile::getColide()
{
	return (m_collisionType == SOLID) ? true : false;
}

void Tile::setGScore(short a_gScore, Tile * a_gParent)
{
	m_gScore = a_gScore;
	m_gParent = (a_gParent == nullptr) ? this : a_gParent;
	m_PathActivate = false;
}

void Tile::setPathActive(bool a_active)
{
	m_PathActivate = a_active;
}

short Tile::getGScore()
{
	return m_gScore;
}

Tile * Tile::getGParent()
{
	return m_gParent;
}
