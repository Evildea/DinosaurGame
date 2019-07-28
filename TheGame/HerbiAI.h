#pragma once
#include "AbstractAI.h"

class HerbiAI : public AbstractAI
{
private:
	enum States { SLEEP, PICKTARGET, FLEETARGET, SEEKRANDOMTARGET, SEEKWATER, DRINK, SEEKTREE, EAT };
	States m_state;
	float timer;

public:
	HerbiAI();
	~HerbiAI();

	virtual void update(float deltaTime, V2<int> a_cameraPosition);
};

