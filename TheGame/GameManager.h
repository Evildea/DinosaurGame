#pragma once
#include "ResourceManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "Renderer2D.h"
#include "Input.h"

class GameManager
{
private:
	ResourceManager*	m_resourceManager;	// This represents the Resource Manager which manages sprites.
	InputManager*		m_inputManager;		// This represents the Input Manager which manages user input.
	ObjectManager*		m_objectManager;	// This represents the Object Manager which manages all the game objects.

public:

	~GameManager();

	// ALL GAME OBJECTS are created and configured in the Constructor.
	GameManager();

	// These functions perform the update and draw of the Input and Object Managers.
	void update(float deltaTime);
	void draw(aie::Renderer2D* a_renderer);

	// This function instantiates a new Dinosaur on the stack.
	void addEntity(char a_PrimaryTexture[], char a_SecondaryTexture[], char a_ThirdTexture[], char a_scarTexture[], BehaviourType a_dinosaurRole, float x, float y, float r, float g, float b, float r1, float g1, float b1);
	
	// This function instantiates a new Tree on the stack.
	void addTree(char a_PrimaryTexture[], char a_SecondaryTexture[], float x, float y);

	// This function instantiates a new Tile on the stack.
	void addTile(CollisionType a_collision, char a_PrimaryTexture[], float x, float y);

};

