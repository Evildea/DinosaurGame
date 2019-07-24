#include "TheGameApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

TheGameApp::TheGameApp() {
	srand(time(NULL));
}

TheGameApp::~TheGameApp() {

}

bool TheGameApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	m_gameManager = new GameManager;

	return true;
}

void TheGameApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete m_gameManager;
}

void TheGameApp::update(float deltaTime) {

	m_gameManager->update(deltaTime);

}

void TheGameApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	m_gameManager->draw(m_2dRenderer);

	// done drawing sprites
	m_2dRenderer->end();
}