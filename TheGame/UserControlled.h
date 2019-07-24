#pragma once
#include "AbstractAI.h"
#include "Input.h"

class UserControlled : public AbstractAI
{
private:
	bool m_targetSet;

public:
	UserControlled();
	~UserControlled();

	virtual void update(float deltaTime, V2<int> a_cameraPosition);

};

