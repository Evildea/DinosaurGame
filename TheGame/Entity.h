#pragma once
#include "AbstractObject.h"
#include "Tail.h"
#include "Head.h"
#include "Legs.h"

class Entity : public AbstractObject
{
private:
	Tail*			m_tail;					// This represents the dinosaur's tail.
	Head*			m_head;					// This represents the dinosaur's head.
	Legs*			m_legs;					// This represents the dinosaur's legs.
	float			m_thirst, m_hunger;		// These represent the dinosaur's vitals.
	V2<float>		m_previousPosition;		// This represents the previous position of the dinosaur.
	V2<float>		m_previousDifference;	// This represents the difference of the previous position and the current.
	BehaviourType	m_dinosaurRole;			// This represents the role the dinosaur is playing: i.e. Predator of Herbivore.

public:
	Entity();
	~Entity();

	// These are custom update and draw functions.
	virtual void customUpdate(float deltaTime);
	virtual void customDraw(aie::Renderer2D* a_renderer);

	// These functions set or get the whether the dinosaur has been selected by the user.
	void setMouseSelected(bool a_selectedStatus);
	bool getMouseSelected();

	// These functions set the Tail colours.
	void setTailColour(float r, float g, float b);
	void setTailSpotColour(float r, float g, float b);

	// These functions get the dinosaur's head and legs.
	Head* getHead();
	Legs* getLegs();

	// These functions return the dinosaur's vitals.
	virtual int getThirst() override { return m_thirst; };
	virtual int getHealth() override { return m_health; };
	virtual int getHunger() override { return m_hunger; };
	
	// These functions set the dinosaur's vitals.
	virtual void setHealth(int a_health) override { m_health = (a_health < 100) ? a_health : 100; }
	virtual void setThirst(int a_thirst) override { m_thirst = (a_thirst < 100) ? a_thirst : 100; }
	virtual void setHunger(int a_hunger) override { m_hunger = (a_hunger < 100) ? a_hunger : 100; }

	// This function gets the distance the dinosaur has travelled.
	float getDistanceTravelled();

	// These functions set and return the AI associated with the dinosaur.
	void setSpeciesType(BehaviourType a_dinosaurRole);
	virtual BehaviourType getBehaviourType() override { return m_dinosaurRole; };

	// This draws a health, thirst or hunger bar when the dinosaur is selected.
	void DrawBar(aie::Renderer2D* a_renderer, int a_yOffset, int a_valueToDraw, float r, float g, float b);

};
