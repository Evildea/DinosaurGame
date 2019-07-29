#pragma once
#include "HerbiAI.h"
#include "PredatorAI.h"
#include "UserControlled.h"
#include "Renderer2D.h"

enum BehaviourType { UserControlledAI, PredatorControlledAI, HerbiControlledAI, NoAI };
class AbstractObject;

class BehaviourManager
{
private:
	AbstractAI*		m_behaviourType; // This represents the AI associated with this behaviour manager.

public:
	BehaviourManager();
	~BehaviourManager();

	// This function sets the AI for this behaviour manager.
	void setAI(BehaviourType a_behaviour, AbstractObject* a_owner);

	// This function performs the AI's update function.
	void update(float deltaTime, V2<int> a_cameraPosition);
};

