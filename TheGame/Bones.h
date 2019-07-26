#pragma once
#include "AbstractObject.h"

class Bones : public AbstractObject
{
public:
	Bones();
	~Bones() {};

	virtual void customUpdate(float deltatime) {};
	virtual void customDraw(aie::Renderer2D* a_renderer) {};

};

