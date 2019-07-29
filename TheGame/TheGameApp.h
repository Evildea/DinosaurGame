#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "GameManager.h"
#include "Global.h"
#include <time.h>
#include "CRT.h"

class TheGameApp : public aie::Application {
public:

	TheGameApp();
	virtual ~TheGameApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	GameManager*		m_gameManager;
};