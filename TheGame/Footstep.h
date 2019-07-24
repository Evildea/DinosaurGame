#pragma once
#include "AbstractObject.h"

class Footstep : public AbstractObject
{
public:
	Footstep();
	~Footstep();

	virtual void customUpdate(float deltatime) {};
	virtual void customDraw(aie::Renderer2D* a_renderer) {};

};

