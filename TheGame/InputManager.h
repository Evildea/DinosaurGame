#pragma once
#include "Input.h"
#include "ObjectManager.h"
#include "V2.h"
#include "Renderer2D.h"

enum Action {SINGLE_SELECT, GROUP_SELECT};

class InputManager
{
private:
	ObjectManager*		m_objectManager;
	V2<int>				m_startPoint;
	V2<int>				m_endPoint;
	Action				m_selectType;
	V2<int>				m_cameraPosition;

public:
	InputManager();
	~InputManager();

	void update();
	void draw(aie::Renderer2D * a_renderer);

	void addObjectManager(ObjectManager * a_objectManager);
	V2<int> getCameraPosition();

};

