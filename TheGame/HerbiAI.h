#pragma once
#include "AbstractAI.h"

class HerbiAI : public AbstractAI
{
private:
	// These states represent the different states of the AI Finite State Machine.
	enum States { START, FLEE, SEEK_RANDOM, SEEK_WATER, DRINK, SEEK_TREE, EAT };
	States m_state;

	// This timer is used for creating delays between actions within the Finite State Machine.
	float timer;

public:
	HerbiAI();
	~HerbiAI();

	// This function manages the AI Finite State Machine.
	virtual void update(float deltaTime, V2<int> a_cameraPosition);
	void FleeFrom(float x, float y);
};

