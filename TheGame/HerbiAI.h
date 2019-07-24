#pragma once
#include "AbstractAI.h"

class HerbiAI : public AbstractAI
{
public:
	HerbiAI();
	~HerbiAI();

	virtual void update(float deltaTime, V2<int> a_cameraPosition) {};
};

