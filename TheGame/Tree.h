#pragma once
#include "AbstractObject.h"
#include "ResourceManager.h"

class Tree : public AbstractObject
{
private:
	aie::Texture*	m_leaves;
	float			m_transparency;

public:
	Tree();
	~Tree();

	virtual void customUpdate(float deltatime) {};
	virtual void customDraw(aie::Renderer2D* a_renderer);

	void addLeaves(ResourceManager* a_resourceManager, char a_textureGameName[]);
	void setTransparency(float a_transparency);

};

