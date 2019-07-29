#include "Tree.h"

Tree::Tree()
{
	m_foliageTransparency	= 1;
	m_depth					= 0.2f;
}

Tree::~Tree()
{
}

void Tree::customDraw(aie::Renderer2D * a_renderer)
{
	a_renderer->setRenderColour(1, 1, 1, m_foliageTransparency);
	a_renderer->drawSprite(m_foliage, m_position.x, m_position.y, 0, 0, 0, 0.1);
}

void Tree::addFoliage(ResourceManager * a_resourceManager, char a_spriteGameName[])
{
	m_foliage = a_resourceManager->getSprite(a_spriteGameName);
}

void Tree::setTransparency(float a_transparency)
{
	m_foliageTransparency = a_transparency;
}

