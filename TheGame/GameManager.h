#pragma once
#include "ResourceManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "Renderer2D.h"
#include "Input.h"

class GameManager
{
private:
	ResourceManager*	m_resourceManager;
	InputManager*		m_inputManager;
	ObjectManager*		m_objectManager;

public:

	~GameManager();

	// ALL GAME OBJECTS are created and configured in the Constructor.
	GameManager();

	void update(float deltaTime);
	void draw(aie::Renderer2D* a_renderer);

	// This function instantiates a new object on the stack.
	void addEntity(char a_PrimaryTexture[], char a_SecondaryTexture[], char a_ThirdTexture[], float x, float y, float r, float g, float b, float r1, float g1, float b1);
	void addTree(char a_PrimaryTexture[], char a_SecondaryTexture[], float x, float y);
	void addTile(CollisionType a_collision, char a_PrimaryTexture[], float x, float y);

};

