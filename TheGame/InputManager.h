#pragma once
#include "Input.h"
#include "ObjectManager.h"
#include "V2.h"
#include "Renderer2D.h"

enum Action {SINGLE_SELECT, GROUP_SELECT};

class InputManager
{
private:
	ObjectManager*		m_objectManager;		// This represents the Object Manager.
	V2<int>				m_selectionStartPoint;	// This represents the start point of the group selection.
	V2<int>				m_selectionEndPoint;	// This represents the end point of the group selection.
	Action				m_selectionType;		// This represents the selection type. I.e. SINGLE or GROUP.
	V2<int>				m_cameraPosition;		// This represents the position of the camera.

public:
	InputManager();
	~InputManager() {};

	// These functions perform the update and draw functions.
	void update();
	void draw(aie::Renderer2D * a_renderer);

	// This function adds the Object Manager.
	void addObjectManager(ObjectManager * a_objectManager);

	// This function returns the current camera position.
	V2<int> getCameraPosition();

};

