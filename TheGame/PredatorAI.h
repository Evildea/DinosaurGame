#pragma once
#include "AbstractAI.h"

class PredatorAI : public AbstractAI
{
private:
	enum States {SLEEP, PICKTARGET, SEEKRANDOMTARGET, SEEKWATER, DRINK, SEEKTREE, EAT};
	States m_state;
	float timer;

public:
	PredatorAI();
	~PredatorAI();

	virtual void update(float deltaTime, V2<int> a_cameraPosition);

};

