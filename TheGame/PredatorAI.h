#pragma once
#include "AbstractAI.h"

class PredatorAI : public AbstractAI
{
private:
	// These states represent the different states of the AI Finite State Machine.
	enum States {START, SEEK_WATER, SEEK_RANDOM, HUNT_HERBI, DRINK, SLEEP};
	States m_state;

	// This timer is used for creating delays between actions within the Finite State Machine.
	float timer;

	// This represents the herbivore (prey) of the predator.
	AbstractObject* m_herbi;

public:
	PredatorAI();
	~PredatorAI();

	// This function manages the AI Finite State Machine.
	virtual void update(float deltaTime, V2<int> a_cameraPosition);

};

