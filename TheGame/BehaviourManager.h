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
	AbstractAI*		m_behaviourType;

public:
	BehaviourManager();
	~BehaviourManager();

	void setAI(BehaviourType a_behaviour, AbstractObject* a_owner);

	void update(float deltaTime, V2<int> a_cameraPosition);
	virtual void draw(aie::Renderer2D* a_renderer);
};

