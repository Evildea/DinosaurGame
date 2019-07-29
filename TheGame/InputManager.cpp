#include "InputManager.h"

InputManager::InputManager()
{
	m_cameraPosition			= { 0, 0 };
	m_selectionStartPoint		= { -10, -10 };
	m_selectionEndPoint			= { -10, -10 };
	m_selectionType				= SINGLE_SELECT;
}

void InputManager::update()
{
	aie::Input* input = aie::Input::getInstance();
	bool found;

	// Select a specific object on the map.
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT) && m_selectionType == SINGLE_SELECT)
	{
		found = m_objectManager->setSelected(input->getMouseX() + m_cameraPosition.x - 30, input->getMouseY() + m_cameraPosition.y - 30, input->getMouseX() + m_cameraPosition.x + 30, input->getMouseY() + m_cameraPosition.y + 30);
		if (found == false)
			m_selectionType = GROUP_SELECT;
	}

	// Select a range of objects on the map.
	if (m_selectionType == GROUP_SELECT)
	{
		// Set the end point of the bounding box to be the current mouse position.
		m_selectionEndPoint = { input->getMouseX() + m_cameraPosition.x, input->getMouseY() + m_cameraPosition.y };

		// LEFT CLICK: Set the start point of the bounding box.
		if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
			m_selectionStartPoint = { input->getMouseX() + m_cameraPosition.x, input->getMouseY() + m_cameraPosition.y };

		// RIGHT CLICK: Select all objects within the bounding box area.
		if (input->wasMouseButtonReleased(aie::INPUT_MOUSE_BUTTON_LEFT))
		{
			m_objectManager->setSelected(m_selectionStartPoint.x, m_selectionStartPoint.y, m_selectionEndPoint.x, m_selectionEndPoint.y);
			m_selectionType = SINGLE_SELECT;
		}
	}

	// These keys allow the movement of the camera.
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		m_cameraPosition.x -= 5;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		m_cameraPosition.x += 5;

	if (input->isKeyDown(aie::INPUT_KEY_UP))
		m_cameraPosition.y += 5;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		m_cameraPosition.y -= 5;

}

void InputManager::draw(aie::Renderer2D * a_renderer)
{
	// This updates the camera position.
	a_renderer->setCameraPos(m_cameraPosition.x, m_cameraPosition.y);

	// This draws a box showing the selection area.
	if (m_selectionType == GROUP_SELECT)
	{
		a_renderer->setRenderColour(1, 0, 0);
		a_renderer->drawLine(m_selectionStartPoint.x, m_selectionStartPoint.y, m_selectionEndPoint.x, m_selectionStartPoint.y);
		a_renderer->drawLine(m_selectionStartPoint.x, m_selectionStartPoint.y, m_selectionStartPoint.x, m_selectionEndPoint.y);
		a_renderer->drawLine(m_selectionStartPoint.x, m_selectionEndPoint.y, m_selectionEndPoint.x, m_selectionEndPoint.y);
		a_renderer->drawLine(m_selectionEndPoint.x, m_selectionStartPoint.y, m_selectionEndPoint.x, m_selectionEndPoint.y);
	}
}

void InputManager::addObjectManager(ObjectManager * a_objectManager)
{
	m_objectManager = a_objectManager;
}

V2<int> InputManager::getCameraPosition()
{
	return m_cameraPosition;
}
