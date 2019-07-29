#pragma once
#include "AbstractObject.h"
#include "ResourceManager.h"

class Tree : public AbstractObject
{
private:
	aie::Texture*	m_foliage;				// This represents the foliage of the Tree.
	float			m_foliageTransparency;	// This represents the transparency of the foliage.

public:
	Tree();
	~Tree();

	// These are custom update and draw functions.
	virtual void customUpdate(float deltatime) {};
	virtual void customDraw(aie::Renderer2D* a_renderer);

	// This function adds foliage for the tree.
	void addFoliage(ResourceManager* a_resourceManager, char a_spriteGameName[]);

	// This function sets the transparency of the foliage based on how close a dinosaur is.
	void setTransparency(float a_transparency);

};

