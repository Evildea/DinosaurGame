#include "BehaviourManager.h"
#include "AbstractObject.h"

BehaviourManager::BehaviourManager()
{
	m_behaviourType = nullptr;
}


BehaviourManager::~BehaviourManager()
{
	delete m_behaviourType;
}

void BehaviourManager::setAI(BehaviourType a_behaviour, AbstractObject* a_owner)
{

	if (a_behaviour == UserControlledAI)
	{
		if (m_behaviourType != nullptr)
		{
			if (m_behaviourType->GetAIType() != 'u')
			{
				delete m_behaviourType;
				m_behaviourType = DBG_NEW UserControlled;
			}
		}
		else
			m_behaviourType = DBG_NEW UserControlled;
	}

	if (a_behaviour == PredatorControlledAI)
	{
		if (m_behaviourType != nullptr)
		{
			if (m_behaviourType->GetAIType() != 'p')
			{
				delete m_behaviourType;
				m_behaviourType = DBG_NEW PredatorAI;
			}
		}
		else
			m_behaviourType = DBG_NEW PredatorAI;
	}

	if (a_behaviour == HerbiControlledAI)
	{
		if (m_behaviourType != nullptr)
		{
			if (m_behaviourType->GetAIType() != 'h')
			{
				delete m_behaviourType;
				m_behaviourType = DBG_NEW HerbiAI;
			}
		}
		else
			m_behaviourType = DBG_NEW HerbiAI;
	}

	if (m_behaviourType != nullptr)
		m_behaviourType->setOwner(a_owner);
}

void BehaviourManager::update(float deltaTime, V2<int> a_cameraPosition)
{
	if (m_behaviourType != nullptr)
		m_behaviourType->update(deltaTime, a_cameraPosition);
}
