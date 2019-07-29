#pragma once
#include "AbstractAI.h"
#include "Input.h"

class UserControlled : public AbstractAI
{
private:
	// This represents whether a target has been choosen by the User.
	bool m_targetSet;

public:
	UserControlled();
	~UserControlled();

	// This function manages the user input and directs the dinosaur accordingly.
	virtual void update(float deltaTime, V2<int> a_cameraPosition);

};

