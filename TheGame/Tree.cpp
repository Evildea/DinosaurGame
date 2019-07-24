#include "Tree.h"

Tree::Tree()
{
	m_transparency = 1;
	m_depth = 0.2f;
}

Tree::~Tree()
{
}

void Tree::customDraw(aie::Renderer2D * a_renderer)
{
	a_renderer->setRenderColour(1, 1, 1, m_transparency);
	a_renderer->drawSprite(m_leaves, m_position.x, m_position.y, 0, 0, 0, 0.1);
}

void Tree::addLeaves(ResourceManager * a_resourceManager, char a_textureGameName[])
{
	m_leaves = a_resourceManager->getTexture(a_textureGameName);
}

void Tree::setTransparency(float a_transparency)
{
	m_transparency = a_transparency;
}

